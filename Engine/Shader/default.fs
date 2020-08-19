#version 330 core

// Interpolated values from the vertex shaders
in vec3 vertexPosition_cameraspace;
in vec3 fragmentColor;
in vec3 vertexNormal_cameraspace;
in vec2 texCoord;

in vec3 fogPosition;
in vec3 vertexPosition;
in mat4 tempMV;

// Ouput data
out vec4 color;

struct Light {
	int type;
	vec3 position_cameraspace;
	vec3 color;
	float power;
	float kC;
	float kL;
	float kQ;
	vec3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
	bool active;
};

struct FogParam
{
    vec3 color;        //Fog color
    float start;    //For linear fog
    float end;        //For linear fog
    float density;  //For exponential fog
    int type;        // 0 = linear, 1 = exp, 2 = exp2
    bool enabled;     //Toggle fog
};


struct Material {
	vec3 kAmbient;
	vec3 kDiffuse;
	vec3 kSpecular;
	float kShininess;
};

//FOG RELATED STUFF
struct VolumetricFogParam
{
	vec3 color;        	//Fog color
	float density;  	//For exponential fog
	bool enabled;   	//Toggle fog
	vec3 scale;			//Scale of fog 
	vec3 Position;		//Position of the fog
};

float getAttenuation(Light light, float distance) {
	if(light.type == 1)
		return 1;
	else
		return 1 / max(1, light.kC + light.kL * distance + light.kQ * distance * distance);
}

float getSpotlightEffect(Light light, vec3 lightDirection) {
	vec3 S = normalize(light.spotDirection);
	vec3 L = normalize(lightDirection);
	float cosDirection = dot(L, S);
	//return smoothstep(light.cosCutoff, light.cosInner, cosDirection);
	if(cosDirection < light.cosCutoff)
		return 0;
	else
		return 1; //pow(cosDirection, light.exponent);
}

float getFogFactor (FogParam fog, float fogDistance)
{
    //If fog is not enabled
    if(!fog.enabled)
    {
        return 0.0f;
    }

    float factor = 0.0f;
    //Linear
    if(fog.type == 0)
    {
        factor = (fog.end - fogDistance)/(fog.end-fog.start);
    }
    //exponential
    else if(fog.type == 1)
    {
        factor = exp(-fog.density * fogDistance);
    }
    //exponential2
    else if (fog.type == 2)
    {
        factor = exp(-pow(fog.density * fogDistance, 2.0));
    }

    factor = 1.0 - clamp(factor,0.0,1.0);
    return factor;
}

// Constant values
const int MAX_LIGHTS = 72;
const int MAX_TEXTURES = 8;

// Values that stay constant for the whole mesh.
uniform bool lightEnabled;
uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform int numLights;
uniform bool colorTextureEnabled[MAX_TEXTURES];
uniform sampler2D colorTexture[MAX_TEXTURES];
uniform bool textEnabled;
uniform vec3 textColor;
uniform bool greyscaleEnabled;
uniform FogParam fogParam;
uniform VolumetricFogParam volumetricfogparam;

void main(){
	
		if (colorTextureEnabled[0] == true && textEnabled == true)
		{
				color = texture2D (colorTexture[0], texCoord) * vec4(textColor, 1);
		}
		else
		{
			int texCount = 0;
			color = vec4(0, 0, 0, 0);
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				if (colorTextureEnabled[i] == true)
				{
					vec4 texColor = texture2D(colorTexture[i], texCoord);
					if (texColor.a < 0.1)
					{
						discard;
					}
					color += texColor;
					++texCount;
				}
			}
				if (texCount > 0)
				{
					color = color/texCount;
				}
				else
				{
					color = vec4(fragmentColor, 1);
				}
		}


	if(lightEnabled == true)
	{
		// Vectors
		vec3 eyeDirection_cameraspace = - vertexPosition_cameraspace;
		vec3 E = normalize(eyeDirection_cameraspace);
		vec3 N = normalize( vertexNormal_cameraspace );
		
		color = vec4(0, 0, 0, 0);
		
		color = (materialColor * vec4(material.kAmbient, 1));
		
		for(int i = 0; i < numLights; ++i)
		{
			if (lights[i].active != true)
			{
				continue;
			}
			
			// Light direction
			float spotlightEffect = 1;
			vec3 lightDirection_cameraspace;
			if(lights[i].type == 1) {
				lightDirection_cameraspace = lights[i].position_cameraspace;
			}
			else if(lights[i].type == 2) {
				lightDirection_cameraspace = lights[i].position_cameraspace - vertexPosition_cameraspace;
				spotlightEffect = getSpotlightEffect(lights[i], lightDirection_cameraspace);
			}
			else {
				lightDirection_cameraspace = lights[i].position_cameraspace - vertexPosition_cameraspace;
			}
			// Distance to the light
			float distance = length( lightDirection_cameraspace );
			
			// Light attenuation
			float attenuationFactor = getAttenuation(lights[i], distance);

			vec3 L = normalize( lightDirection_cameraspace );
			float cosTheta = clamp( dot( N, L ), 0, 1 );
			
			vec3 R = reflect(-L, N);
			float cosAlpha = clamp( dot( E, R ), 0, 1 );
			
			color += 
				
				// Diffuse : "color" of the object
				materialColor * vec4(material.kDiffuse, 1) * vec4(lights[i].color, 1) * lights[i].power * cosTheta * attenuationFactor * spotlightEffect +
				
				// Specular : reflective highlight, like a mirror
				vec4(material.kSpecular, 1) * vec4(lights[i].color, 1) * lights[i].power * pow(cosAlpha, material.kShininess) * attenuationFactor * spotlightEffect;
		}
	}
	
	if (greyscaleEnabled == true)
	{
		float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
		vec3 grayscale = vec3(gray);
		color = vec4(grayscale, color.a);
	}
	
	if (volumetricfogparam.enabled  && textEnabled != true)
	{
		vec3 dist = vertexPosition - fogPosition;
		if (
		abs(dist.x) < volumetricfogparam.scale.x * 0.5 && 
		abs(dist.y) < volumetricfogparam.scale.y * 0.5 && 
		abs(dist.z) < volumetricfogparam.scale.z * 0.5
		)
		{
			float fogDistance = abs(dist.y);
			float fogFactor = ((volumetricfogparam.scale.y * 0.5f) - fogDistance) / (volumetricfogparam.scale.y * 0.5f);
			color.xyz = mix(color.xyz, volumetricfogparam.color, fogFactor);
		}
	}
	
	if(fogParam.enabled)
    {
		float fogDistance = abs(vertexPosition_cameraspace.z);
        float fogFactor = getFogFactor(fogParam,fogDistance);
        color.xyz = mix(color.xyz,fogParam.color,fogFactor);
		
    }
	
	
}
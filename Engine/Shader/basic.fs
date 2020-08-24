#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out float FragDepth;

// Constant values
const int MAX_LIGHTS = 32; //Add a +1 for shadow light
const int MAX_TEXTURES = 8;

in vec3 vertexNormal_cameraspace;
in vec3 vertexPosition_cameraspace;

//Define all the structs here
struct Material 
{
	vec3 kColor;
	vec3 kAmbient;
	vec3 kDiffuse;
	vec3 kSpecular;
	float kShininess;

	sampler2D colorTexture[MAX_TEXTURES];
    int colorTextureNum;

    sampler2D SpecularMap;
    bool SpecularMapEnabled;
};

struct Light 
{
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
	bool isactive;
};

//Helper functions
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

//Uniforms
uniform Material material;

layout (std140) uniform LightBlock
{
	Light lights[MAX_LIGHTS];
	int numLights;	
};

//In Data
in vec2 TexCoord;

void main()
{
    if(material.colorTextureNum == 0)
    {
        FragColor = vec4(material.kColor, 1);
    }
    else
    {
        vec4 color = vec4(0, 0, 0, 0);
        for (int i = 0; i < material.colorTextureNum; i++)
        {
            vec4 textureColor = texture2D( material.colorTexture[i], TexCoord );
            if (textureColor.a < 0.1)
            {
                discard;
            }
            color += textureColor;
        }
        color = color/material.colorTextureNum;
        FragColor = color;
    }

    FragColor = FragColor * vec4(material.kAmbient, 1);

    vec3 eyeDirection_cameraspace = - vertexPosition_cameraspace;
	vec3 E = normalize(eyeDirection_cameraspace);
	vec3 N = normalize(vertexNormal_cameraspace );

    for (int i = 0; i < numLights; i++)
    {
            // // Light direction
			// float spotlightEffect = 1;
			// vec3 lightDirection_cameraspace;
			// if(lights[i].type == 1) {
			// 	lightDirection_cameraspace = lights[i].position_cameraspace;
			// }
			// else if(lights[i].type == 2) {
			// 	lightDirection_cameraspace = lights[i].position_cameraspace - vertexPosition_cameraspace;
			// 	spotlightEffect = getSpotlightEffect(lights[i], lightDirection_cameraspace);
			// }
			// else {
			// 	lightDirection_cameraspace = lights[i].position_cameraspace - vertexPosition_cameraspace;
			// }
			// // Distance to the light
			// float distance = length( lightDirection_cameraspace );
			
			// // Light attenuation
			// float attenuationFactor = getAttenuation(lights[i], distance);

			// vec3 L = normalize( lightDirection_cameraspace );
			// float cosTheta = clamp( dot( N, L ), 0, 1 );
			
			// vec3 R = reflect(-L, N);
			// float cosAlpha = clamp( dot( E, R ), 0, 1 );
			
			// FragColor += 
				
			// 	// Diffuse : "color" of the object
			// 	FragColor * vec4(material.kDiffuse, 1) * vec4(lights[i].color, 1) * lights[i].power * cosTheta * attenuationFactor * spotlightEffect +
				
			// 	// Specular : reflective highlight, like a mirror
			// 	vec4(material.kSpecular, 1) * vec4(lights[i].color, 1) * lights[i].power * pow(cosAlpha, material.kShininess) * attenuationFactor * spotlightEffect;

			FragColor = vec4(1,1,1,1);

    }

    if (FragColor.a < 0.1f)
	{
		discard;
	}
    FragDepth = gl_FragCoord.z;
}
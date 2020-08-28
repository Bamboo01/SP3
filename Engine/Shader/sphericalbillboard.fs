#version 330 core
layout(location = 0) out vec4 FragColor;
//layout(location = 1) out float FragDepth;

// Constant values
const int MAX_LIGHTS = 32; //Add a +1 for shadow light
const int MAX_TEXTURES = 8;
const int MAX_UNITS = 1000;

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

//Uniforms
uniform Material material;

layout (std140) uniform LightBlock
{
	Light lights[MAX_LIGHTS];
	int numLights;	
};

layout (std140) uniform FogOfWarBlock
{
    vec4 UnitPositions[MAX_UNITS];
    vec4 NumUnits;
};

//In Data
in vec2 TexCoord;
in vec4 fragPos;

void main()
{

    bool canSee = false;
    for (int i = 0; i < floor(NumUnits.x); i++)
    {
        if (length(UnitPositions[i] - fragPos) < 50.f)
        {
            canSee = true;
            break;
        }
    }

    if (canSee != true)
    {
        discard;
    }

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

    if (FragColor.a < 0.1f)
	{
		discard;
	}
}
#version 330 core
layout(location = 0) out vec4 FragColor;

const int MAX_TEXTURES = 8;

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

//Uniforms
uniform Material material;

in vec2 TexCoord;

void main()
{
    float depth = 50.f / (gl_FragCoord.z / gl_FragCoord.w);

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

    vec4 blacky = vec4(0, 0, 0, depth);
    FragColor = mix(FragColor, blacky, 1.f / blacky.w);
}
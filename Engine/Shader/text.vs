#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

layout (std140) uniform MatriceBlock
{
	mat4 projection;
	mat4 view;
};

out vec2 TexCoord;
uniform mat4 ModelMatrix;

void main()
{
    //TexCoord = aPos.xy * 0.5f + 0.5f;
    mat4 m = ModelMatrix;
    TexCoord = aTexCoord;
    gl_Position = projection * m * vec4(aPos.xy, 0, 1.0);
}
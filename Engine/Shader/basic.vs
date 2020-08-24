#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in mat4 aModel;

out vec2 TexCoord;
out vec3 vertexPosition_cameraspace;
out vec3 vertexNormal_cameraspace;

layout (std140) uniform MatriceBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
    mat4 MV = view *  aModel;
    mat4 MV_inverse_transpose = transpose(inverse(MV));
    vertexPosition_cameraspace = ( MV * vec4(aPos, 1) ).xyz;
    vertexNormal_cameraspace = ( MV_inverse_transpose * vec4(aPos, 0) ).xyz;

    TexCoord = aTexCoord;
    gl_Position = projection * view * aModel * vec4(aPos, 1.0f);
}

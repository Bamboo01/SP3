#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in mat4 aModel;

out vec2 TexCoord;

layout (std140) uniform MatriceBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
    mat4 modelviewmatrix = view * aModel;
    modelviewmatrix[0][0] = 1.0; 
    modelviewmatrix[0][1] = 0.0; 
    modelviewmatrix[0][2] = 0.0; 

    modelviewmatrix[1][0] = 0.0; 
    modelviewmatrix[1][1] = 1.0; 
    modelviewmatrix[1][2] = 0.0; 

    modelviewmatrix[2][0] = 0.0; 
    modelviewmatrix[2][1] = 0.0; 
    modelviewmatrix[2][2] = 1.0; 

    vec4 P = modelviewmatrix * vec4(aPos, 1);
    gl_Position = projection * P;
    TexCoord = aTexCoord;
}

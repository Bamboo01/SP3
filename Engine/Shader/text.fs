#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 TextColor;
uniform sampler2D Font;

void main()
{
    vec4 texColor = texture(Font, TexCoord);
    if (texColor.a < 0.1)
    {
        discard;
    }
    FragColor = texColor;
}    
#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 TexCoord;

void main()
{
    float depth = 50.f / (gl_FragCoord.z / gl_FragCoord.w);
    vec4 outputcolor = vec4 (1,1,1,1);
    vec4 blacky = vec4(0, 0, 0, depth);
    FragColor = mix(outputcolor, blacky, 1.f / blacky.w);
}
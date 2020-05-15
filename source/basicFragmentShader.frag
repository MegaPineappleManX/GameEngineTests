#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 light = vec4(0.33, 0.42, 0.18, 1.0);
    vec4 color = vec4(1.0, 0.5, 0.31, 1.0);
    //FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.5) ;
    FragColor = light * color;
}

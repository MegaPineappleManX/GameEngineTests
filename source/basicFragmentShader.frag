#version 330 core
out vec4 FragColor;
  
//in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = lightColor * ambientStrength;
    FragColor = vec4(ambient * objectColor, 1.0);
}

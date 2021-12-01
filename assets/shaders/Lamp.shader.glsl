#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() // Start Main
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(FragPos, 1.0);
    TexCoord = aTexCoord;
} // End Main

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

void main() // Start Main
{
    FragColor = vec4(lightColor, 1.0);
} // End Main
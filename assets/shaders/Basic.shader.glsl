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

//    =========================================================================================================

#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

#define MAX_POINT_LIGHT 10

uniform PointLight multiPointLight[MAX_POINT_LIGHT];
uniform int noOfPointLight;

uniform DirLight dirLight;
uniform Material material;

uniform vec3 viewPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform int noTex;

void main() // Start Main
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec4 diffMap;
    vec4 specMap;

    if (noTex == 1)
    {
        diffMap = material.diffuse;
        specMap = material.specular;
    }
    else
    {
        diffMap = texture(diffuse0, TexCoord);
        specMap = texture(specular0, TexCoord);
    }

    vec4 result = CalcDirLight(norm, viewDir, diffMap, specMap, FragPos, dirLight.ambient, dirLight.diffuse, dirLight.specular, dirLight.direction, material.shininess);

    for (int i = 0; i < noOfPointLight; i++)
        result += CalcPointLight(norm, viewDir, diffMap, specMap, FragPos, multiPointLight[i].ambient, multiPointLight[i].diffuse, multiPointLight[i].specular, multiPointLight[i].position, material.shininess, multiPointLight[i].k0, multiPointLight[i].k1, multiPointLight[i].k2);

    FragColor = result;
} // End Main
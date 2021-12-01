struct Material
{
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct MaterialTexture
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
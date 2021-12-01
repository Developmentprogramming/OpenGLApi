struct PointLight
{
    vec3 position;

    float k0, k1, k2;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

vec4 CalcPointLight(vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap, vec3 FragPos, vec4 lightAmbient, vec4 lightDiffuse, vec4 lightSpecular, vec3 lightPosition, float materialShininess, float k0, float k1, float k2)
{
    // Ambient Light
    vec4 ambient = lightAmbient * diffMap;

    // Diffuse Light
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = lightDiffuse * (diff * diffMap);

    // Specular Light
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec4 specular = lightSpecular * (spec * specMap);

    float dist = length(lightPosition - FragPos);
    float attenuation = 1.0 / k0 + k1 * dist + k2 * (dist * dist);

    return vec4(ambient + diffuse + specular) * attenuation;
}

struct DirLight
{
    vec3 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

vec4 CalcDirLight(vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap, vec3 FragPos, vec4 lightAmbient, vec4 lightDiffuse, vec4 lightSpecular, vec3 lightDirection, float materialShininess)
{
    // Ambient Light
    vec4 ambient = lightAmbient * diffMap;

    // Diffuse Light
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = lightDiffuse * (diff * diffMap);

    // Specular Light
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess * 128);
    vec4 specular = lightSpecular * (spec * specMap);

    return vec4(ambient + diffuse + specular);
}
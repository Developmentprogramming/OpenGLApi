struct PointLight
{
    vec3 position;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

vec4 calcPointLight(vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap, vec3 FragPos, vec4 lightAmbient, vec4 lightDiffuse, vec4 lightSpecular, vec3 lightPosition, vec4 materialAmbient, float materialShininess)
{
    // Ambient Light
    vec4 ambient = lightAmbient * materialAmbient;

    // Diffuse Light
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = lightDiffuse * (diff * diffMap);

    // Specular Light
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess * 128);
    vec4 specular = lightSpecular * (spec * specMap);

    return vec4(ambient + diffuse + specular);
}
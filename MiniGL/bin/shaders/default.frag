#version 460

in vec3 normal;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D albedo;
uniform int useTexture = 1;
uniform vec3 baseColor = vec3(.8);

void main() {
    vec3 n = normalize(normal);
    vec3 lightDir = normalize(vec3(0, -1, -1));
    float cosTheta = max(.0f, dot(n, -lightDir));
    vec3 albedoColor = useTexture != 0 ? texture(albedo, texcoord).xyz : baseColor;
    vec3 color = cosTheta * albedoColor;

    FragColor = vec4(color, 1.0);
}

#version 460

layout(location = 0) in vec3 iPos;
layout(location = 1) in vec3 iNorm;
layout(location = 2) in vec2 iTexcoord;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 position;
out vec3 normal;
out vec2 texcoord;

void main() {
    normal = mat3(transpose(inverse(modelMatrix))) * iNorm;
    texcoord = iTexcoord;
    position = vec3(modelMatrix * vec4(iPos, 1.f));
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.f);
}

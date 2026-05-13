#version 410 core

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_fragPos;

uniform sampler2D u_texture;
uniform bool u_hasTexture;
uniform vec3 u_color;
uniform bool u_isEmissive;

// lighting
uniform vec3 u_lightPos;    // sun position in world space
uniform vec3 u_viewPos;     // camera position in world space
uniform vec3 u_lightColor;  // sun color, usually white

out vec4 fragColor;

void main() {
    // get base color from texture or uniform color
    vec4 baseColor = u_hasTexture ? texture(u_texture, v_uv) : vec4(u_color, 1.0);

    if (u_isEmissive) {
        // sun just renders at full brightness
        fragColor = baseColor;
        return;
    }

    // normalize vectors
    vec3 normal = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    vec3 viewDir = normalize(u_viewPos - v_fragPos);

    // ambient — small base light so dark side isnt pitch black
    float ambientStrength = 0.05f;
    vec3 ambient = ambientStrength * u_lightColor;

    // diffuse — main lighting based on angle to sun
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    // specular — shiny highlight
    float specularStrength = 0.3f;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * u_lightColor;

    // combine
    vec3 result = (ambient + diffuse + specular) * vec3(baseColor);
    fragColor = vec4(result, 1.0);
}
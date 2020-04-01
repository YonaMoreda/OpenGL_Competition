#version 330 core

// Define constants
#define M_PI 3.141593

in vec4 material_phong;
in vec3 lightPos_phong;
in vec3 lightColor_phong;

uniform sampler2D textureSamplerPhong;

in vec3 normal;
in vec2 textureCoords;
in mat4 projectionTransformOut;
in vec3 objPosition;

out vec4 fColor;

void main()
{
    vec4 lightPosTransf = normalize(projectionTransformOut * vec4(lightPos_phong, 1));

    vec3 texColor = texture(textureSamplerPhong, textureCoords).xyz;
    vec3 ambient = material_phong.xyz * texColor;

    vec3 diffuse = texColor * max(0, dot(lightPosTransf.xyz, normal)) * material_phong.xyz * lightColor_phong;

    vec3 r = normalize(reflect(-lightPosTransf.xyz, normal));
    vec3 v = normalize(-objPosition);
    vec3 specular = pow(max(0, dot(r,v)), material_phong.w) * lightColor_phong * 0.1;

    fColor = vec4(vec3(ambient + diffuse + specular), 1.0);
}

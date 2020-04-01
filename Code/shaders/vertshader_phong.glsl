#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertColor_in;
layout (location = 2) in vec2 textureCoords_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelViewTransformPhong;
uniform mat4 projectionTransformPhong;
uniform mat3 normalTransformPhong;

//Illumination constants
uniform vec4 materialPhong;
uniform vec3 lightPosPhong;
uniform vec3 lightColorPhong;

out vec4 material_phong;
out vec3 lightPos_phong;
out vec3 lightColor_phong;

// Specify the output of the vertex stage
out vec3 normal;
out vec3 objPosition;
out mat4 projectionTransformOut;

// Textures
out vec2 textureCoords;

void main()
{
    gl_Position = projectionTransformPhong * modelViewTransformPhong * vec4(vertCoordinates_in, 1.0);
    objPosition = vec3(modelViewTransformPhong * vec4(vertCoordinates_in, 1.0F));
    normal = normalize(normalTransformPhong * vertColor_in);

    projectionTransformOut = projectionTransformPhong;

    textureCoords = textureCoords_in;

    material_phong = materialPhong;
    lightPos_phong = lightPosPhong;
    lightColor_phong = lightColorPhong;
}

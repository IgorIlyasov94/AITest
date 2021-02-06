#version 430

layout(local_size_x = 1, local_size_y = 1) in;

uniform int imageWidth;
uniform int imageHeight;

layout(rgba8, binding = 0) readonly uniform image2D inputTexture;

layout(std430, binding = 1) writeonly buffer outputBuffer
{
	vec4 textureData[];
};

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy);
	
	vec4 textureDataSample = imageLoad(inputTexture, textureCoords);
	
	textureData[textureCoords.x + textureCoords.y * imageWidth] = textureDataSample;
}

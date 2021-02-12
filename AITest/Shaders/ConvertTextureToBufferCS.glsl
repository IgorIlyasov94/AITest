#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int imageWidth;
uniform int imageHeight;

layout(rgba8, binding = 0) readonly uniform image2D inputTexture;

layout(std430, binding = 1) writeonly buffer OutputBuffer
{
	uint textureData[];
} outputBuffer;

uint PackTextureData(vec4 data)
{
	uint result = uint(data.x * 255.0f) << 24;
	result |= uint(data.y * 255.0f) << 16;
	result |= uint(data.z * 255.0f) << 8;
	result |= uint(data.w * 255.0f);
	
	return result;
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy);
	
	vec4 textureDataSample = imageLoad(inputTexture, textureCoords);
	
	int bufferCoord = textureCoords.x + textureCoords.y * imageWidth;
	
	outputBuffer.textureData[bufferCoord] = PackTextureData(textureDataSample);
}

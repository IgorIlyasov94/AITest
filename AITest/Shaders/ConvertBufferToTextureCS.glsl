#version 430

layout(local_size_x = 16) in;

uniform int imageWidth;
uniform int imageHeight;

layout(std430, binding = 0) readonly buffer InputBuffer
{
	uint TextureData[];
} inputBuffer;

layout(rgba8, binding = 1) writeonly uniform image2D outputTexture;

vec4 UnpackTextureData(uint data)
{
	vec4 result;
	
	result.x = float(data >> 24) / 255.0f;
	result.y = float((data & uint(0x00FF0000)) >> 16) / 255.0f;
	result.z = float((data & uint(0x0000FF00)) >> 8) / 255.0f;
	result.w = float(data & uint(0x000000FF)) / 255.0f;
	
	return result;
}

void main()
{
	int bufferCoord = int(gl_GlobalInvocationID.x);
	
	ivec2 textureCoords = ivec2(0, 0);
	textureCoords.y = bufferCoord / imageWidth;
	textureCoords.x = int(mod(float(bufferCoord), float(imageWidth)));
	
	vec4 textureDataSample = UnpackTextureData(inputBuffer.TextureData[bufferCoord]);
	
	imageStore(outputTexture, textureCoords, textureDataSample);
}

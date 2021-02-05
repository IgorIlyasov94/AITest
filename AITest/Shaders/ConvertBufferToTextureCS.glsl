#version 430

layout(local_size_x = 1) in;

uniform int imageWidth;
uniform int imageHeight;

layout(std430, binding = 0) buffer inputBuffer
{
	vec4 textureData[];
};

layout(rgba8, binding = 1) uniform image2D outputTexture;

void main()
{
	int bufferCoord = int(gl_GlobalInvocationID.x);
	
	ivec2 textureCoords = ivec2(0, 0);
	textureCoords.y = bufferCoord / imageWidth;
	textureCoords.x = int(mod(float(bufferCoord), float(imageWidth)));
	
	vec4 textureDataSample = textureData[bufferCoord];
	
	imageStore(outputTexture, textureCoords, textureDataSample);
}

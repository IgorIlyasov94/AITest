#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int paddingSize;

uniform float bias;

uniform mat3 kernel;

layout(r32f, binding = 0) readonly uniform image2D inputTexture;
layout(r32f, binding = 1) writeonly uniform image2D outputTexture;

float ConvolutionSample(ivec2 textureCoords, int rowId, int columnId)
{
	float textureSample = imageLoad(inputTexture, textureCoords).x;
	
	return textureSample * kernel[columnId][rowId];
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy) - paddingSize.xx + ivec2(1, 1);
	
	float sum = ConvolutionSample(textureCoords, 1, 1);
	
	sum += ConvolutionSample(textureCoords + ivec2(-1, -1), 0, 0);
	sum += ConvolutionSample(textureCoords + ivec2(0, -1), 1, 0);
	sum += ConvolutionSample(textureCoords + ivec2(1, -1), 2, 0);
	sum += ConvolutionSample(textureCoords + ivec2(-1, 0), 0, 1);
	sum += ConvolutionSample(textureCoords + ivec2(1, 0), 2, 1);
	sum += ConvolutionSample(textureCoords + ivec2(-1, 1), 0, 2);
	sum += ConvolutionSample(textureCoords + ivec2(0, 1), 1, 2);
	sum += ConvolutionSample(textureCoords + ivec2(1, 1), 2, 2);
	
	float result = sum;
	
	memoryBarrier();
	
	result += bias;
	
	imageStore(outputTexture, textureCoords, vec4(result, 0.0f, 0.0f, 0.0f));
}

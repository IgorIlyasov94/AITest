#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int paddingSize;

uniform float bias;

uniform mat4 kernel;

layout(r32f, binding = 0) readonly uniform image2DRect inputTexture;
layout(r32f, binding = 1) writeonly uniform image2DRect outputTexture;

float ConvolutionSample(ivec2 textureCoords, int rowId, int columnId)
{
	float textureSample = imageLoad(inputTexture, textureCoords + ivec2(columnId, rowId)).x;
	
	return textureSample * kernel[columnId][rowId];
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy) - paddingSize.xx;
	
	float sum = ConvolutionSample(textureCoords, 0, 0);
	sum += ConvolutionSample(textureCoords, 1, 0);
	sum += ConvolutionSample(textureCoords, 2, 0);
	sum += ConvolutionSample(textureCoords, 3, 0);
	sum += ConvolutionSample(textureCoords, 0, 1);
	sum += ConvolutionSample(textureCoords, 1, 1);
	sum += ConvolutionSample(textureCoords, 2, 1);
	sum += ConvolutionSample(textureCoords, 3, 1);
	sum += ConvolutionSample(textureCoords, 0, 2);
	sum += ConvolutionSample(textureCoords, 1, 2);
	sum += ConvolutionSample(textureCoords, 2, 2);
	sum += ConvolutionSample(textureCoords, 3, 2);
	sum += ConvolutionSample(textureCoords, 0, 3);
	sum += ConvolutionSample(textureCoords, 1, 3);
	sum += ConvolutionSample(textureCoords, 2, 3);
	sum += ConvolutionSample(textureCoords, 3, 3);
	
	float result = sum;
	
	memoryBarrier();
	
	result += bias;
	
	imageStore(outputTexture, textureCoords + paddingSize.xx + ivec2(1, 1), vec4(result, 0.0f, 0.0f, 0.0f));
}

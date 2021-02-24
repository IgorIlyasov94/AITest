#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int paddingSize;

uniform float bias;

uniform mat4 kernel;

layout(r32f, binding = 0) readonly uniform image2DRect inputTexture;
layout(r32f, binding = 1) writeonly uniform image2DRect outputTexture;

const int KERNEL_ROW_NUMBER = 4;
const int KERNEL_COLUMN_NUMBER = 4;

float ConvolutionSample(ivec2 textureCoords, int rowId, int columnId)
{
	float textureSample = imageLoad(inputTexture, textureCoords + ivec2(columnId, rowId)).x;
	
	return textureSample * kernel[columnId][rowId];
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy) - paddingSize.xx;
	
	float sum = 0.0f;
	
	for (int columnId = 0; columnId < KERNEL_COLUMN_NUMBER; columnId++)
		for (int rowId = 0; rowId < KERNEL_ROW_NUMBER; rowId++)
			sum += ConvolutionSample(textureCoords, rowId, columnId);
	
	float result = sum;
	
	memoryBarrier();
	
	result += bias;
	
	imageStore(outputTexture, textureCoords + paddingSize.xx + ivec2(1, 1), vec4(result, 0.0f, 0.0f, 0.0f));
}

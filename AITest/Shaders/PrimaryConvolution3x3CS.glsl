#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int paddingSize;

uniform float bias;

uniform mat3 kernelR;
uniform mat3 kernelG;
uniform mat3 kernelB;

layout(rgba8, binding = 0) readonly uniform image2DRect inputTexture;
layout(r32f, binding = 1) writeonly uniform image2DRect outputTexture;

const int KERNEL_ROW_NUMBER = 3;
const int KERNEL_COLUMN_NUMBER = 3;

vec3 ConvolutionSample(ivec2 textureCoords, int rowId, int columnId)
{
	vec3 textureSample = imageLoad(inputTexture, textureCoords + ivec2(columnId - 1, rowId - 1)).xyz;
	vec3 rgbKernel = vec3(kernelR[columnId][rowId], kernelG[columnId][rowId], kernelB[columnId][rowId]);
	
	return textureSample * rgbKernel;
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy) - paddingSize.xx + ivec2(1, 1);
	
	vec3 sum = 0.0f.xxx;
	
	for (int columnId = 0; columnId < KERNEL_COLUMN_NUMBER; columnId++)
		for (int rowId = 0; rowId < KERNEL_ROW_NUMBER; rowId++)
			sum += ConvolutionSample(textureCoords, rowId, columnId);
	
	float result = dot(sum, 1.0f.xxx);
	
	memoryBarrier();
	
	result += bias;
	
	imageStore(outputTexture, textureCoords + paddingSize.xx - ivec2(1, 1), vec4(result, 0.0f, 0.0f, 0.0f));
}

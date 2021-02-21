#version 430

layout(local_size_x = 16, local_size_y = 16) in;

uniform int paddingSize;

uniform float bias;

uniform mat3 kernelR;
uniform mat3 kernelG;
uniform mat3 kernelB;

layout(rgba8, binding = 0) readonly uniform image2D inputTexture;
layout(r32f, binding = 1) writeonly uniform image2D outputTexture;

vec3 ConvolutionSample(ivec2 textureCoords, int rowId, int columnId)
{
	vec3 textureSample = imageLoad(inputTexture, textureCoords).xyz;
	vec3 rgbKernel = vec3(kernelR[columnId][rowId], kernelG[columnId][rowId], kernelB[columnId][rowId]);
	
	return textureSample * rgbKernel;
}

void main()
{
	ivec2 textureCoords = ivec2(gl_GlobalInvocationID.xy) - paddingSize.xx + ivec2(1, 1);
	
	vec3 sum = ConvolutionSample(textureCoords, 1, 1);
	
	sum += ConvolutionSample(textureCoords + ivec2(-1, -1), 0, 0);
	sum += ConvolutionSample(textureCoords + ivec2(0, -1), 1, 0);
	sum += ConvolutionSample(textureCoords + ivec2(1, -1), 2, 0);
	sum += ConvolutionSample(textureCoords + ivec2(-1, 0), 0, 1);
	sum += ConvolutionSample(textureCoords + ivec2(1, 0), 2, 1);
	sum += ConvolutionSample(textureCoords + ivec2(-1, 1), 0, 2);
	sum += ConvolutionSample(textureCoords + ivec2(0, 1), 1, 2);
	sum += ConvolutionSample(textureCoords + ivec2(1, 1), 2, 2);
	
	float result = dot(sum, 1.0f.xxx);
	
	memoryBarrier();
	
	result += bias;
	
	imageStore(outputTexture, textureCoords + paddingSize.xx - ivec2(1, 1), vec4(result, 0.0f, 0.0f, 0.0f));
}

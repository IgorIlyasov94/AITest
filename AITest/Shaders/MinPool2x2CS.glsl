#version 430

layout(local_size_x = 16, local_size_y = 16) in;

layout(r32f, binding = 0) readonly uniform image2DRect inputTexture;
layout(r32f, binding = 1) writeonly uniform image2DRect outputTexture;

void main()
{
	ivec2 inputTextureCoords = ivec2(gl_GlobalInvocationID.xy);
	ivec2 outputTextureCoords = inputTextureCoords;
	inputTextureCoords *= 2;
	
	float sample00 = imageLoad(inputTexture, inputTextureCoords).x;
	float sample01 = imageLoad(inputTexture, inputTextureCoords + ivec2(0, 1)).x;
	float sample10 = imageLoad(inputTexture, inputTextureCoords + ivec2(1, 0)).x;
	float sample11 = imageLoad(inputTexture, inputTextureCoords + ivec2(1, 1)).x;
	
	float result = min(min(sample00, sample01), min(sample10, sample11));
	
	imageStore(outputTexture, outputTextureCoords, vec4(result, 0.0f, 0.0f, 0.0f));
}

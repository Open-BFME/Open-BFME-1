void bfmeUnpackTwoColors1280(float *output, const unsigned int *colors)
{
	const float scale = 1.0f / 255.0f;
	const unsigned char *bytes = (const unsigned char *)colors;
	output[0] = (float)bytes[3] * scale;
	output[1] = (float)bytes[2] * scale;
	output[2] = (float)bytes[1] * scale;
	output[3] = (float)(colors[0] & 0xff) * scale;
	output[4] = (float)bytes[7] * scale;
	output[5] = (float)bytes[6] * scale;
	output[6] = (float)bytes[5] * scale;
	output[7] = (float)(colors[1] & 0xff) * scale;
}

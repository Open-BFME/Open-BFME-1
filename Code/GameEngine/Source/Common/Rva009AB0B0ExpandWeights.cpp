// Open-BFME5 conversion of the codec's eleven-byte weight expansion.

void Rva009AB0B0ExpandWeights(const unsigned char *input, unsigned int *output)
{
	unsigned int factor01 = ((unsigned int)input[0] * input[1]) >> 8;
	output[11] = factor01;

	unsigned int factor0 = ((unsigned int)input[0] * (0xff - input[1])) >> 8;
	output[0] = factor0;

	unsigned int inverse0 = 0xff - input[0];
	output[1] = ((unsigned int)input[2] * inverse0) >> 8;

	unsigned int factor3 = ((0xff - input[2]) * inverse0) >> 8;
	unsigned int value3 = ((unsigned int)input[3] * factor3) >> 8;
	unsigned int value4 = ((unsigned int)input[4] * value3) >> 8;
	output[2] = value4;

	unsigned int factor5 = ((0xff - input[4]) * value3) >> 8;
	unsigned int value5 = ((unsigned int)input[5] * factor5) >> 8;
	output[3] = value5;
	unsigned int value6 = ((0xff - input[5]) * factor5) >> 8;
	output[4] = value6;

	unsigned int factor6 = ((0xff - input[3]) * factor3) >> 8;
	unsigned int value7 = ((unsigned int)input[6] * factor6) >> 8;
	unsigned int value8 = ((unsigned int)input[7] * value7) >> 8;
	output[5] = value8;
	unsigned int value9 = ((0xff - input[7]) * value7) >> 8;
	output[6] = value9;

	unsigned int factor8 = ((0xff - input[6]) * factor6) >> 8;
	unsigned int value10 = ((unsigned int)input[8] * factor8) >> 8;
	unsigned int value11 = ((unsigned int)input[9] * value10) >> 8;
	output[7] = value11;
	unsigned int value12 = ((0xff - input[9]) * value10) >> 8;
	output[8] = value12;

	unsigned int factor10 = ((0xff - input[8]) * factor8) >> 8;
	unsigned int value13 = ((unsigned int)input[10] * factor10) >> 8;
	output[9] = value13;
	unsigned int value14 = ((0xff - input[10]) * factor10) >> 8;
	output[10] = value14;
}

void __cdecl Rva009AB200BuildWeights(
	unsigned char *source,
	int *destination)
{
	unsigned int factor = source[0] * source[1];
	factor >>= 8;
	unsigned int result = source[2] * factor;
	result >>= 8;
	destination[0] = result;

	{
		unsigned int inverse = 0xFF - source[2];
		inverse *= factor;
		inverse >>= 8;
		destination[1] = inverse;
	}

	{
		unsigned int inverse = 0xFF - source[1];
		inverse *= source[0];
		inverse >>= 8;
		unsigned int result = source[3] * inverse;
		result >>= 8;
		destination[2] = result;
		result = (0xFF - source[3]) * inverse;
		result >>= 8;
		destination[3] = result;
	}

	{
		unsigned int factor = (0xFF - source[0]) * source[4];
		factor >>= 8;
		factor *= source[5];
		factor >>= 8;
		unsigned int result = source[6] * factor;
		result >>= 8;
		destination[4] = result;
		result = (0xFF - source[6]) * factor;
		result >>= 8;
		destination[5] = result;
	}

	{
		unsigned int factor = (0xFF - source[0]) * source[4];
		factor >>= 8;
		factor *= 0xFF - source[5];
		factor >>= 8;
		unsigned int result = source[7] * factor;
		result >>= 8;
		destination[6] = result;
		result = (0xFF - source[7]) * factor;
		result >>= 8;
		destination[7] = result;
	}

	destination[8] = ((unsigned int)(0xFF - source[0]) *
		(unsigned int)(0xFF - source[4])) >> 8;
}

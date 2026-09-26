// One more: a fill check that masks the last partial word.

unsigned char bfmeAllSame(const unsigned int *data, unsigned int value, unsigned int bytes)
{
	while (bytes > 3)
	{
		if (*data != value)
			return 0;
		bytes -= 4;
		++data;
	}

	if (bytes != 0)
	{
		unsigned int mask = 0xFFFFFFFF >> ((4 - bytes) * 8);
		if ((*data & mask) != (value & mask))
			return 0;
	}
	return 1;
}

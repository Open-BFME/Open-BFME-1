// A header read out of six bytes.

unsigned int bfmeReadYU(const unsigned char *data)
{
	unsigned int tag = ((unsigned int)data[0] << 8) | data[1];

	if (tag == 0x15FB)
	{
		unsigned int value = ((unsigned int)data[2] << 8) | data[3];

		value = (value << 8) | data[4];
		value = (value << 8) | data[5];

		return value;
	}

	return 0;
}

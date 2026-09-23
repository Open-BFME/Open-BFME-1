// Retail 0x0013A070, 53 bytes: sums a little-endian byte run into an int.
// Identity unproven (one caller via ILT thunk 0x00028911), so the name keeps
// the address token.

int readLittleEndian0013A070(const unsigned char *bytes, int count)
{
	int value = 0;
	int scale = 1;

	for (int i = 0; i < count; i++)
	{
		value += bytes[i] * scale;
		scale *= 256;
	}

	return value;
}

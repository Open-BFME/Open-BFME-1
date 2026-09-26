// Retail 0x00368AF0 scans the low seven mask bits and returns their first set index.
struct Rva00368AF0BitMask
{
	unsigned int bits;
	int firstSet() const;
};

int Rva00368AF0BitMask::firstSet() const
{
	for (int index = 0; index < 7; ++index)
	{
		if (bits & (1u << (index & 31)))
			return index;
	}
	return -1;
}

class Rva005A31A0Object
{
public:
	int test(unsigned char index, unsigned int mask);
};

int Rva005A31A0Object::test(unsigned char index, unsigned int mask)
{
	const unsigned int value = *reinterpret_cast<const unsigned short *>(
		reinterpret_cast<const unsigned char *>(this) + 0x1a + index * 8);
	return (value & mask) != 0;
}

class Rva005A31C0Object
{
public:
	int test(unsigned char index);
};

int Rva005A31C0Object::test(unsigned char index)
{
	return (*(reinterpret_cast<const unsigned char *>(this) + 0x1a + index * 8) >> 1) & 1;
}

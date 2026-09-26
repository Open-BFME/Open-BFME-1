class Rva005A3190Object
{
public:
	unsigned char get(unsigned char index);
};

unsigned char Rva005A3190Object::get(unsigned char index)
{
	return *(reinterpret_cast<unsigned char *>(this) + 0x19 + index * 8);
}

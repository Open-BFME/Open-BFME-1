class Rva005A31E0Object
{
public:
	unsigned int get(unsigned char index);
};

unsigned int Rva005A31E0Object::get(unsigned char index)
{
	return *reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 0x1c + index * 8);
}

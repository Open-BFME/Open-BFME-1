class Rva001EB070Object
{
public:
	unsigned char *at(unsigned int index);
};

unsigned char *Rva001EB070Object::at(unsigned int index)
{
	return reinterpret_cast<unsigned char *>(this) + 0x28 + index * 24;
}

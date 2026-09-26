class Rva005A3210Object
{
public:
	void set(unsigned char index, unsigned char value);
};

void Rva005A3210Object::set(unsigned char index, unsigned char value)
{
	*reinterpret_cast<unsigned short *>(reinterpret_cast<unsigned char *>(this) + 0x1a + index * 8) = value;
}

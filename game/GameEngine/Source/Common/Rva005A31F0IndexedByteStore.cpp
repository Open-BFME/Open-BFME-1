class Rva005A31F0Object
{
public:
	void set(unsigned char index, unsigned char value);
};

void Rva005A31F0Object::set(unsigned char index, unsigned char value)
{
	*(reinterpret_cast<unsigned char *>(this) + 0x19 + index * 8) = value;
}

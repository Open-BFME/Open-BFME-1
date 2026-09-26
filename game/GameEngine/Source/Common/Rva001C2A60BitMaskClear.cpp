class Rva001C2A60
{
public:
	unsigned char unused[8];
	unsigned int value;
	void clear();
};

void Rva001C2A60::clear()
{
	value &= 0x003FFFFF;
}

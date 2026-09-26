// Retail 0x006BE020 returns the dword at offset 0x10.

struct Rva006BE020Object
{
	int getValue() const;
};

int Rva006BE020Object::getValue() const
{
	return *(const int *)((const char *)this + 0x10);
}

// Retail 0x00200B90 returns the dword at offset 0x04.

struct Rva00200B90DwordGetter
{
	int get() const;
};

int Rva00200B90DwordGetter::get() const
{
	return *(const int *)((const char *)this + 4);
}

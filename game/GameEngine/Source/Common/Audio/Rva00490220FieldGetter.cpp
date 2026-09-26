// Retail 0x00490220 returns the dword at offset 0x04.

struct Rva00490220FieldGetter
{
	int get() const;
};

int Rva00490220FieldGetter::get() const
{
	return *(const int *)((const char *)this + 4);
}

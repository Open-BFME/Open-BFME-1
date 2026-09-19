// Retail 0x003BCD90 returns the first dword of an opaque object.

struct Rva003BCD90Owner
{
	int first() const;
};

int Rva003BCD90Owner::first() const
{
	return *(const int *)this;
}

// Retail reads a dword through the pointer at this-0x340 and returns its
// value at offset 0x88. No caller or table proves the owning class.

class Rva002C8540DwordGetter
{
public:
	int get() const;
};

int Rva002C8540DwordGetter::get() const
{
	const char *base = *(const char *const *)( (const char *)this - 0x340 );
	return *(const int *)( base + 0x88 );
}

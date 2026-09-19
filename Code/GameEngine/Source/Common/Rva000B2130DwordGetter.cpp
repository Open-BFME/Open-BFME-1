// Retail RVA 0x000B2130 returns the dword at offset 0x5C.
// The carved boundary proves the field offset, but no evidence names its
// owning class.

class Rva000B2130DwordField
{
public:
	unsigned int get() const;
};

unsigned int Rva000B2130DwordField::get() const
{
	return *(const unsigned int *)((const char *)this + 0x5C);
}

// Retail returns the dword at this+0x3c at 0x007E4750. No caller proves the
// owning class or the semantic field name.

class Rva007E4750GetOffset3C
{
public:
	int get();
};

int Rva007E4750GetOffset3C::get()
{
	return *(const int *)((const char *)this + 0x3c);
}

// cl: /O2
// Retail 0x006959B0 returns the dword at this+0x64.  No caller or identity
// table proves a semantic owner, so the class name remains address-derived.
class Rva006959B0Owner
{
public:
	__declspec(noinline) int get() const;

	char fields[0x64];
	int value;
};

__declspec(noinline) int Rva006959B0Owner::get() const
{
	return value;
}

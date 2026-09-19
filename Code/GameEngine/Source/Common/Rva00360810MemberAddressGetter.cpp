// cl: /O2 /Ob0

// Retail 0x00360810 returns the address at this+0x94. The carved boundary and
// ILT route prove the accessor shape, but no evidence names the owning class.

class Rva00360810MemberAddressGetter
{
public:
	void *get() const;
};

void *Rva00360810MemberAddressGetter::get() const
{
	return reinterpret_cast<char *>(const_cast<Rva00360810MemberAddressGetter *>(this)) + 0x94;
}

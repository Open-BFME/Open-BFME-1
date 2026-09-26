// Retail at 0x005A7360 returns the address of the member at this+0x128.
// The owning type and member semantics were not recovered.
class Rva005A7360MemberAddressGetter
{
public:
	int &get();

private:
	char m_padding[0x128];
	int m_value;
};

int &Rva005A7360MemberAddressGetter::get()
{
	return m_value;
}

// Retail at 0x005A73B0 returns the address of the member at this+0x2E8.
// The owning type and member semantics were not recovered.
class Rva005A73B0MemberAddressGetter
{
public:
    int &get();

private:
    char m_padding[0x2E8];
    int m_value;
};

int &Rva005A73B0MemberAddressGetter::get()
{
    return m_value;
}

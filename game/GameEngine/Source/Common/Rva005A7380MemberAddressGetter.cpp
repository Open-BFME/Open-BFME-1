// Retail at 0x005A7380 returns the address of the member at this+0x198.
// The owning type and member semantics were not recovered.
class Rva005A7380MemberAddressGetter
{
public:
    int &get();

private:
    char m_padding[0x198];
    int m_value;
};

int &Rva005A7380MemberAddressGetter::get()
{
    return m_value;
}

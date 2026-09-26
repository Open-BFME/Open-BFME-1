// Retail at 0x000C9CE0 returns the unsigned word at this+0x344.
// The owning type and field semantics were not recovered.
class Rva000C9CE0WordGetter
{
public:
    unsigned short get() const;

private:
    unsigned char m_padding[0x344];
    unsigned short m_value;
};

unsigned short Rva000C9CE0WordGetter::get() const
{
    return m_value;
}

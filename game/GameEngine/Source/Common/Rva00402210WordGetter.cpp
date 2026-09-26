// Retail at 0x00402210 returns the unsigned word at this+0x30.
// The owning type and field semantics were not recovered.
class Rva00402210WordGetter
{
public:
    unsigned short get() const;

private:
    unsigned char m_padding[0x30];
    unsigned short m_value;
};

unsigned short Rva00402210WordGetter::get() const
{
    return m_value;
}

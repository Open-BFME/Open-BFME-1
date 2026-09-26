// Retail at 0x00402200 loads the word at this+0x0A and returns it in AX.
// The owning type and field semantics were not recovered.
class Rva00402200WordGetter
{
public:
    unsigned short get() const;

private:
    unsigned char m_padding[0x0A];
    unsigned short m_value;
};

unsigned short Rva00402200WordGetter::get() const
{
    return m_value;
}

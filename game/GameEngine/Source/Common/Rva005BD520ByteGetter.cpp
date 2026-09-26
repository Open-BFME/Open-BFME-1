// Retail at 0x005BD520 loads the byte at this+0x1AB and returns.
// The owning type and field semantics were not recovered.
class Rva005BD520ByteGetter
{
public:
    unsigned char get() const;

private:
    unsigned char m_padding[0x1AB];
    unsigned char m_value;
};

unsigned char Rva005BD520ByteGetter::get() const
{
    return m_value;
}

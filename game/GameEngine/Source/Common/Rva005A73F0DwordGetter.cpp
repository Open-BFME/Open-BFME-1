// Retail at 0x005A73F0 loads the dword at this+0x434 and returns.
// The owning type and field semantics were not recovered.
class Rva005A73F0DwordGetter
{
public:
    unsigned int get() const;

private:
    unsigned char m_padding[0x434];
    unsigned int m_value;
};

unsigned int Rva005A73F0DwordGetter::get() const
{
    return m_value;
}

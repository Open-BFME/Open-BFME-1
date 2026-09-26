// Retail at 0x004708F0 is mov ax, word ptr [ecx+0x12]; ret.
// The owning type and field semantics were not recovered.
class Rva004708F0WordGetter
{
public:
    unsigned short get() const;

private:
    char m_padding[0x12];
    unsigned short m_value;
};

unsigned short Rva004708F0WordGetter::get() const
{
    return m_value;
}

// cl: /DNDEBUG /MD /EHsc

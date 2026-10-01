// Independent address views; no common native owner or field meaning is proven.
// Retail 0x00955AE0: 15 bytes, RET 4; INT3 at 0x00955AEF.
// Retail 0x00955AF0: 33 bytes, RET 4; INT3 begins at 0x00955B11.
// Both receive ECX plus one output pointer, copy physical 32-bit words,
// and leave that pointer in EAX. The original declared return and word types
// are unproven; these views preserve that physical result without naming it.
class Rva00955AE0
{
public:
    unsigned int *method(unsigned int *output) const;
private:
    unsigned char m_before00EC[0xEC];
    unsigned int m_at00EC;
};
unsigned int *Rva00955AE0::method(unsigned int *output) const
{
    *output = m_at00EC;
    return output;
}
class Rva00955AF0
{
public:
    unsigned int *method(unsigned int *output) const;
private:
    unsigned char m_before00F4[0xF4];
    unsigned int m_at00F4;
    unsigned int m_at00F8;
    unsigned int m_at00FC;
};
unsigned int *Rva00955AF0::method(unsigned int *output) const
{
    output[0] = m_at00F4;
    output[1] = m_at00F8;
    output[2] = m_at00FC;
    return output;
}

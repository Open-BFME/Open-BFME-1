// Retail at 0x00673830 is movzx eax, word ptr [ecx+0x1c]; ret.
// The owning type and field semantics were not recovered.
class Rva00673830Holder
{
public:
    unsigned int get();

private:
    char m_padding[0x1c];
    unsigned short m_value;
};

unsigned int Rva00673830Holder::get()
{
    return m_value;
}

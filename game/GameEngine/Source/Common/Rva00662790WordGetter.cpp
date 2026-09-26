// Retail at 0x00662790 is movzx eax, word ptr [ecx+0x10]; ret.
// The owning type and field semantics were not recovered.
class Rva00662790Holder
{
public:
    unsigned int get();

private:
    char m_padding[0x10];
    unsigned short m_value;
};

unsigned int Rva00662790Holder::get()
{
    return m_value;
}

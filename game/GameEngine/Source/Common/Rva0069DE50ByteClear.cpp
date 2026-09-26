// Retail at 0x0069DE50 is mov eax, ecx; mov byte ptr [eax+8], 0; ret.
// The owning type and field semantics were not recovered.
struct Rva0069DE50Holder
{
    unsigned int m_first;
    unsigned int m_second;
    unsigned char m_value;

    Rva0069DE50Holder *clear();
};

Rva0069DE50Holder *Rva0069DE50Holder::clear()
{
    m_value = 0;
    return this;
}

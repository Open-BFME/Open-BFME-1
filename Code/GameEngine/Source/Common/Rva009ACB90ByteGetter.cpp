// cl: /DNDEBUG /MD /EHsc
// RVA 0x009ACB90: read the byte at context offset 0x1AC.
// Retail places this function after the 0x009ACB80 setter and an int3 byte.
struct Rva009ACB90Context
{
    unsigned char m_pad[0x1AC];
    unsigned char m_byte;
};

unsigned char __cdecl Rva009ACB90GetByte(const Rva009ACB90Context *context)
{
    return context->m_byte;
}

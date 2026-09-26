// cl: /DNDEBUG /MD /EHsc
// RVA 0x009ACB80: write the byte at context offset 0x1AC.
// The previous 27-byte dump extent crossed an int3 into a second function.
struct Rva009ACB80Context
{
    unsigned char m_pad[0x1AC];
    unsigned char m_byte;
};

void __cdecl Rva009ACB80SetByte(Rva009ACB80Context *context, unsigned char value)
{
    context->m_byte = value;
}

// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail byte setter at 0x005A7340.
// The complete body is `mov byte ptr [ecx+0x4D],1 / ret`; the original
// member identity is not recoverable from the bytes, so the layout is
// explicit and the class name is derived from the retail address.
struct Rva005A7340ByteSetter
{
    unsigned char m_padding[0x4D];
    unsigned char m_value;

    void set();
};

void Rva005A7340ByteSetter::set()
{
    m_value = 1;
}

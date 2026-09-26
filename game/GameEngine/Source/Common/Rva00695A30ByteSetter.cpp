// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail byte setter at 0x00695A30.
// The complete body is `mov byte ptr [ecx+0x45],1 / ret`; the original
// member identity is not recoverable from the bytes, so the layout is
// explicit and the class name is derived from the retail address.
struct Rva00695A30ByteSetter
{
    unsigned char m_padding[0x45];
    unsigned char m_value;

    void set();
};

void Rva00695A30ByteSetter::set()
{
    m_value = 1;
}

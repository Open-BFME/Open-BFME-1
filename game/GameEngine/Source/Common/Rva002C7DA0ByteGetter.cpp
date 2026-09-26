// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail FUN_006c7da0 at 0x002C7DA0.
// The complete body is `mov al,[ecx+0xD6] / ret`; the original member
// identity is not recoverable from the bytes, so the layout is explicit and
// the class name is derived from the retail address.
class Rva002C7DA0Holder
{
public:
    unsigned char get() const;

private:
    char m_padding[0xD6];
    unsigned char m_value;
};

unsigned char Rva002C7DA0Holder::get() const
{
    return m_value;
}

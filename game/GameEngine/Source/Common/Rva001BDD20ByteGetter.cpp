// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail byte getter at 0x001BDD20.
// The complete body is `mov al,[ecx+0x17634] / ret`; the original member
// identity is not recoverable from the bytes, so the layout is explicit and
// the class name is derived from the retail address.
class Rva001BDD20Holder
{
public:
    unsigned char get() const;

private:
    char m_padding[0x17634];
    unsigned char m_value;
};

unsigned char Rva001BDD20Holder::get() const
{
    return m_value;
}

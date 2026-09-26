// Open-BFME5: clean C++ lift of retail FUN_004b2170 at 0x000B2170.
//
// The complete retail body is `mov al,[ecx+0x143] / ret`.  The original
// member identity is not recoverable from those bytes, so the layout and
// address-derived class name intentionally record only that observable
// behavior.
class Rva000B2170Holder
{
public:
    char get() const;

private:
    char m_padding[0x143];
    char m_value;
};

char Rva000B2170Holder::get() const
{
    return m_value;
}

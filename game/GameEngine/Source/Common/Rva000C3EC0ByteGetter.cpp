// Open-BFME5: clean C++ lift of retail FUN_004c3ec0 at 0x000C3EC0.
//
// The complete retail body is `mov al,[ecx+0x4CA] / ret`.  The original
// member identity is not recoverable from those bytes, so the layout and
// address-derived class name intentionally record only that observable
// behavior.
class Rva000C3EC0Holder
{
public:
    char get() const;

private:
    char m_padding[0x4CA];
    char m_value;
};

char Rva000C3EC0Holder::get() const
{
    return m_value;
}

// Open-BFME5: clean C++ lift of retail FUN_0047c570 at 0x0007C570.
//
// The complete retail body is `mov al,[ecx+0x16EE] / ret`.  The original
// member identity is not recoverable from those bytes, so the layout and
// address-derived class name intentionally record only that observable
// behavior.
class Rva0007C570Holder
{
public:
    char get() const;

private:
    char m_padding[0x16EE];
    char m_value;
};

char Rva0007C570Holder::get() const
{
    return m_value;
}

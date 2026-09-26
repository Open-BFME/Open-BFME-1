// cl: /O2 /DNDEBUG /MD
// Retail 0x00944B20 is mov eax,[ecx]; ret, bracketed by padding.
// No semantic identity or pointer interpretation is asserted.
class Rva00944B20
{
public:
    unsigned int readWord() const;
private:
    unsigned int m_00;
};
unsigned int Rva00944B20::readWord() const { return m_00; }

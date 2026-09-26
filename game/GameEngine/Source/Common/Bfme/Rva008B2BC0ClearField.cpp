// Retail vtable entry at VA 0x01136A28 points to RVA 0x008B2BC0.
// The following slots point to the matched 0x00899460 / 0x008994B0 /
// 0x008994D0 family. No semantic class or field identity is established.
// Padding proves the start; mov [ecx+0x20],0 followed by ret is all 8 bytes.

class Rva008B2BC0
{
public:
    void clearField();

private:
    unsigned char m_unmodelled_00[0x20];
    unsigned m_20;
};

void Rva008B2BC0::clearField()
{
    m_20 = 0;
}

// cl: /MD
struct Rva00749B90Bytes {
    unsigned char *m_begin;
    unsigned char *m_end;
    unsigned size() const { return (unsigned)(m_end - m_begin); }
    unsigned char &operator[](int index) { return m_begin[index]; }
};
class Rva00749B90 {
public:
    void setBit(int x, int y, char value);
    char m_pad[8];
    int m_width;
    int m_height;
    char m_pad2[0x24];
    int m_pitch;
    char m_pad3[0x48];
    Rva00749B90Bytes m_bits;
};
// ?setBit@Rva00749B90@@QAEXHHD@Z
// Open BFME 2: Code/GameEngine/Source/Common/Rva000AD9ABFinish.cpp.
void Rva00749B90::setBit(int x, int y, char value) {
    int xx = x;
    if (xx < 0) return;
    if (y < 0) return;
    if (y >= m_height) return;
    if (xx >= m_width) return;
    int index = m_pitch * y + (xx >> 3);
    int size = (int)m_bits.size();
    if ((unsigned)index >= (unsigned)size) return;
    unsigned char current = m_bits[index];
    unsigned char mask = (unsigned char)(1 << (xx & 7));
    if (value) current |= mask;
    else current &= (unsigned char)~mask;
    m_bits[index] = current;
}

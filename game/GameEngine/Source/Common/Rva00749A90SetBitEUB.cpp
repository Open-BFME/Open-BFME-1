// cl: /MD
struct Rva00749A90Bytes {
    unsigned char *m_bfmeBeginEUB;
    unsigned char *m_bfmeEndEUB;
    unsigned size() const { return (unsigned)(m_bfmeEndEUB - m_bfmeBeginEUB); }
    unsigned char &operator[](int index) { return m_bfmeBeginEUB[index]; }
};
class BfmeMaskEUB {
public:
    void bfmeSetBitEUB(int x, int y, char set);
    char m_bfmeHeadEUB[8];
    int m_bfmeWEUB;
    int m_bfmeHEUB;
    char m_bfmePadAEUB[0x24];
    int m_bfmePitchEUB;
    Rva00749A90Bytes m_bfmeBitsEUB;
};
// ?bfmeSetBitEUB@BfmeMaskEUB@@QAEXHHD@Z
// Open BFME 2: Code/GameEngine/Source/Common/Rva000AD9ABFinish.cpp.
void BfmeMaskEUB::bfmeSetBitEUB(int x, int y, char set) {
    int xx = x;
    if (xx < 0) return;
    if (y < 0) return;
    if (y >= m_bfmeHEUB) return;
    if (xx >= m_bfmeWEUB) return;
    int index = m_bfmePitchEUB * y + (xx >> 3);
    int size = (int)m_bfmeBitsEUB.size();
    if ((unsigned)index >= (unsigned)size) return;
    unsigned char current = m_bfmeBitsEUB[index];
    unsigned char mask = (unsigned char)(1 << (xx & 7));
    if (set) current |= mask;
    else current &= (unsigned char)~mask;
    m_bfmeBitsEUB[index] = current;
}

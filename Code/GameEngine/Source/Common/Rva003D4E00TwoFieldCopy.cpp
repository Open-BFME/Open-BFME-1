// Open-BFME: two-field copy reconstructed from retail RVA 0x003D4E00.

struct Rva003D4E00Pair
{
    int first;
    int second;
};

class Rva003D4E00Source
{
public:
    void copyTo(Rva003D4E00Pair* output);

private:
    unsigned char m_padding[0x2362C];
    int m_first;
    int m_second;
};

void Rva003D4E00Source::copyTo(Rva003D4E00Pair* output)
{
    output->first = m_first;
    output->second = m_second;
}

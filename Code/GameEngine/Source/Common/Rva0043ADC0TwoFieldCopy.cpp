// Open-BFME: two-field copy reconstructed from retail RVA 0x0043ADC0.

struct Rva0043ADC0Pair
{
    int first;
    int second;
};

class Rva0043ADC0Source
{
public:
    void copyTo(Rva0043ADC0Pair* output);

private:
    unsigned char m_padding[0x830];
    int m_first;
    int m_second;
};

void Rva0043ADC0Source::copyTo(Rva0043ADC0Pair* output)
{
    output->first = m_first;
    output->second = m_second;
}

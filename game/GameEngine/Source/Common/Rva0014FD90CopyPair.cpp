// Open-BFME: two-word field copy reconstructed from retail RVA 0x0014FD90.

struct Rva0014FD90Pair
{
    int m_first;
    int m_second;
};

class Rva0014FD90CopySource
{
public:
    void copyTo(Rva0014FD90Pair *output);

private:
    unsigned char m_padding[0x320];
    int m_first;
    int m_second;
};

void Rva0014FD90CopySource::copyTo(Rva0014FD90Pair *output)
{
    output->m_first = m_first;
    output->m_second = m_second;
}

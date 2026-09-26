// Open-BFME: clamped integer increment reconstructed from retail RVA 0x0039B820.

class Rva0039B820Accumulator
{
public:
    void adjust(int delta);

private:
    unsigned char m_padding[4];
    int m_value;
};

void Rva0039B820Accumulator::adjust(int delta)
{
    m_value += delta;
    if (m_value < 0)
        m_value = 0;
}

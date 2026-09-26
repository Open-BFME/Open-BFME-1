// cl: /O2 /MD

class Rva008C4510Bits
{
    unsigned char m_prefix[10];
    short m_rva008C4510Bits;

public:
    int maskBitRva008C4510(unsigned int bit) const;
};

int Rva008C4510Bits::maskBitRva008C4510(unsigned int bit) const
{
    return m_rva008C4510Bits & (1U << bit);
}

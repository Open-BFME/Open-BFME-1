class Rva00433760WrappedIndex {
public:
    int remainder(int value) const;

private:
    unsigned char m_prefix[0x24];
    int m_divisor;
    unsigned char m_middle[0x14];
    int m_base;
};

int Rva00433760WrappedIndex::remainder(int value) const
{
    return (m_base + value) % m_divisor;
}

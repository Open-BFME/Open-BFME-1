class Rva13E990BitTest
{
public:
    bool test(unsigned int bit) const;

private:
    unsigned int m_bits;
};

// ?d_0013e990@@YAXXZ
bool Rva13E990BitTest::test(unsigned int bit) const
{
    return (m_bits & (1U << (bit & 31))) != 0;
}

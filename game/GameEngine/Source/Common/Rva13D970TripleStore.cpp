class Rva13D970TripleStore
{
public:
    void store(unsigned int first, unsigned int second, unsigned int third);

private:
    unsigned int m_first;
    unsigned int m_second;
    unsigned int m_third;
};

// ?d_0013d970@@YAXXZ
void Rva13D970TripleStore::store(unsigned int first, unsigned int second, unsigned int third)
{
    m_first = first;
    m_second = second;
    m_third = third;
}

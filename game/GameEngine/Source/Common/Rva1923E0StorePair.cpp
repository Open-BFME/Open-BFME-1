class Rva1923E0StorePair
{
public:
    Rva1923E0StorePair *store(unsigned int *word, unsigned char *byte);

private:
    unsigned int m_word;
    unsigned char m_byte;
};

// ?d_001923e0@@YAXXZ
Rva1923E0StorePair *Rva1923E0StorePair::store(unsigned int *word, unsigned char *byte)
{
    m_word = *word;
    m_byte = *byte;
    return this;
}

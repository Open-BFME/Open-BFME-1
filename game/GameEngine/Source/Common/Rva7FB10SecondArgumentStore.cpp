class Rva7FB10SecondArgumentStore
{
public:
    Rva7FB10SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0007fb10@@YAXXZ
Rva7FB10SecondArgumentStore *Rva7FB10SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

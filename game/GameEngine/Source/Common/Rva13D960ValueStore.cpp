class Rva13D960ValueStore
{
public:
    Rva13D960ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d960@@YAXXZ
Rva13D960ValueStore *Rva13D960ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

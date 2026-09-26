class Rva13DD60ValueStore
{
public:
    Rva13DD60ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013dd60@@YAXXZ
Rva13DD60ValueStore *Rva13DD60ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

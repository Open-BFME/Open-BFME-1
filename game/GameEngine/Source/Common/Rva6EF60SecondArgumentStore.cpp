class Rva6EF60SecondArgumentStore {
public:
    Rva6EF60SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006ef60@@YAXXZ
Rva6EF60SecondArgumentStore *Rva6EF60SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

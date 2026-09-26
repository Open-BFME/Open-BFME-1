class Rva1A6CF0SecondArgumentStore
{
public:
    Rva1A6CF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_001a6cf0@@YAXXZ
Rva1A6CF0SecondArgumentStore *Rva1A6CF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

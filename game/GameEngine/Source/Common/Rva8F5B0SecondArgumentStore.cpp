class Rva8F5B0SecondArgumentStore
{
public:
    Rva8F5B0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0008f5b0@@YAXXZ
Rva8F5B0SecondArgumentStore *Rva8F5B0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

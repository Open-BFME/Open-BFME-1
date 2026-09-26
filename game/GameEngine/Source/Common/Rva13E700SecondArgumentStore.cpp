class Rva13E700SecondArgumentStore {
public:
    Rva13E700SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e700@@YAXXZ
Rva13E700SecondArgumentStore *Rva13E700SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

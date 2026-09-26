class Rva6EF70SecondArgumentStore {
public:
    Rva6EF70SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006ef70@@YAXXZ
Rva6EF70SecondArgumentStore *Rva6EF70SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

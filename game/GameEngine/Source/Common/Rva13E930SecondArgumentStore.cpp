class Rva13E930SecondArgumentStore {
public:
    Rva13E930SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e930@@YAXXZ
Rva13E930SecondArgumentStore *Rva13E930SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

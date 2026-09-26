class Rva13D6D0ValueStore {
public:
    Rva13D6D0ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d6d0@@YAXXZ
Rva13D6D0ValueStore *Rva13D6D0ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

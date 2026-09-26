class Rva13D6E0ValueStore {
public:
    Rva13D6E0ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d6e0@@YAXXZ
Rva13D6E0ValueStore *Rva13D6E0ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

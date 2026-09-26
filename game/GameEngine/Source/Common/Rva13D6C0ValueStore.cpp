class Rva13D6C0ValueStore {
public:
    Rva13D6C0ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d6c0@@YAXXZ
Rva13D6C0ValueStore *Rva13D6C0ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

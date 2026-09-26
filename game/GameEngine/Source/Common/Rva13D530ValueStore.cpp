class Rva13D530ValueStore {
public:
    Rva13D530ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d530@@YAXXZ
Rva13D530ValueStore *Rva13D530ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

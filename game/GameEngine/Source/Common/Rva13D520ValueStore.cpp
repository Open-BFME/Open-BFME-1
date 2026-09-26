class Rva13D520ValueStore {
public:
    Rva13D520ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013d520@@YAXXZ
Rva13D520ValueStore *Rva13D520ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}

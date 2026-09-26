class Rva6EEC0SecondArgumentStore {
public:
    Rva6EEC0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006eec0@@YAXXZ
Rva6EEC0SecondArgumentStore *Rva6EEC0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

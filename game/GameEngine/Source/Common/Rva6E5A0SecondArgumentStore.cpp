class Rva6E5A0SecondArgumentStore {
public:
    Rva6E5A0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006e5a0@@YAXXZ
Rva6E5A0SecondArgumentStore *Rva6E5A0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

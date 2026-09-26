class Rva6EED0SecondArgumentStore {
public:
    Rva6EED0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006eed0@@YAXXZ
Rva6EED0SecondArgumentStore *Rva6EED0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

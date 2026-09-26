class Rva6EEB0SecondArgumentStore {
public:
    Rva6EEB0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006eeb0@@YAXXZ
Rva6EEB0SecondArgumentStore *Rva6EEB0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

class Rva6EEA0SecondArgumentStore {
public:
    Rva6EEA0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006eea0@@YAXXZ
Rva6EEA0SecondArgumentStore *Rva6EEA0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

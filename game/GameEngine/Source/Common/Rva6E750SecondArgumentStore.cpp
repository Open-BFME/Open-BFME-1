class Rva6E750SecondArgumentStore {
public:
    Rva6E750SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006e750@@YAXXZ
Rva6E750SecondArgumentStore *Rva6E750SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

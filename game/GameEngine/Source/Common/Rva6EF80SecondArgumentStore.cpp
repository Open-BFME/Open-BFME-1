class Rva6EF80SecondArgumentStore {
public:
    Rva6EF80SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0006ef80@@YAXXZ
Rva6EF80SecondArgumentStore *Rva6EF80SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

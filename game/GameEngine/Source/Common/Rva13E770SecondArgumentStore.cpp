class Rva13E770SecondArgumentStore {
public:
    Rva13E770SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e770@@YAXXZ
Rva13E770SecondArgumentStore *Rva13E770SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

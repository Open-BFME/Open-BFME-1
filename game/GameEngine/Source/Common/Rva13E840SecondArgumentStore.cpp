class Rva13E840SecondArgumentStore {
public:
    Rva13E840SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e840@@YAXXZ
Rva13E840SecondArgumentStore *Rva13E840SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

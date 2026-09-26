class Rva13E960SecondArgumentStore {
public:
    Rva13E960SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e960@@YAXXZ
Rva13E960SecondArgumentStore *Rva13E960SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

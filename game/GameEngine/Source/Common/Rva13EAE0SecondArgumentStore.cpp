class Rva13EAE0SecondArgumentStore {
public:
    Rva13EAE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013eae0@@YAXXZ
Rva13EAE0SecondArgumentStore *Rva13EAE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

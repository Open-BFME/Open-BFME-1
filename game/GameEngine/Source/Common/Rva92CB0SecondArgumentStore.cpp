class Rva92CB0SecondArgumentStore {
public:
    Rva92CB0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_00092cb0@@YAXXZ
Rva92CB0SecondArgumentStore *Rva92CB0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

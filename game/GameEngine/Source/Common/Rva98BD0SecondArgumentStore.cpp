class Rva98BD0SecondArgumentStore {
public:
    Rva98BD0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_00098bd0@@YAXXZ
Rva98BD0SecondArgumentStore *Rva98BD0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

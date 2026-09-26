class Rva1A6D00SecondArgumentStore
{
public:
    Rva1A6D00SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_001a6d00@@YAXXZ
Rva1A6D00SecondArgumentStore *Rva1A6D00SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

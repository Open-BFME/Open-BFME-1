class Rva8E220SecondArgumentStore
{
public:
    Rva8E220SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0008e220@@YAXXZ
Rva8E220SecondArgumentStore *Rva8E220SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

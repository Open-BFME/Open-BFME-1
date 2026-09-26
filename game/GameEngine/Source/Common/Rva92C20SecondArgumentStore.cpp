class Rva92C20SecondArgumentStore
{
public:
    Rva92C20SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_00092c20@@YAXXZ
Rva92C20SecondArgumentStore *Rva92C20SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

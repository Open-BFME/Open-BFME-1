class Rva13E970SecondArgumentStore {
public:
    Rva13E970SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_0013e970@@YAXXZ
Rva13E970SecondArgumentStore *Rva13E970SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

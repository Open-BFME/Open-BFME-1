class RvaA8F70SecondArgumentStore {
public:
    RvaA8F70SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000a8f70@@YAXXZ
RvaA8F70SecondArgumentStore *RvaA8F70SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

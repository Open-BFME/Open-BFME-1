class RvaA0A10SecondArgumentStore {
public:
    RvaA0A10SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000a0a10@@YAXXZ
RvaA0A10SecondArgumentStore *RvaA0A10SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

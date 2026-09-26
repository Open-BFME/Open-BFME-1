class RvaA8F20SecondArgumentStore {
public:
    RvaA8F20SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000a8f20@@YAXXZ
RvaA8F20SecondArgumentStore *RvaA8F20SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

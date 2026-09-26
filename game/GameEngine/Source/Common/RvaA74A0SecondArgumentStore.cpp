class RvaA74A0SecondArgumentStore {
public:
    RvaA74A0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000a74a0@@YAXXZ
RvaA74A0SecondArgumentStore *RvaA74A0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

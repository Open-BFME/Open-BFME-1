class RvaA7530SecondArgumentStore {
public:
    RvaA7530SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000a7530@@YAXXZ
RvaA7530SecondArgumentStore *RvaA7530SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

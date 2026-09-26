class RvaE5CC0SecondArgumentStore {
public:
    RvaE5CC0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000e5cc0@@YAXXZ
RvaE5CC0SecondArgumentStore *RvaE5CC0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

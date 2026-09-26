class RvaBEDB0SecondArgumentStore {
public:
    RvaBEDB0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000bedb0@@YAXXZ
RvaBEDB0SecondArgumentStore *RvaBEDB0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

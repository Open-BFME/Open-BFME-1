class RvaCCEE0SecondArgumentStore {
public:
    RvaCCEE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccee0@@YAXXZ
RvaCCEE0SecondArgumentStore *RvaCCEE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

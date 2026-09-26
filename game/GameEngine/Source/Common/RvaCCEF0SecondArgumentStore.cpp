class RvaCCEF0SecondArgumentStore {
public:
    RvaCCEF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccef0@@YAXXZ
RvaCCEF0SecondArgumentStore *RvaCCEF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

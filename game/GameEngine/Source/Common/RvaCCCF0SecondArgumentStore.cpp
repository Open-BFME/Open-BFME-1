class RvaCCCF0SecondArgumentStore {
public:
    RvaCCCF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000cccf0@@YAXXZ
RvaCCCF0SecondArgumentStore *RvaCCCF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

class RvaCCDB0SecondArgumentStore {
public:
    RvaCCDB0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccdb0@@YAXXZ
RvaCCDB0SecondArgumentStore *RvaCCDB0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

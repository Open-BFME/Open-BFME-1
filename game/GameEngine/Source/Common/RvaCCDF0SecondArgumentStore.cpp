class RvaCCDF0SecondArgumentStore {
public:
    RvaCCDF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccdf0@@YAXXZ
RvaCCDF0SecondArgumentStore *RvaCCDF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

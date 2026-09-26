class RvaCCD30SecondArgumentStore {
public:
    RvaCCD30SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccd30@@YAXXZ
RvaCCD30SecondArgumentStore *RvaCCD30SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

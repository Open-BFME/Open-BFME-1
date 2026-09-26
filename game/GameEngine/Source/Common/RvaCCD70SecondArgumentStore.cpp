class RvaCCD70SecondArgumentStore {
public:
    RvaCCD70SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ccd70@@YAXXZ
RvaCCD70SecondArgumentStore *RvaCCD70SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

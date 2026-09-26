class RvaE7160SecondArgumentStore {
public:
    RvaE7160SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000e7160@@YAXXZ
RvaE7160SecondArgumentStore *RvaE7160SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

class RvaEE310SecondArgumentStore {
public:
    RvaEE310SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ee310@@YAXXZ
RvaEE310SecondArgumentStore *RvaEE310SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

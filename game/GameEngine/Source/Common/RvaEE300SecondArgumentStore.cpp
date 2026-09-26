class RvaEE300SecondArgumentStore {
public:
    RvaEE300SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

// ?d_000ee300@@YAXXZ
RvaEE300SecondArgumentStore *RvaEE300SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}

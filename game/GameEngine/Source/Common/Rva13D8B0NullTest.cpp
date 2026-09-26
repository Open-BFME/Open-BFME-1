class Rva13D8B0NullTest
{
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

// ?d_0013d8b0@@YAXXZ
bool Rva13D8B0NullTest::empty() const
{
    return m_value == 0;
}

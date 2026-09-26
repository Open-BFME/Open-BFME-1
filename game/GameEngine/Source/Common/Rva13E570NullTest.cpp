class Rva13E570NullTest
{
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

// ?d_0013e570@@YAXXZ
bool Rva13E570NullTest::empty() const
{
    return m_value == 0;
}

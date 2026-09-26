class Rva13D1D0NullMemberTest {
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

bool Rva13D1D0NullMemberTest::empty() const
{
    return m_value == 0;
}

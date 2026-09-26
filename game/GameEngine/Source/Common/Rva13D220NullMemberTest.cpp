class Rva13D220NullMemberTest {
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

// ?d_0013d220@@YAXXZ
bool Rva13D220NullMemberTest::empty() const
{
    return m_value == 0;
}

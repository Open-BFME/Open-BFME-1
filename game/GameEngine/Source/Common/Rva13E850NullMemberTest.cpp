class Rva13E850NullMemberTest {
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

// ?d_0013e850@@YAXXZ
bool Rva13E850NullMemberTest::empty() const
{
    return m_value == 0;
}

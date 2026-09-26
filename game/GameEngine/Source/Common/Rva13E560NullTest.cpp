class Rva13E560NullTest
{
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

// ?d_0013e560@@YAXXZ
bool Rva13E560NullTest::empty() const
{
    return m_value == 0;
}

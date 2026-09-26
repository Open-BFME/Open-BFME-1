struct Rva007EA490Nested
{
    char m_padding[0x224];
    void *m_first;
    void *m_second;
    void *m_third;
};

class Rva007EA490Owner
{
public:
    void set(void *first, void *second, void *third);
private:
    void *m_head;
    Rva007EA490Nested *m_nested;
};

void Rva007EA490Owner::set(void *first, void *second, void *third)
{
    m_nested->m_first = first;
    m_nested->m_second = second;
    m_nested->m_third = third;
}

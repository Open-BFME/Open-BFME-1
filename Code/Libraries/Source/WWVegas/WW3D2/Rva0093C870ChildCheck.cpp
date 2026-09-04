// cl: /DNDEBUG /MD /EHsc

class Rva0093C4A0Target
{
public:
    bool Check(void *first, void *second, void *third);

    void *m_gap00;
    void *m_gap04;
    Rva0093C4A0Target *m_child;
};

class Rva0093C870Owner
{
public:
    Rva0093C4A0Target *Check(void *first, void *second, void *third);

private:
    char m_gap00[0x4c];
    Rva0093C4A0Target *m_target;
};

Rva0093C4A0Target *Rva0093C870Owner::Check(
    void *first, void *second, void *third)
{
    if (!m_target->Check(first, second, third))
    {
        if (m_target->m_child != 0)
        {
            m_target->m_child->Check(first, second, third);
            return m_target->m_child;
        }
    }

    return m_target;
}

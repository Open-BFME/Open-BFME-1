class Rva007F90E0Fields
{
public:
    void reset();
private:
    unsigned int m_first;
    unsigned int m_second;
    unsigned int m_remaining[5];
};

void Rva007F90E0Fields::reset()
{
    m_second = 0;
    m_first = 0;
    for (int i = 0; i < 5; ++i)
        m_remaining[i] = 0;
}

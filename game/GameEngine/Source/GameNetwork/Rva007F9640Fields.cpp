class Rva007F9640Fields
{
public:
    Rva007F9640Fields();
private:
    unsigned int m_first;
    unsigned int m_second;
    unsigned int m_remaining[5];
};

Rva007F9640Fields::Rva007F9640Fields()
{
    m_second = 0;
    m_first = 0;
    for (int i = 0; i < 5; ++i)
        m_remaining[i] = 0;
}

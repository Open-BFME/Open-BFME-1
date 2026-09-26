class Rva007F4850Fields
{
public:
    void reset();
private:
    unsigned int m_head[2];
    unsigned int m_values[4];
};

void Rva007F4850Fields::reset()
{
    for (int i = 0; i < 4; ++i)
        m_values[i] = 0;
}

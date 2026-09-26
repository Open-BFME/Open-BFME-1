class Rva0015E700
{
public:
    unsigned int get();

private:
    char m_padding[0x1c];
    unsigned int m_value;
};

unsigned int Rva0015E700::get()
{
    return m_value;
}

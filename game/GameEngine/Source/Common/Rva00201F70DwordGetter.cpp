class Rva00201F70
{
public:
    unsigned int get();

private:
    char m_padding[4];
    unsigned int m_value;
};

unsigned int Rva00201F70::get()
{
    return m_value;
}

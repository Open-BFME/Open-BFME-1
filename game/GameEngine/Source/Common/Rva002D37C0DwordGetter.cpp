class Rva002D37C0
{
public:
    unsigned int get();

private:
    char m_padding[4];
    unsigned int m_value;
};

unsigned int Rva002D37C0::get()
{
    return m_value;
}

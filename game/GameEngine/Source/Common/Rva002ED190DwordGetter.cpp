// cl: /O2

class Rva002ED190DwordGetter
{
public:
    unsigned int get() const;

private:
    char m_padding[0x20];
    unsigned int m_value;
};

unsigned int Rva002ED190DwordGetter::get() const
{
    return m_value;
}

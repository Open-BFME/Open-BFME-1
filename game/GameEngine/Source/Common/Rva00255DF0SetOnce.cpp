// Open-BFME: one-time field setter reconstructed from retail RVA 0x00255DF0.

class Rva00255DF0Object
{
public:
    void setIfClear(int value);

private:
    char m_pad0[0x14];
    int m_value;
    unsigned char m_initialized;
};

void Rva00255DF0Object::setIfClear(int value)
{
    if (m_initialized == 0)
    {
        m_initialized = 1;
        m_value = value;
    }
}

// Open-BFME: scaled arithmetic leaf reconstructed from retail RVA 0x00977870.

class Rva00977870Object
{
public:
    int compute(void);

private:
    char m_pad0[8];
    int m_factor;
    char m_pad1[12];
    int m_base;
    int m_delta;
};

int Rva00977870Object::compute(void)
{
    return (m_delta - m_base + 1) * m_factor * 4 + 0x20;
}

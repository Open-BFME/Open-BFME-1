// Open-BFME: nested two-field setter reconstructed from retail RVA 0x003F69C0.

class Rva003F69C0Inner
{
public:
    char m_pad0[8];
    int m_first;
    int m_second;
};

class Rva003F69C0Object
{
public:
    void set(int *source, int value);

private:
    Rva003F69C0Inner *m_inner;
};

void Rva003F69C0Object::set(int *source, int value)
{
    m_inner->m_first = *source;
    m_inner->m_second = value;
}

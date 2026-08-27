// Open-BFME: flag-or-field selector reconstructed from retail RVA 0x0049AC30.

class Rva0049AC30Object
{
public:
    int select(void);

private:
    char m_pad0[0x90];
    int m_fallback;
    char m_pad94[0xBB];
    unsigned char m_flag;
};

int Rva0049AC30Object::select(void)
{
    return m_flag ? 5 : m_fallback;
}

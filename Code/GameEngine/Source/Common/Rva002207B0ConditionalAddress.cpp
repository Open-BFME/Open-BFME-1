// Open-BFME: conditional address accessor reconstructed from retail RVA 0x002207B0.

class Rva002207B0Object
{
public:
    void *getAddress(void);

private:
    char m_pad0[0x78];
    int m_value;
    char m_pad7C[8];
    unsigned char m_enabled;
};

void *Rva002207B0Object::getAddress(void)
{
    return m_enabled ? &m_value : 0;
}

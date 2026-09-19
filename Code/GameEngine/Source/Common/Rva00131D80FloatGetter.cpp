// cl: /DNDEBUG /MD

class Rva00131D80
{
public:
    float getAt2C(void) const;

private:
    unsigned char m_beforeField[0x2C];
    float m_field;
};

// ?getAt2C@Rva00131D80@@QBEMXZ
float Rva00131D80::getAt2C(void) const
{
    return m_field;
}

class Rva13A430SignedByte
{
public:
    int value() const;

private:
    unsigned char m_prefix[0x496];
    signed char m_value;
};

// ?d_0013a430@@YAXXZ
int Rva13A430SignedByte::value() const
{
    return m_value;
}

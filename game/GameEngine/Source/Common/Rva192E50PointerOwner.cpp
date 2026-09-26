class Rva192E50PointerOwner
{
public:
    unsigned char *offset();

private:
    unsigned char *m_value;
};

// ?d_00192e50@@YAXXZ
unsigned char *Rva192E50PointerOwner::offset()
{
    return m_value + 16;
}

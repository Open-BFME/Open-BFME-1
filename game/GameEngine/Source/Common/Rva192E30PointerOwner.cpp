class Rva192E30PointerOwner
{
public:
    unsigned char *offset();

private:
    unsigned char *m_value;
};

// ?d_00192e30@@YAXXZ
unsigned char *Rva192E30PointerOwner::offset()
{
    return m_value + 16;
}

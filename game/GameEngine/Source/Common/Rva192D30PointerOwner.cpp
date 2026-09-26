class Rva192D30PointerOwner
{
public:
    unsigned char *offset();

private:
    unsigned char *m_value;
};

// ?d_00192d30@@YAXXZ
unsigned char *Rva192D30PointerOwner::offset()
{
    return m_value + 16;
}

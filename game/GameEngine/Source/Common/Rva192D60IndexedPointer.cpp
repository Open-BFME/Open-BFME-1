class Rva192D60IndexedPointer
{
public:
    unsigned char *at(unsigned int index);

private:
    unsigned char *m_base;
};

// ?d_00192d60@@YAXXZ
unsigned char *Rva192D60IndexedPointer::at(unsigned int index)
{
    return m_base + index * 140;
}

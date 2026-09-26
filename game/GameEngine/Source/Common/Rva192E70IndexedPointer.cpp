class Rva192E70IndexedPointer
{
public:
    unsigned char *at(unsigned int index);

private:
    unsigned char *m_base;
};

unsigned char *Rva192E70IndexedPointer::at(unsigned int index)
{
    return m_base + index * 12;
}

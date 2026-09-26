struct Rva13E540Record
{
    unsigned char data[36];
};

class Rva13E540RecordIndex
{
public:
    Rva13E540Record *at(unsigned int index);

private:
    Rva13E540Record *m_records;
};

// ?d_0013e540@@YAXXZ
Rva13E540Record *Rva13E540RecordIndex::at(unsigned int index)
{
    return m_records + index;
}

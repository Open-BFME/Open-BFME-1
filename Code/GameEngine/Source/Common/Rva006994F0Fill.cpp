// Open-BFME5: clean C++ conversion of the embedded byte-table fill.

class Rva006994F0Owner
{
public:
    void initializeTable();

private:
    char m_pad00[0x188];
    unsigned char m_table[48];
};

void Rva006994F0Owner::initializeTable()
{
    for (unsigned int i = 0; i != sizeof(m_table); ++i) {
        m_table[i] = 2;
    }
}

// cl: /DNDEBUG /MD /EHsc
// RVA 0x00801430: clear five witnessed fields in an opaque object.
struct Rva00801430Owner
{
    char m_pad0[4];
    int m_word4;
    char m_pad8[0x20];
    int m_word28;
    int m_word2C;
    unsigned char m_byte30;
    char m_pad31[0x24];
    unsigned char m_byte55;

    void clearFields();
};

void Rva00801430Owner::clearFields()
{
    m_word4 = 0;
    m_word28 = 0;
    m_byte30 = 0;
    m_byte55 = 0;
    m_word2C = 0;
}

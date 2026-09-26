// cl: /DNDEBUG /MD /EHsc
// RVA 0x008008C0: clear four words and one byte in an opaque object.
struct Rva008008C0Owner
{
    int m_word0;
    int m_word4;
    unsigned char m_byte8;
    char m_pad9[3];
    int m_wordC;
    char m_pad10[0x10];
    int m_word20;

    void clearFields();
};

void Rva008008C0Owner::clearFields()
{
    m_word0 = 0;
    m_word4 = 0;
    m_wordC = 0;
    m_word20 = 0;
    m_byte8 = 0;
}

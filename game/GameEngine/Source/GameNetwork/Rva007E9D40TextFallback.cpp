// cl: /O2
// Return the local nonempty text at +0x101, otherwise forward through slot 7.
struct Rva007E9D40Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6();
    virtual char *fallback();
};

struct Rva007E9D40Owner
{
    char m_pad0[12];
    Rva007E9D40Source *m_source;
    char m_pad10[0xF1];
    char m_text[1];
    char *getText();
};

char *Rva007E9D40Owner::getText()
{
    char *local = m_text;
    if (*local)
        return local;
    return m_source ? m_source->fallback() : 0;
}

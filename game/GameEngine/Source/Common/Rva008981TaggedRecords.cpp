// cl: /DNDEBUG /MD /O2

struct Rva00898130Record
{
    void *m_vptr;
    unsigned int m_tag;
    char m_unknown08[0x18];
    void *m_payload;
    void *active();
};
void *Rva00898130Record::active()
{
    if ((m_tag & 0x3F) == 1)
        return this;
    return m_payload;
}

struct Rva008981A0Record
{
    int m_unknown;
    unsigned int m_tag;
    bool isTypeThree();
};
bool Rva008981A0Record::isTypeThree()
{
    return (m_tag & 0x3F) == 3;
}

struct Rva008982C0Chars
{
    const char *m_data;
    int at(int index);
};
int Rva008982C0Chars::at(int index)
{
    return m_data[index + 8];
}

extern void ji_009f6fa0();
struct Rva008982D0Chars
{
    const char *m_data;
    bool equalIgnoringCase(const char *text);
};
bool Rva008982D0Chars::equalIgnoringCase(const char *text)
{
    typedef int (__cdecl *Compare)(const char *, const char *);
    return ((Compare)ji_009f6fa0)(m_data + 8, text) == 0;
}

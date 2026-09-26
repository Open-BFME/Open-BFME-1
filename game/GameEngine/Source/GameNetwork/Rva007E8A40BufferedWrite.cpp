// cl: /O2

int Rva007ED0E0(char *record, int size, const char *name,
    const unsigned char *source, int count);

class Rva007E8A40BufferedWrite
{
    char m_unknown00[0x10];
    char *m_field10;
    int m_field14;
    char m_unknown18[0x0C];
    int m_field24;

public:
    void write(const char *name, const unsigned char *source, int count);
};

void Rva007E8A40BufferedWrite::write(const char *name,
    const unsigned char *source, int count)
{
    if (Rva007ED0E0(m_field10, m_field14, name, source, count) < 0)
        m_field24 = -100;
}

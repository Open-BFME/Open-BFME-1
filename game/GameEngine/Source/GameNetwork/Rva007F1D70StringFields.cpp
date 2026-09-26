// cl: /O2
// These independent objects copy user strings into fixed-size member buffers.
void Rva007E8640Copy(char *dst, unsigned int dstSize, const char *src);

struct Rva007F1D70Buffer
{
    char m_prefix[8];
    char m_buffer[0x200];
    void set(const char *src);
};

void Rva007F1D70Buffer::set(const char *src)
{
    Rva007E8640Copy(m_buffer, sizeof(m_buffer), src);
}

struct Rva007F2620Buffer
{
    char m_prefix[0x54];
    char m_buffer[0xFF];
    void set(const char *src);
};

void Rva007F2620Buffer::set(const char *src)
{
    Rva007E8640Copy(m_buffer, sizeof(m_buffer), src);
}

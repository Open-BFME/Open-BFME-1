// cl: /O2
// Copy a string into the nested object's +0xE1 32-byte field.
void Rva007E8640Copy(char *dst, unsigned int dstSize, const char *src);

struct Rva007EA470Nested
{
    char m_prefix[0xE1];
    char m_field[0x20];
};

struct Rva007EA470Owner
{
    int m_reserved;
    Rva007EA470Nested *m_nested;
    void set(const char *src);
};

void Rva007EA470Owner::set(const char *src)
{
    Rva007E8640Copy(m_nested->m_field, sizeof(m_nested->m_field), src);
}

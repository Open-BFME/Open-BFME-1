// cl: /O2
// Two independent string fields use the same 32-byte bounded copy.
void Rva007E8640Copy(char *dst, unsigned int dstSize, const char *src);

class Rva007F25E0Fields
{
public:
    void setFirst(const char *src);
    void setSecond(const char *src);
private:
    char m_prefix[0x10];
    char m_first[0x20];
    char m_second[0x20];
};

void Rva007F25E0Fields::setFirst(const char *src)
{
    Rva007E8640Copy(m_first, sizeof(m_first), src);
}

void Rva007F25E0Fields::setSecond(const char *src)
{
    Rva007E8640Copy(m_second, sizeof(m_second), src);
}

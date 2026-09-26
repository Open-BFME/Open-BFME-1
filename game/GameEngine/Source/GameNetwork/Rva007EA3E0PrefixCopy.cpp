extern "C" char *__cdecl strncpy(char *destination, const char *source, unsigned int count);

struct Rva007EA3E0Nested
{
    char m_padding[0x183];
    char m_prefix[0x5f];
};

class Rva007EA3E0Owner
{
public:
    void setPrefix(const char *value);
private:
    void *m_head;
    Rva007EA3E0Nested *m_nested;
};

void Rva007EA3E0Owner::setPrefix(const char *value)
{
    strncpy(m_nested->m_prefix, value, sizeof(m_nested->m_prefix));
}

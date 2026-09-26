void Rva007E8640Copy(char *destination, unsigned int capacity, const char *source);

struct Rva007EA470Nested
{
    char m_padding[0xe1];
    char m_text[0x20];
};

class Rva007EA470Owner
{
public:
    void setText(const char *text);
private:
    void *m_head;
    Rva007EA470Nested *m_nested;
};

void Rva007EA470Owner::setText(const char *text)
{
    Rva007E8640Copy(m_nested->m_text, sizeof(m_nested->m_text), text);
}

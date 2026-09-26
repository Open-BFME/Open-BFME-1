void Rva007E8640Copy(char *destination, unsigned int capacity, const char *source);

class Rva007F1D70Text
{
public:
    void set(const char *value);
private:
    char m_padding[8];
    char m_text[0x200];
};

void Rva007F1D70Text::set(const char *value)
{
    Rva007E8640Copy(m_text, sizeof(m_text), value);
}

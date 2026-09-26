void Rva007E8640Copy(char *destination, unsigned int capacity, const char *source);

class Rva007F25E0Strings
{
public:
    void setFirst(const char *value);
    void setSecond(const char *value);
    void setThird(const char *value);
private:
    char m_padding[0x10];
    char m_first[0x20];
    char m_second[0x20];
    char m_metadata[4];
    char m_third[0xff];
};

void Rva007F25E0Strings::setFirst(const char *value)
{
    Rva007E8640Copy(m_first, sizeof(m_first), value);
}

void Rva007F25E0Strings::setSecond(const char *value)
{
    Rva007E8640Copy(m_second, sizeof(m_second), value);
}

void Rva007F25E0Strings::setThird(const char *value)
{
    Rva007E8640Copy(m_third, sizeof(m_third), value);
}

class Rva13D070MemberAdvanceSixteen {
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

// ?d_0013d070@@YAXXZ
unsigned char *Rva13D070MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}

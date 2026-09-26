class Rva13D080MemberAdvanceSixteen {
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

// ?d_0013d080@@YAXXZ
unsigned char *Rva13D080MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}

// cl: /O2

struct Rva00385140Offset8Getter
{
    char m_prefix[8];
    int m_value;

    int get() const;
};

int Rva00385140Offset8Getter::get() const
{
    return m_value;
}

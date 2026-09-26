class Rva13DED0PointerAssign
{
public:
    Rva13DED0PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013ded0@@YAXXZ
Rva13DED0PointerAssign *Rva13DED0PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

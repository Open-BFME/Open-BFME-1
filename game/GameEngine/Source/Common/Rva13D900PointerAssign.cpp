class Rva13D900PointerAssign
{
public:
    Rva13D900PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013d900@@YAXXZ
Rva13D900PointerAssign *Rva13D900PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

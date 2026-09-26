class Rva13D300PointerAssign {
public:
    Rva13D300PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013d300@@YAXXZ
Rva13D300PointerAssign *Rva13D300PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

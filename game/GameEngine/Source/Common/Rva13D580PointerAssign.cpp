class Rva13D580PointerAssign {
public:
    Rva13D580PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013d580@@YAXXZ
Rva13D580PointerAssign *Rva13D580PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

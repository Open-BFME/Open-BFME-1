class Rva13D360PointerAssign {
public:
    Rva13D360PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013d360@@YAXXZ
Rva13D360PointerAssign *Rva13D360PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

class Rva13D380
{
public:
    void method();
};

void Rva13D380::method()
{
}

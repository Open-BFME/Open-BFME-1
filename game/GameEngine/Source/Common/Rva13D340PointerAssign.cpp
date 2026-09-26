class Rva13D340PointerAssign {
public:
    Rva13D340PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

// ?d_0013d340@@YAXXZ
Rva13D340PointerAssign *Rva13D340PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}

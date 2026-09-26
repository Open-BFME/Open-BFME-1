class Rva13D5C0ResetValue {
public:
    Rva13D5C0ResetValue *reset();

private:
    unsigned int m_value;
};

// ?d_0013d5c0@@YAXXZ
Rva13D5C0ResetValue *Rva13D5C0ResetValue::reset()
{
    m_value = 0;
    return this;
}

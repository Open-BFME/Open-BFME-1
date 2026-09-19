// cl: /DNDEBUG /MD /EHsc /O2

// Retail 0x0060A6C0 stores one dword argument at this-relative offset 0xA8.
// No caller proves the field's semantic owner, so the owner keeps the RVA.
class Rva0060A6C0Owner
{
public:
    void setFieldAtA8(int value);

private:
    char m_head[0xA8];
    int m_field;
};

void Rva0060A6C0Owner::setFieldAtA8(int value)
{
    m_field = value;
}

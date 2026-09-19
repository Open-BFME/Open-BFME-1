// cl: /DNDEBUG /MD /EHsc /O2

// Retail 0x00097180 returns the dword stored at this-relative offset 0x0C.
// No caller proves the field's semantic owner, so the owner keeps the RVA.
class Rva00097180Owner
{
public:
    int getFieldAtC() const;

private:
    char m_head[0x0C];
    int m_field;
};

int Rva00097180Owner::getFieldAtC() const
{
    return m_field;
}

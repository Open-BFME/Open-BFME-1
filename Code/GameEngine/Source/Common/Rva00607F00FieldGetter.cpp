// cl: /DNDEBUG /MD /EHsc /O2

// Retail 0x00607F00 returns the dword stored at this-relative offset 0x04.
// The nearby flag-pair methods do not prove the field's semantic owner, so the
// owner keeps the RVA in its name.
class Rva00607F00Owner
{
public:
    int getFieldAt4() const;

private:
    char m_head[4];
    int m_field;
};

int Rva00607F00Owner::getFieldAt4() const
{
    return m_field;
}

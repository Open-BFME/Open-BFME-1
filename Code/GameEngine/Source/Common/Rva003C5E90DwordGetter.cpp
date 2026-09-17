// cl: /O2

// Retail 0x003C5E90 loads a dword from this+0x78 and returns it.
// The carved boundary and instruction shape provide no stronger identity.
class Rva003C5E90DwordField
{
public:
    unsigned int get() const;

private:
    char m_padding[0x78];
    unsigned int m_value;
};

unsigned int Rva003C5E90DwordField::get() const
{
    return m_value;
}

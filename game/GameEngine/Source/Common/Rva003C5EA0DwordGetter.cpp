// cl: /O2

// Retail 0x003C5EA0 loads a dword from this+0x7C and returns it.
// The carved boundary and instruction shape provide no stronger identity.
class Rva003C5EA0DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x7C];
	unsigned int m_value;
};

unsigned int Rva003C5EA0DwordField::get() const
{
	return m_value;
}

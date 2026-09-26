// cl: /O2 /Ob0

// Retail 0x003378E0 returns the raw dword at this-relative offset 0x04.
class Rva003378E0DwordField
{
public:
	unsigned int m_pad00;
	unsigned int m_value;

	unsigned int get() const;
};

unsigned int Rva003378E0DwordField::get() const
{
	return m_value;
}

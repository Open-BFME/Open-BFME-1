// cl: /O2 /Ob0

// Retail 0x00337880 returns the raw dword at this-relative offset 0x04.
class Rva00337880DwordField
{
public:
	unsigned int m_pad00;
	unsigned int m_value;

	unsigned int get() const;
};

unsigned int Rva00337880DwordField::get() const
{
	return m_value;
}

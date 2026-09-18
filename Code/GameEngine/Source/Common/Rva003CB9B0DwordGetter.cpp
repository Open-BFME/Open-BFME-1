// cl: /DNDEBUG /MD /EHsc

// Retail 0x003CB9B0 returns the raw dword at this-relative offset 0x30.
class Rva003CB9B0DwordField
{
public:
	unsigned int get() const;

private:
	char m_pad[0x30];
	unsigned int m_value;
};

unsigned int Rva003CB9B0DwordField::get() const
{
	return m_value;
}

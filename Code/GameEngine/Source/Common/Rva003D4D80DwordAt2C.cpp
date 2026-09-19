// cl: /O2 /DNDEBUG /MD
// Retail RVA 0x003D4D80 is a four-byte dword getter with no surviving name.

class Rva003D4D80DwordAt2C
{
public:
	unsigned int get() const;

private:
	char m_prefix[0x2c];
	unsigned int m_value;
};

// ?get@Rva003D4D80DwordAt2C@@QBEIXZ
unsigned int Rva003D4D80DwordAt2C::get() const
{
	return m_value;
}

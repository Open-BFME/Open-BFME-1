// cl: /O2 /DNDEBUG /MD
// Retail RVA 0x006E7A80 is a four-byte dword getter with no surviving name.

class Rva006E7A80DwordAt10
{
public:
	unsigned int get() const;

private:
	char m_prefix[0x10];
	unsigned int m_value;
};

// ?get@Rva006E7A80DwordAt10@@QBEIXZ
unsigned int Rva006E7A80DwordAt10::get() const
{
	return m_value;
}

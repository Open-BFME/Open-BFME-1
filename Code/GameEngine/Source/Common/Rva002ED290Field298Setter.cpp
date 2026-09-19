// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved body copies its one 32-bit argument into this+0x298 and returns.
// No caller or type table proves a semantic owner or field type, so the source
// keeps the address-derived owner and models the field as an unsigned integer.

class Rva002ED290Owner
{
public:
	void setField298(unsigned int value);

private:
	unsigned char m_beforeField[0x298];
	unsigned int m_field298;
};

// ?setField298@Rva002ED290Owner@@QAEXI@Z
void Rva002ED290Owner::setField298(unsigned int value)
{
	m_field298 = value;
}

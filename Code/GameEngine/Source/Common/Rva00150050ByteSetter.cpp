// cl: /O2
// Retail 0x00150050 stores one byte at this+0x33A and returns with ret 4.
// The body has no evidence for a semantic owner, so the class keeps its address.

class Rva00150050ByteSetter
{
public:
	void set(bool value);

private:
	unsigned char m_beforeValue[0x33A];
	bool m_value;
};

void Rva00150050ByteSetter::set(bool value)
{
	m_value = value;
}

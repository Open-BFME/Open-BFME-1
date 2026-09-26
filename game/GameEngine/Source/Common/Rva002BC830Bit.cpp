// cl: /O2
//
// Retail 0x002BC830 reads an unsigned dword at this-relative offset 0x3F0,
// extracts bit 8, and returns the full integer result.  No caller, vtable, or
// class evidence proves a semantic owner, so the method keeps the RVA.

class Rva002BC830
{
	char m_lead[0x3F0];
	unsigned int m_bits;

public:
	int bit() const;
};

int Rva002BC830::bit() const
{
	return (m_bits >> 8) & 1;
}

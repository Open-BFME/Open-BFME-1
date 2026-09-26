// cl: /O2 /Ob0

// Retail 0x001E0BD0 returns the byte at this+0x65. No caller or identity table
// proves a semantic owner, so the ledger keeps the carved address identity.

class Rva001E0BD0ByteField
{
public:
	unsigned char get() const;

private:
	unsigned char m_padding[0x65];
	unsigned char m_value;
};

// ?b_001e0bd0@@YAXXZ
unsigned char Rva001E0BD0ByteField::get() const
{
	return m_value;
}

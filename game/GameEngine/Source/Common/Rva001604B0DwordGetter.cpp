// cl: /O2 /Ob0

// Retail 0x001604B0 returns the dword at this+0x20. No caller or identity
// table proves a semantic owner, so the ledger keeps the carved address.

class Rva001604B0DwordField
{
public:
	unsigned int get() const;

private:
	char m_pad00[0x20];
	unsigned int m_value;
};

// ?d_001604b0@@YAXXZ
unsigned int Rva001604B0DwordField::get() const
{
	return m_value;
}

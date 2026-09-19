// cl: /O2 /Ob0

// Retail 0x0020A8F0 returns the dword at this+4. No caller or identity table
// proves a semantic owner, so the ledger keeps the carved address identity.

class Rva0020A8F0DwordField
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

// ?d_0020a8f0@@YAXXZ
unsigned int Rva0020A8F0DwordField::get() const
{
	return m_value;
}

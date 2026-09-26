// cl: /O2 /Ob0

// Retail 0x00251A20 returns the dword at this+4. No caller or identity table
// proves a semantic owner, so the ledger keeps the carved address identity.

class Rva00251A20DwordField
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

// ?d_00251a20@@YAXXZ
unsigned int Rva00251A20DwordField::get() const
{
	return m_value;
}

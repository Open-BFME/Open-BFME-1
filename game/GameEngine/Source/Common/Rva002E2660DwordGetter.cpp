// cl: /O2 /Ob0

// Retail 0x002E2660 returns the dword at this+0x14. No caller names the
// owner, so the source keeps the carved address in its type and method names.

class Rva002E2660DwordField
{
public:
	unsigned int get() const;

private:
	char m_gap[0x14];
	unsigned int m_value;
};

// ?get@Rva002E2660DwordField@@QBEIXZ
unsigned int Rva002E2660DwordField::get() const
{
	return m_value;
}

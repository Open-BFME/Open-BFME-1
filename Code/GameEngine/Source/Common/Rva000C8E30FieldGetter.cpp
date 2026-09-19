// cl: /O2 /Ob0

// Retail RVA 0x000C8E30 returns the dword at this+0x08.
// No caller or symbol evidence proves a semantic owner.

class Rva000C8E30
{
	char m_padding[0x08];
	int m_value;

public:
	int get() const;
};

int Rva000C8E30::get() const
{
	return m_value;
}

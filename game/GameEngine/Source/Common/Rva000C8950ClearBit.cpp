// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C8950
{
	char m_lead[0x2A0];
	unsigned m_flags;

public:
	Rva000C8950 *clear(unsigned bit);
};

Rva000C8950 *Rva000C8950::clear(unsigned bit)
{
	m_flags &= ~(1u << bit);
	return this;
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva004104F0
{
	char m_pad[0x114];
	unsigned m_114;

public:
	bool test(unsigned mask);
};

bool Rva004104F0::test(unsigned mask)
{
	return (m_114 & mask) != 0;
}

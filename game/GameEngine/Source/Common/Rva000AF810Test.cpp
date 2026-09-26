// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000AF810
{
	unsigned char m_pad[0x38];
	unsigned m_38;

public:
	int test(unsigned mask) const;
};

int Rva000AF810::test(unsigned mask) const
{
	return (m_38 & mask) != 0;
}

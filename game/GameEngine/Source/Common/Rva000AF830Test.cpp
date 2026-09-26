// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000AF830
{
	unsigned char m_pad[0x3C];
	unsigned m_3C;

public:
	int test(unsigned mask) const;
};

int Rva000AF830::test(unsigned mask) const
{
	return (m_3C & mask) != 0;
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00694850
{
	unsigned char m_pad[0x38];
	unsigned m_38;

public:
	int test(unsigned mask) const;
};

int Rva00694850::test(unsigned mask) const
{
	return (m_38 & mask) != 0;
}

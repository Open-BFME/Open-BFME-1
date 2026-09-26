// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00360670
{
	unsigned char m_pad[0x20];
	unsigned m_20;

public:
	int test() const;
};

int Rva00360670::test() const
{
	return m_20 != 1 && m_20 != 4;
}

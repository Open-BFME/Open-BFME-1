// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005375C0
{
	unsigned char m_pad[0xC];
	unsigned *m_C;

public:
	int test(unsigned mask, unsigned char index) const;
};

int Rva005375C0::test(unsigned mask, unsigned char index) const
{
	return (m_C[index] & mask) != 0;
}

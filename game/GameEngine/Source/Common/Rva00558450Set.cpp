// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00558450
{
	unsigned char m_pad[0x3C];
	unsigned m_3C;
	unsigned char m_pad40[0x55 - 0x40];
	unsigned char m_55;

public:
	int set(int);
};

int Rva00558450::set(int)
{
	m_55 = 1;
	m_3C = 1;
	return 1;
}

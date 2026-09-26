// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00409580
{
	char m_pad0[4];
	int *m_ptr;
	char m_pad1[8];
	int m_10;

public:
	void set(int value);
};

void Rva00409580::set(int value)
{
	m_ptr[0x10] = value;
	m_10 = value;
}

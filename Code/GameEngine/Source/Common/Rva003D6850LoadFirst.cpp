// cl: /O2 /DNDEBUG /MD
// Retail 0x003D6850 returns the dword at receiver offset zero.

struct Rva003D6850
{
	int m_value;

	int method();
};

int Rva003D6850::method()
{
	return m_value;
}

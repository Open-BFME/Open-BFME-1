// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005114A0
{
	char m_lead[0x258];
	unsigned int m_val;

public:
	void apply(int);
};

void Rva005114A0::apply(int)
{
	if (m_val == 1)
		m_val = 2;
}

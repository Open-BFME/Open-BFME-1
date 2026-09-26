// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00511230
{
	char m_lead[0x258];
	unsigned int m_val;

public:
	void apply(int);
};

void Rva00511230::apply(int)
{
	if (m_val == 0)
		m_val = 1;
}

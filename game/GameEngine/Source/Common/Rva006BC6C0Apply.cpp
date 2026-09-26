// cl: /O2 /Ob0

class Rva006BC6C0Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08(int value);
};

extern Rva006BC6C0Target *g_rva006BC6C0Target;

class Rva006BC6C0
{
	char m_lead[4];
	int m_at4;

public:
	void apply();
};

void Rva006BC6C0::apply()
{
	g_rva006BC6C0Target->slot08(m_at4);
}

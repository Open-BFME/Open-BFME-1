// cl: /O2 /Ob0

class Rva006E6CC0Target
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual int slot24();
};

extern Rva006E6CC0Target *g_rva006E6CC0Target;

class Rva006E6CC0
{
	char m_lead[0x2C];
	int m_at2C;

public:
	void apply();
};

void Rva006E6CC0::apply()
{
	m_at2C = g_rva006E6CC0Target->slot24();
}

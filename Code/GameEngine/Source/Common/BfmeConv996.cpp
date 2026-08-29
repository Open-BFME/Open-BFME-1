// Open-BFME5 conversions.

class BfmeX996
{
public:
	virtual void bfmeVX0996();
	virtual void bfmeVX1996();
	virtual void bfmeVX2996();
	virtual void bfmeVX3996();
	virtual void bfmeVX4996();
	virtual void bfmeVX5996();
	virtual char *bfmeName996();
};

struct BfmeSlot996
{
	char m_bfmePad[8];
	int m_bfmeVal;
};

class BfmeThing996
{
public:
	virtual void bfmeVX0996();
	virtual void bfmeVX1996();
	virtual void bfmeVX2996();
	virtual void bfmeVX3996();
	virtual void bfmeVX4996();
	virtual void bfmeVX5996();
	virtual void bfmeVX6996();
	virtual void bfmeVX7996();
	virtual void bfmeVX8996();
	virtual void bfmeVX9996();
	virtual void bfmeVX10996();
	virtual void bfmeVX11996();
	virtual void bfmeVX12996();
	virtual void bfmeVX13996();
	virtual void bfmeVX14996();
	virtual void bfmeVX15996();
	virtual void bfmeVX16996();
	virtual void bfmeVX17996();
	virtual void bfmeVX18996();
	virtual void bfmeVX19996();
	virtual void bfmeVX20996();
	virtual void bfmeVX21996();
	virtual void bfmeVX22996();
	virtual void bfmeVX23996();
	virtual void bfmeVX24996();
	virtual void bfmeVX25996();
	virtual void bfmeVX26996();
	virtual void bfmeVX27996();
	virtual void bfmeVX28996();
	virtual void bfmeVX29996();
	virtual void bfmeVX30996();
	virtual void bfmeVX31996();
	virtual void bfmeVX32996();
	virtual void bfmeVX33996();
	virtual void bfmeVX34996();
	virtual void bfmeVX35996();
	virtual void bfmeVX36996();
	virtual void bfmeVX37996();
	virtual void bfmeVX38996();
	virtual void bfmeVX39996();
	virtual void bfmeVX40996();
	virtual void bfmeVX41996();
	virtual void bfmeVX42996();
	virtual void bfmeVX43996();
	virtual void bfmeVX44996();
	virtual void bfmeVX45996();
	virtual BfmeX996 *bfmeGet996();

	char m_bfmePad[0x278];
	BfmeSlot996 *m_bfmeSlot;
};

class BfmeMap996
{
public:
	int bfmeIntern996(char *s);
};

extern BfmeMap996 *g_bfmeMap996;
extern char g_bfmeDefault996[];

void __stdcall bfmeGo996A(BfmeThing996 *t)
{
	BfmeX996 *x = t->bfmeGet996();
	char *s = x ? x->bfmeName996() : g_bfmeDefault996;

	t->m_bfmeSlot->m_bfmeVal = g_bfmeMap996->bfmeIntern996(s);
}

class BfmeDev996
{
public:
	virtual void bfmeVX0996();
	virtual void bfmeVX1996();
	virtual void bfmeVX2996();
	virtual void bfmeVX3996();
	virtual void bfmeVX4996();
	virtual void bfmeSet996(int a, int b);
};

class BfmeB996
{
public:
	char bfmeGo996B(int a, int b, char *c);
	char bfmeTry996(int a, int b, char *c);

	char m_bfmePad[4];
	BfmeDev996 *m_bfmeDev;
	int m_bfmeKind;
};

char BfmeB996::bfmeGo996B(int a, int b, char *c)
{
	if (m_bfmeKind == 6 && bfmeTry996(a, b, c) && !*c) {
		m_bfmeDev->bfmeSet996(-8, 1);
		return 1;
	}

	return 0;
}

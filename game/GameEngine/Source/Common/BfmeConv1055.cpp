// Open-BFME5 conversions.

extern "C" void *bfmeVft1055B[];
extern "C" void *bfmeVft1055C[];

class BfmeB1055
{
public:
	BfmeB1055 *bfmeGo1055B(int a, int b, int c, int d);
	BfmeB1055 *bfmeGo1055C(int a, int b, int c, int d);
	void bfmeBase1055(int b, int c, int d);

	void *m_bfmeVfptr;
	char m_bfmePad[0x2c];
	int m_bfme30;
};

BfmeB1055 *BfmeB1055::bfmeGo1055B(int a, int b, int c, int d)
{
	bfmeBase1055(b, c, d);
	m_bfme30 = a;
	m_bfmeVfptr = bfmeVft1055B;
	return this;
}

BfmeB1055 *BfmeB1055::bfmeGo1055C(int a, int b, int c, int d)
{
	bfmeBase1055(b, c, d);
	m_bfme30 = a;
	m_bfmeVfptr = bfmeVft1055C;
	return this;
}

struct BfmeR1055
{
	char m_bfmePad[0xab4];
	int m_bfmeH;
};

struct BfmeT1055
{
	BfmeR1055 *m_bfmeA;
	int m_bfmeB;
};

extern "C" void bfmeHook1055(void);
void bfmeCall1055(int h, void (*fn)(void), BfmeT1055 *t);

void bfmeGo1055E(BfmeR1055 *p, int b)
{
	BfmeT1055 t;

	t.m_bfmeA = p;
	t.m_bfmeB = b;
	bfmeCall1055(p->m_bfmeH, bfmeHook1055, &t);
}

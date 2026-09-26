// Open-BFME5 conversions.

class BfmeT1225
{
public:
	virtual void bfmeV1225A();
	virtual void bfmeV1225B();
	virtual void bfmeV1225C();
	virtual void bfmeV1225D();
	virtual void bfmeV1225E(char *a, char *b);
};

class BfmeN1225
{
public:
	unsigned m_bfme00;
	unsigned m_bfme04;
	char *m_bfme08;
	char m_bfmePad0c[0x20 - 0x0c];
	BfmeN1225 *m_bfme20;
};

class BfmeH1225
{
public:
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	BfmeT1225 *m_bfme20;
};

char __stdcall bfmeVisit1225(BfmeH1225 *a, char **b, BfmeN1225 *c)
{
	unsigned k;
	BfmeN1225 *t;

	if ((a->m_bfme04 & 0x3f) == 0x22) {
		k = c->m_bfme04 & 0x3f;
		if ((k == 1 || k == 0x2a) && !((unsigned char)(~(c->m_bfme04 >> 15)) & 1)) {
			t = (k == 1) ? c : c->m_bfme20;
			a->m_bfme20->bfmeV1225E(*b + 8, t->m_bfme08 + 8);
		}
	}
	return 1;
}

// Open-BFME5 conversions.

class BfmeMgr1000
{
public:
	virtual void bfmeVX01000();
	virtual void bfmeVX11000();
	virtual char bfmeReady1000();
	virtual void bfmeVX31000();
	virtual void bfmeVX41000();
	virtual void bfmeVX51000();
	virtual void bfmeVX61000();
	virtual void bfmeVX71000();
	virtual void bfmeVX81000();
	virtual void bfmeVX91000();
	virtual void bfmeVX101000();
	virtual void bfmeVX111000();
	virtual void bfmeVX121000();
	virtual void bfmeVX131000();
	virtual void bfmeVX141000();
	virtual void bfmeVX151000();
	virtual void bfmeVX161000();
	virtual void bfmeVX171000();
	virtual void bfmeVX181000();
	virtual void bfmeVX191000();
	virtual void bfmeVX201000();
	virtual void bfmeVX211000();
	virtual void bfmeVX221000();
	virtual void bfmeVX231000();
	virtual void bfmeVX241000();
	virtual void bfmeVX251000();
	virtual void bfmeVX261000();
	virtual void bfmeVX271000();
	virtual void bfmeVX281000();
	virtual void bfmeVX291000();
	virtual void bfmeVX301000();
	virtual void bfmeVX311000();
	virtual void bfmeVX321000();
	virtual void bfmeVX331000();
	virtual void bfmeVX341000();
	virtual void bfmeVX351000();
	virtual void bfmeVX361000();
	virtual void bfmeVX371000();
	virtual void bfmeVX381000();
	virtual void bfmeVX391000();
	virtual void bfmeVX401000();
	virtual void bfmeVX411000();
	virtual void bfmeVX421000();
	virtual void bfmeVX431000();
	virtual void bfmeVX441000();
	virtual void bfmeVX451000();
	virtual void bfmeVX461000();
	virtual void bfmeVX471000();
	virtual void bfmeVX481000();
	virtual void bfmeVX491000();
	virtual void bfmeVX501000();
	virtual void bfmeVX511000();
	virtual void bfmeVX521000();
	virtual void bfmeVX531000();
	virtual void bfmeVX541000();
	virtual void bfmeVX551000();
	virtual void bfmeVX561000();
	virtual void bfmeVX571000();
	virtual void bfmeVX581000();
	virtual void bfmeVX591000();
	virtual void bfmeVX601000();
	virtual void bfmeVX611000();
	virtual void bfmeVX621000();
	virtual void bfmeVX631000();
	virtual void bfmeVX641000();
	virtual void bfmeVX651000();
	virtual void bfmeVX661000();
	virtual void bfmeVX671000();
	virtual int bfmeGet1000();
};

class BfmeArg1000
{
public:
	char bfmeHas1000(int v);

	char m_bfmePad[0x1fc];
	BfmeMgr1000 *m_bfmeMgr;
};

class BfmeA1000
{
public:
	char bfmeGo1000A(BfmeArg1000 *a);

	char m_bfmePad[8];
	int m_bfmeVal;
};

char BfmeA1000::bfmeGo1000A(BfmeArg1000 *a)
{
	if (a->bfmeHas1000(m_bfmeVal))
		return 1;

	BfmeMgr1000 *m = a->m_bfmeMgr;

	if (m && m->bfmeReady1000() && m->bfmeGet1000())
		return 1;

	return 0;
}

class BfmeThing1000
{
public:
	char bfmeIs1000(int kind);
};

struct BfmeSlot1000
{
	BfmeThing1000 *m_bfmeFirst;
	BfmeThing1000 *m_bfmeCur;
};

int bfmeGo1000B(BfmeThing1000 *t, BfmeSlot1000 *s)
{
	if (t) {
		BfmeThing1000 *cur = s->m_bfmeCur;

		if (cur) {
			if (t == cur)
				s->m_bfmeCur = 0;
		} else if (t->bfmeIs1000(0x59)) {
			s->m_bfmeFirst = t;
			return 0;
		}
	}

	return 1;
}

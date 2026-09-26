// Open-BFME5 conversions.

struct BfmeNode913D
{
	BfmeNode913D *m_bfmeNext;
	int m_bfmePad;
	void *m_bfmeKey;
};

struct BfmeList913D
{
	BfmeNode913D *m_bfmeHead;
};

struct BfmeHolder913D
{
	BfmeList913D *m_bfmeList;
};

class BfmeThing913D
{
public:
	virtual void bfmeSlot91300();
	virtual void bfmeSlot91301();
	virtual void bfmeSlot91302();
	virtual void bfmeSlot91303();
	virtual void bfmeSlot91304();
	virtual void bfmeSlot91305();
	virtual void bfmeSlot91306();
	virtual void bfmeSlot91307();
	virtual void bfmeSlot91308();
	virtual void bfmeSlot91309();
	virtual void bfmeSlot91310();
	virtual void bfmeSlot91311();
	virtual void bfmeSlot91312();
	virtual void bfmeSlot91313();
	virtual void bfmeSlot91314();
	virtual void bfmeSlot91315();
	virtual void bfmeSlot91316();
	virtual void bfmeSlot91317();
	virtual void bfmeSlot91318();
	virtual void bfmeSlot91319();
	virtual void bfmeSlot91320();
	virtual void bfmeSlot91321();
	virtual void bfmeSlot91322();
	virtual void bfmeSlot91323();
	virtual void bfmeSlot91324();
	virtual void bfmeSlot91325();
	virtual void bfmeSlot91326();
	virtual void bfmeSlot91327();
	virtual void bfmeSlot91328();
	virtual void bfmeSlot91329();
	virtual void bfmeSlot91330();
	virtual void bfmeSlot91331();
	virtual void bfmeSlot91332();
	virtual void bfmeSlot91333();
	virtual void bfmeSlot91334();
	virtual void bfmeSlot91335();
	virtual void bfmeSlot91336();
	virtual void bfmeSlot91337();
	virtual void bfmeSlot91338();
	virtual void bfmeSlot91339();
	virtual void bfmeSlot91340();
	virtual void bfmeSlot91341();
	virtual void bfmeSlot91342();
	virtual void bfmeSlot91343();
	virtual void bfmeSlot91344();
	virtual void bfmeSlot91345();
	virtual void bfmeSlot91346();
	virtual void bfmeSlot91347();
	virtual void bfmeSlot91348();
	virtual void bfmeSlot91349();
	virtual void bfmeSlot91350();
	virtual void bfmeSlot91351();
	virtual void bfmeSlot91352();
	virtual void bfmeSlot91353();
	virtual void bfmeSlot91354();
	virtual void bfmeSlot91355();
	virtual void bfmeSlot91356();
	virtual void bfmeSlot91357();
	virtual void bfmeSlot91358();
	virtual void bfmeSlot91359();
	virtual void bfmeSlot91360();
	virtual void bfmeSlot91361();
	virtual void bfmeSlot91362();
	virtual void bfmeSlot91363();
	virtual void bfmeSlot91364();
	virtual void bfmeSlot91365();
	virtual BfmeHolder913D *bfmeGet913D();
	char bfmeGo913D(void *k);
	char bfmeAdd913D(void *k);
};

char BfmeThing913D::bfmeGo913D(void *k)
{
	BfmeList913D *l = bfmeGet913D()->m_bfmeList;
	for (BfmeNode913D *n = l->m_bfmeHead; n != (BfmeNode913D *)l; n = n->m_bfmeNext)
		if (n->m_bfmeKey == k)
			return 1;
	return bfmeAdd913D(k);
}

class BfmeRes913E
{
public:
	virtual void bfmeSlot913E00();
	virtual void bfmeUse913E(void *b);
};

class BfmeSub913E
{
public:
	virtual void bfmeSlot913E100();
	virtual void bfmeSlot913E101();
	virtual void bfmeSlot913E102();
	virtual void bfmeSlot913E103();
	virtual void bfmeSlot913E104();
	virtual void bfmeSlot913E105();
	virtual void bfmeSlot913E106();
	virtual void bfmeSlot913E107();
	virtual void bfmeSlot913E108();
	virtual void bfmeSlot913E109();
	virtual void bfmeSlot913E110();
	virtual void bfmeSlot913E111();
	virtual void bfmeSlot913E112();
	virtual void bfmeSlot913E113();
	virtual void bfmeSlot913E114();
	virtual void bfmeSlot913E115();
	virtual void bfmeSlot913E116();
	virtual void bfmeSlot913E117();
	virtual void bfmeSlot913E118();
	virtual void bfmeSlot913E119();
	virtual void bfmeSlot913E120();
	virtual void bfmeSlot913E121();
	virtual void bfmeSlot913E122();
	virtual void bfmeSlot913E123();
	virtual void bfmeSlot913E124();
	virtual void bfmeSlot913E125();
	virtual BfmeRes913E *bfmeStep913E();
};

struct BfmeObj913E
{
	char m_bfmePad[0x1fc];
	BfmeSub913E *m_bfmeSub;
};

struct BfmeArg913E
{
	char m_bfmePad[8];
	void *m_bfmeKey;
};

class BfmeGlob913E
{
public:
	BfmeObj913E *bfmeFind913E(void *k);
};

extern BfmeGlob913E *g_bfme913Glob;

void __stdcall bfmeGo913E(BfmeArg913E *a, void *b)
{
	BfmeObj913E *o = g_bfme913Glob->bfmeFind913E(a->m_bfmeKey);
	if (o) {
		BfmeSub913E *s = o->m_bfmeSub;
		if (s)
			s->bfmeStep913E()->bfmeUse913E(b);
	}
}


// Open-BFME5 conversions.

class BfmeObjPA
{
public:
	virtual void bfmeSlotPA00();
	virtual void bfmeSlotPA01();
	virtual void bfmeSlotPA02();
	virtual void bfmeSlotPA03();
	virtual void bfmeSlotPA04();
	virtual void bfmeSlotPA05();
	virtual void bfmeSlotPA06();
	virtual void bfmeSlotPA07();
	virtual void bfmeSlotPA08();
	virtual void bfmeSlotPA09();
	virtual void bfmeSlotPA10();
	virtual void bfmeSlotPA11();
	virtual void bfmeSlotPA12();
	virtual void bfmeSlotPA13();
	virtual void bfmeSlotPA14();
	virtual void bfmeSlotPA15();
	virtual void bfmeVirtPA();
};

struct BfmeNodePA
{
	int m_bfmePad;
	BfmeObjPA *m_bfmeObj;
	BfmeNodePA *m_bfmeNext;
};

class BfmeThingPA
{
public:
	void bfmeGoPA(int i);
	char m_bfmePad[0x80];
	BfmeNodePA *m_bfmeHeads[1];
};

void BfmeThingPA::bfmeGoPA(int i)
{
	BfmeNodePA *n = m_bfmeHeads[i];
	while (n) {
		n->m_bfmeObj->bfmeVirtPA();
		n = n->m_bfmeNext;
	}
}

struct BfmeNodePB
{
	int m_bfmePad;
	void *m_bfmeObj;
	BfmeNodePB *m_bfmeNext;
};

class BfmeGlobPB
{
public:
	virtual void bfmeSlotPB00();
	virtual void bfmeSlotPB01();
	virtual void bfmeVirtPB(void *o);
};

extern BfmeGlobPB *g_bfmeGlobPB;

class BfmeThingPB
{
public:
	void bfmeGoPB(int i);
	char m_bfmePad[0x80];
	BfmeNodePB *m_bfmeHeads[1];
};

void BfmeThingPB::bfmeGoPB(int i)
{
	BfmeNodePB *n = m_bfmeHeads[i];
	while (n) {
		g_bfmeGlobPB->bfmeVirtPB(n->m_bfmeObj);
		n = n->m_bfmeNext;
	}
}

class BfmeSubPC
{
public:
	void bfmeOnePC();
	void bfmeTwoPC();
};

class BfmeThingPC
{
public:
	void bfmeGoPC();
	char m_bfmePad[0x3094];
	BfmeSubPC *m_bfmeA;
	BfmeSubPC *m_bfmeB;
};

void BfmeThingPC::bfmeGoPC()
{
	if (m_bfmeA)
		m_bfmeA->bfmeOnePC();
	if (m_bfmeB)
		m_bfmeB->bfmeTwoPC();
}

struct BfmeVecPD
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class BfmeSubPD
{
public:
	char bfmeTailPD(int a, BfmeVecPD *v, int e, int f);
};

class BfmeThingPD
{
public:
	char bfmeGoPD(int a, BfmeVecPD v, int e, int f);
	char m_bfmePad[0x309c];
	BfmeSubPD *m_bfmeSub;
};

char BfmeThingPD::bfmeGoPD(int a, BfmeVecPD v, int e, int f)
{
	BfmeSubPD *s = m_bfmeSub;
	if (s)
		return s->bfmeTailPD(a, &v, e, f);
	return 0;
}

struct BfmeSubPE
{
	int *m_bfmeFirst;
	int *bfmeFindPE(int k);
};

class BfmeThingPE
{
public:
	char *bfmeGoPE(int k);
	char m_bfmePad[0x1b8];
	BfmeSubPE m_bfmeSub;
};

char *BfmeThingPE::bfmeGoPE(int k)
{
	int *r = m_bfmeSub.bfmeFindPE(k);
	if (r == m_bfmeSub.m_bfmeFirst)
		return 0;
	return (char *)r + 0x14;
}

class BfmeThingPG
{
public:
	void bfmeGoPG(int v, int i, void *c);
	void bfmeSetPG(int i, void *c);
	char m_bfmePad[0xac4];
	int m_bfmeArr[1];
};

void BfmeThingPG::bfmeGoPG(int v, int i, void *c)
{
	bfmeSetPG(i, c);
	m_bfmeArr[i] = v;
}

struct BfmeSubFDA
{
	unsigned char m_bfmeHead[4];
};

struct BfmeHeldFDA
{
	unsigned char m_bfmeHead[0x248];
	BfmeSubFDA m_bfmeSub;
};

struct BfmeResFDA
{
	unsigned char m_bfmeHead[4];
};

class BfmeGlobFDA
{
public:
	BfmeResFDA *bfmeLookFDA(BfmeSubFDA *s);
};

extern BfmeGlobFDA *g_bfmeObjFDA;

struct BfmeThingFDA
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeVirt25FDA(BfmeResFDA *r);
	void bfmeGoFDA();
};

void BfmeThingFDA::bfmeGoFDA()
{
	BfmeSubFDA *s = &(*(BfmeHeldFDA **)((char *)this - 0xe0))->m_bfmeSub;
	BfmeResFDA *r = g_bfmeObjFDA->bfmeLookFDA(s);
	if (r)
		bfmeVirt25FDA(r);
}

struct BfmeNodeFDB
{
	BfmeNodeFDB *m_bfmeNext;
	unsigned char m_bfmePad[4];
	void *m_bfmeItem;
};

struct BfmeThingFDB
{
	void bfmeGoFDB();
	void bfmeRunFDB(void *it);
	unsigned char m_bfmeHead[0x38];
	BfmeNodeFDB *m_bfmeList;
};

void BfmeThingFDB::bfmeGoFDB()
{
	for (BfmeNodeFDB *n = m_bfmeList->m_bfmeNext; n != m_bfmeList; n = n->m_bfmeNext)
		bfmeRunFDB(n->m_bfmeItem);
}

class BfmeSubFDD
{
public:
	void bfmeTwoFDD(void *a, int n);
};

struct BfmeSubHoldFDD
{
	unsigned char m_bfmeHead[0x20];
	BfmeSubFDD m_bfmeSub;
};

struct BfmeHeldFDD
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubHoldFDD *m_bfmeS;
};

class BfmeOwnFDD
{
public:
	void bfmeOneFDD();
};

struct BfmeThingFDD
{
	void bfmeGoFDD(void *a);
	unsigned char m_bfmeHeadA[8];
	BfmeHeldFDD *m_bfmeP;
	unsigned char m_bfmeHeadB[8];
	BfmeOwnFDD m_bfmeOwn;
};

void BfmeThingFDD::bfmeGoFDD(void *a)
{
	BfmeSubHoldFDD *s = m_bfmeP->m_bfmeS;
	if (s)
	{
		m_bfmeOwn.bfmeOneFDD();
		s->m_bfmeSub.bfmeTwoFDD(a, 2);
	}
}

struct BfmeSubFDE
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void *bfmeVirt8FDE();
};

struct BfmeHeldFDE
{
	unsigned char m_bfmeHead[0x200];
	BfmeSubFDE *m_bfmeS;
};

struct BfmeThingFDE
{
	void bfmeGoFDE();
	void bfmeUseFDE(void *r);
	unsigned char m_bfmeHead[8];
	BfmeHeldFDE *m_bfmeP;
};

void BfmeThingFDE::bfmeGoFDE()
{
	BfmeHeldFDE *h = m_bfmeP;
	if (h)
	{
		BfmeSubFDE *s = h->m_bfmeS;
		if (s)
			bfmeUseFDE(s->bfmeVirt8FDE());
	}
}

class BfmeOwnFDH
{
public:
	char bfmeAskFDH(int k);
};

struct BfmeThingFDH
{
	char bfmeGoFDH(void *unused);
};

char BfmeThingFDH::bfmeGoFDH(void *unused)
{
	BfmeOwnFDH *o = *(BfmeOwnFDH **)((char *)this - 0x18);
	if (o->bfmeAskFDH(0x12))
		return false;
	return o->bfmeAskFDH(0x13) == 0;
}


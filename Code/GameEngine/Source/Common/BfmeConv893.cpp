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
	virtual int bfmeVirt8FDE();
};

struct BfmeEntry
{
	char m_bfmeFields[4];
};

class BfmeEntrySink
{
public:
	void bfmeApply(BfmeEntry *entry, unsigned char kind, int active,
		int mode, int enabled);
};

struct BfmeHeldFDE
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
	virtual BfmeEntrySink *bfmeSinkFDE();
	unsigned char m_bfmeHead[0x1fc];
	BfmeSubFDE *m_bfmeS;
};

struct BfmeRangeFDE
{
	BfmeEntry *m_bfmeBegin;
	BfmeEntry *m_bfmeEnd;
	void *m_bfmeUnused;
};

struct BfmeTableFDE
{
	unsigned char m_bfmeHead[0xfd4];
	BfmeRangeFDE m_bfmeFirst[4];
	BfmeRangeFDE m_bfmeSecond[4];
};

struct BfmeThingFDE
{
	void bfmeGoFDE();
	void bfmeUseFDE(int r);
	unsigned char m_bfmeHead[4];
	BfmeTableFDE *m_bfmeTable;
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

void BfmeThingFDE::bfmeUseFDE(int r)
{
	BfmeHeldFDE *held = m_bfmeP;
	if (held != 0)
	{
		BfmeEntrySink *sink = held->bfmeSinkFDE();
		if (sink != 0)
		{
			BfmeTableFDE *table = m_bfmeTable;
			BfmeEntry *first = table->m_bfmeFirst[r].m_bfmeBegin;
			BfmeEntry **firstEnd = &table->m_bfmeFirst[r].m_bfmeEnd;
			if (first != *firstEnd)
			{
				do
				{
					sink->bfmeApply(first, 0, 1, 0, 0);
					++first;
				} while (first != *firstEnd);
			}

			BfmeEntry *second = table->m_bfmeSecond[r].m_bfmeBegin;
			BfmeEntry **secondEnd = &table->m_bfmeSecond[r].m_bfmeEnd;
			if (second != *secondEnd)
			{
				do
				{
					sink->bfmeApply(second, 1, 1, 0, 0);
					++second;
				} while (second != *secondEnd);
			}
		}
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

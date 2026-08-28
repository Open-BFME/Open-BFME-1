class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *a, int z);
};

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();
};

struct BfmeThingFCB
{
	void bfmeGoFCB(void *a);
};

void BfmeThingFCB::bfmeGoFCB(void *a)
{
	BfmeSubFCB *s = *(BfmeSubFCB **)((char *)this - 8);
	if (s)
	{
		s->bfmeCallFCB(a, 0);
		((BfmeOwnFCB *)((char *)this - 0x10))->bfmeAfterFCB();
	}
}

struct BfmePairFCD
{
	void *m_bfmeA;
	void *m_bfmeB;
	char m_bfmeFlag;
};

class BfmeObjFCD
{
public:
	char bfmeCallFCD(void *a, void *b);
};

void bfmeGoFCD(BfmeObjFCD *o, BfmePairFCD *p)
{
	char r = (o->bfmeCallFCD(p->m_bfmeA, p->m_bfmeB) == 0);
	p->m_bfmeFlag |= r;
}

struct BfmeItemFCE
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
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual void bfmeV43();
	virtual void bfmeV44();
	virtual void bfmeV45();
	virtual void bfmeV46();
	virtual void bfmeV47();
	virtual void bfmeV48();
	virtual void bfmeV49();
	virtual bool bfmeVirt50FCE(void *a, void *b);
};

struct BfmeSubFCE
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeItemFCE *m_bfmeIt;
};

struct BfmeOwnFCE
{
	unsigned char m_bfmeHead[0x214];
	BfmeSubFCE *m_bfmeS;
};

struct BfmeThingFCE
{
	bool bfmeGoFCE(void *a, void *b);
};

bool BfmeThingFCE::bfmeGoFCE(void *a, void *b)
{
	BfmeSubFCE *s = (*(BfmeOwnFCE **)((char *)this - 0x18))->m_bfmeS;
	if (s)
	{
		BfmeItemFCE *it = s->m_bfmeIt;
		if (it)
			return it->bfmeVirt50FCE(a, b);
	}
	return false;
}

struct BfmeNodeFCH
{
	BfmeNodeFCH *m_bfmeNext;
	unsigned char m_bfmePad[4];
	void *m_bfmeVal;
};

struct BfmeThingFCH
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
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeVirt36FCH(void *v, int f);
	void *bfmeGoFCH();
	unsigned char m_bfmeHead[0xc0];
	BfmeNodeFCH *m_bfmeList;
};

void *BfmeThingFCH::bfmeGoFCH()
{
	BfmeNodeFCH *head = m_bfmeList;
	BfmeNodeFCH *n = head->m_bfmeNext;
	if (n != head)
	{
		void *v = n->m_bfmeVal;
		bfmeVirt36FCH(v, 1);
		return v;
	}
	return 0;
}


class LocomotorOverridable
{
public:
	LocomotorOverridable *friend_getFinalOverride();

	unsigned char m_bfmeHeadYX[4];
	LocomotorOverridable *m_bfme04YX;
	unsigned char m_bfmeMidYX[0xc0];
	unsigned int m_bfmeC8YX;
};

class BfmeThingYX
{
public:
	int bfmeGetIdYX();
};

class BfmeObjYX
{
public:
	unsigned char m_bfmeHeadYX[4];
	LocomotorOverridable *m_bfme04YX;
	unsigned char m_bfmeMidYX[0x6c];
	int m_bfme74YX;
};

class BFMEActionManager
{
public:
	bool bfmeCheckYX(BfmeObjYX *o, BfmeThingYX *t, int mode);
};

extern BFMEActionManager *TheActionManager;

class BfmeSubYX
{
public:
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
	virtual void bfmeDoYX(int flag, BfmeThingYX *t);
	virtual void bfmeW13();
	virtual void bfmeW14();
	virtual void bfmeW15();
	virtual void bfmeW16();
	virtual void bfmeW17();
	virtual void bfmeW18();
	virtual void bfmeW19();
	virtual bool bfmeTestYX(BfmeThingYX *t);
};

static __forceinline LocomotorOverridable *bfmeFinalYX(LocomotorOverridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_bfme04YX == 0)
		return p;

	return p->m_bfme04YX->friend_getFinalOverride();
}

class BfmeHostYX
{
public:
	void bfmeApplyYX(BfmeThingYX *t, int mode);

	unsigned char m_bfmeHeadYX[8];
	BfmeObjYX *m_bfme08YX;
	unsigned char m_bfmeGapYX[0x334];
	BfmeSubYX m_bfme340YX;
};

void BfmeHostYX::bfmeApplyYX(BfmeThingYX *t, int mode)
{
	BfmeObjYX *o = m_bfme08YX;

	if (!TheActionManager->bfmeCheckYX(o, t, mode))
		return;

	if ((bfmeFinalYX(o->m_bfme04YX)->m_bfmeC8YX & 0x8000) == 0)
	{
		if (!m_bfme340YX.bfmeTestYX(t))
			return;

		int id = t->bfmeGetIdYX();

		if (id != 0 && id != o->m_bfme74YX)
			return;
	}

	m_bfme340YX.bfmeDoYX(1, t);
}

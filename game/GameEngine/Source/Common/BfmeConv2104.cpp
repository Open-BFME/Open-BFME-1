// Retail spells this accessor ?getFinalOverride@Overridable@@QBEPBV1@XZ
// (public const, upstream Overridable.h); the TU-local stand-in carries the
// template layout this body walks, so it takes the defining class/member name.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_bfmeHeadYX[4];
	Overridable *m_nextOverride;
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
	Overridable *m_nextOverride;
	unsigned char m_bfmeMidYX[0x6c];
	int m_bfme74YX;
};

class BFMEActionManager
{
public:
	bool bfmeCheckYX(BfmeObjYX *o, BfmeThingYX *t, int mode);
};

// Retail: 0x012ED700 is EA's ActionManager *TheActionManager (see
// game/GameEngine/Source/Common/System/game_engine_subsystems.h). This TU only
// needs its 0x012ED700-facing view, so declare the canonical symbol and cast.
class ActionManager;
extern ActionManager *TheActionManager;

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

static __forceinline Overridable *bfmeFinalYX(Overridable *p)
{
	if (p == 0)
		return 0;

	if (p->m_nextOverride == 0)
		return p;

	return const_cast<Overridable *>( p->m_nextOverride->getFinalOverride() );
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

	if (!((BFMEActionManager *)TheActionManager)->bfmeCheckYX(o, t, mode))
		return;

	if ((bfmeFinalYX(o->m_nextOverride)->m_bfmeC8YX & 0x8000) == 0)
	{
		if (!m_bfme340YX.bfmeTestYX(t))
			return;

		int id = t->bfmeGetIdYX();

		if (id != 0 && id != o->m_bfme74YX)
			return;
	}

	m_bfme340YX.bfmeDoYX(1, t);
}

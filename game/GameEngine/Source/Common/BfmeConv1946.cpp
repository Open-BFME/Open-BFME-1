typedef bool Bool;

enum KindOfType
{
	KINDOF_INVALID = 0
};

// The kind query this TU calls is Thing::isKindOf(KindOfType) const; the real
// header declares the class, this TU only adds the member it calls.
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const;
#include "Thing/thing.h"
#undef THING_TU_MEMBERS

class BfmeSubEQT
{
public:
	char bfmeAEQT();
	char bfmeBEQT();
};

class BfmeHoldEQT
{
public:
	unsigned char m_bfmeHeadEQT[4];
	BfmeSubEQT *m_bfmeSubEQT;
};

class BfmeThingEQT
{
public:
};

class BfmeBaseEQT
{
public:
	BfmeBaseEQT() { m_bfmeZeroEQT = 0; }

	int m_bfmeZeroEQT;
};

class BfmeObjEQT : public BfmeBaseEQT
{
public:
	BfmeObjEQT(BfmeThingEQT *owner) { m_bfmeOwnerEQT = owner; }
	virtual ~BfmeObjEQT() {}

	char bfmeRunEQT(void *arg);

	BfmeThingEQT *m_bfmeOwnerEQT;
};

char bfmeCheckEQT(BfmeThingEQT *thing, void *arg, BfmeHoldEQT *hold)
{
	if (hold != 0 && arg != 0 &&
		!hold->m_bfmeSubEQT->bfmeAEQT() &&
		!hold->m_bfmeSubEQT->bfmeBEQT() &&
		((Thing *)thing)->isKindOf((KindOfType)0x3a))
	{
		BfmeObjEQT obj(thing);

		if (!obj.bfmeRunEQT(arg))
			return 0;
	}

	return 1;
}

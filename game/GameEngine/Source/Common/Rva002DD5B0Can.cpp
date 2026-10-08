// ?bfmeCanZE@BfmeHostZE@@QAEDPAXPAVBfmeObjZE@@@Z// partial score=0.80 date=2026-09-09
struct BfmeOwnZE
{
	unsigned char m_bfmeHeadZE[0x4b0];
	char m_bfme4B0ZE;
};

class BfmeAgeZE
{
public:
	virtual void bfmeV00ZE();
	virtual void bfmeV04ZE();
	virtual void bfmeV08ZE();
	virtual void bfmeV0CZE();
	virtual void bfmeV10ZE();
	virtual void bfmeV14ZE();
	virtual void bfmeV18ZE();
	virtual void bfmeV1CZE();
	virtual void bfmeV20ZE();
	virtual void bfmeV24ZE();
	virtual void bfmeV28ZE();
	virtual void bfmeV2CZE();
	virtual void bfmeV30ZE();
	virtual void bfmeV34ZE();
	virtual void bfmeV38ZE();
	virtual void bfmeV3CZE();
	virtual unsigned int bfmeAgeZE();
};

class BfmeStateZE
{
public:
	virtual void bfmeW00ZE();
	virtual void bfmeW04ZE();
	virtual void bfmeW08ZE();
	virtual void bfmeW0CZE();
	virtual void bfmeW10ZE();
	virtual void bfmeW14ZE();
	virtual void bfmeW18ZE();
	virtual void bfmeW1CZE();
	virtual void bfmeW20ZE();
	virtual void bfmeW24ZE();
	virtual void bfmeW28ZE();
	virtual void bfmeW2CZE();
	virtual void bfmeW30ZE();
	virtual void bfmeW34ZE();
	virtual void bfmeW38ZE();
	virtual void bfmeW3CZE();
	virtual void bfmeW40ZE();
	virtual void bfmeW44ZE();
	virtual void bfmeW48ZE();
	virtual void bfmeW4CZE();
	virtual void bfmeW50ZE();
	virtual void bfmeW54ZE();
	virtual void bfmeW58ZE();
	virtual void bfmeW5CZE();
	virtual void bfmeW60ZE();
	virtual void bfmeW64ZE();
	virtual int bfmeStateZE();
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadZE[0x3c];
	unsigned int m_bfme3CZE;
};

class GameLogic;
extern GameLogic *TheGameLogic;

// TU-local field view of the retail global at 0x012F0898; the global itself is
// declared with its real type (GameLogic *) so the linked build has one symbol.
static inline Rva00367E30Logic *theBfmeGameLogic()
{
	return (Rva00367E30Logic *)TheGameLogic;
}

// Matched callee rows (callees.py, via ILT): Thing::isKindOf, Thing::getTemplate
// and the address-named test at 0x002DF120.
enum KindOfType { KINDOF_ZE_7 = 7 };
class ThingTemplate;

class Thing
{
public:
	bool isKindOf(KindOfType t) const;
	const ThingTemplate *getTemplate(void) const;
};

class Rva002DF120
{
public:
	unsigned char test(void *a, void *b);
};

class BfmeObjZE
{
public:

	unsigned char m_bfmeHeadZE[0x1fc];
	BfmeStateZE *m_bfme1FCZE;
	BfmeAgeZE *m_bfme200ZE;
	unsigned char m_bfmeMidZE[0x214 - 0x204];
	BfmeObjZE *m_bfme214ZE;
	unsigned char m_bfmeMid2ZE[0x344 - 0x218];
	unsigned char m_bfme344ZE;
};

class BfmeHostZE
{
public:
	char bfmeCanZE(void *a1, BfmeObjZE *obj);
};


char BfmeHostZE::bfmeCanZE(void *a1, BfmeObjZE *obj)
{
	if (obj == 0)
		return 0;
	else
	{
	if (obj->m_bfme344ZE & 1)
	{
		BfmeAgeZE *age = obj->m_bfme200ZE;

		if (age == 0)
			return 0;

		unsigned int limit = theBfmeGameLogic()->m_bfme3CZE;

		if (age->bfmeAgeZE() < limit)
			return 0;
	}

	if (!((Rva002DF120 *)this)->test(a1, obj))
		return 0;

	BfmeStateZE *state = obj->m_bfme1FCZE;
	if (state != 0 && state->bfmeStateZE() != 0)
		return 0;

	if (obj->m_bfme214ZE != 0 && !((Thing *)obj->m_bfme214ZE)->isKindOf((KindOfType)0x6c))
		return 0;

	if (((Thing *)obj)->isKindOf((KindOfType)0x5d))
		return 0;

	if (((Thing *)obj)->isKindOf((KindOfType)7))
		return 0;

	return ((const BfmeOwnZE *)((Thing *)obj)->getTemplate())->m_bfme4B0ZE == 0;
	}
}

// ?bfmeApplyERN@@YGDPAX0@Z
// partial score=0.9 date=2026-09-09
// 233/230. Fourth member of the nameToKey family at 0x0032xxxx: global
// vslot 26 lookup, CastleBehavior function-local static, module find, then a
// stack handle whose destructor releases a ref-counted object.
// Everything matches except that retail caches the handle's pointer member in
// esi once, right after the out-of-line constructor, and uses that ONE value
// for both call arguments AND the destructor's null test and receiver:
//     mov esi,[esp+0x20] / push esi / ... / push esi / ... / test esi,esi
// MSVC reloads the member for each use because the constructor let &owner
// escape. Variants measured:
//   member read three times (this file)            233
//   member read once into a local, dtor reads member  234
//   as above plus a local inside the dtor             234
// The local form fixes the two argument uses but adds mov esi,eax and leaves
// the destructor reloading, which is a net loss.
// Untried: an empty-base guard so the destructor emits nothing on the normal
// path with an explicit release in the body -- see memory
// empty-guard-base-gives-seh-frame.
// Pins are already in symbols.csv.
class BfmeThingERN;

class BfmeGlobalERN
{
public:
	virtual void bfmeSlot00ERN();
	virtual void bfmeSlot01ERN();
	virtual void bfmeSlot02ERN();
	virtual void bfmeSlot03ERN();
	virtual void bfmeSlot04ERN();
	virtual void bfmeSlot05ERN();
	virtual void bfmeSlot06ERN();
	virtual void bfmeSlot07ERN();
	virtual void bfmeSlot08ERN();
	virtual void bfmeSlot09ERN();
	virtual void bfmeSlot10ERN();
	virtual void bfmeSlot11ERN();
	virtual void bfmeSlot12ERN();
	virtual void bfmeSlot13ERN();
	virtual void bfmeSlot14ERN();
	virtual void bfmeSlot15ERN();
	virtual void bfmeSlot16ERN();
	virtual void bfmeSlot17ERN();
	virtual void bfmeSlot18ERN();
	virtual void bfmeSlot19ERN();
	virtual void bfmeSlot20ERN();
	virtual void bfmeSlot21ERN();
	virtual void bfmeSlot22ERN();
	virtual void bfmeSlot23ERN();
	virtual void bfmeSlot24ERN();
	virtual void bfmeSlot25ERN();
	virtual BfmeThingERN *bfmeSlot26ERN(void *handle);
};

extern BfmeGlobalERN *g_bfmeGlobalERN;

class BfmeObjERN
{
public:
	virtual void bfmeReleaseERN(int flag);
};

class BfmeHandleERN
{
public:
	BfmeHandleERN();

	~BfmeHandleERN()
	{
		if (m_bfmePtrERN != 0)
			m_bfmePtrERN->bfmeReleaseERN(1);
	}

	BfmeObjERN *m_bfmePtrERN;
};

class BfmeModERN
{
public:
	char bfmeTestERN(BfmeObjERN *obj);
};

class BfmeThingERN
{
public:
	BfmeModERN *bfmeFindERN(int key);
};

class BfmeKeyGenERN
{
public:
	int bfmeNameToKeyERN(const char *name);
};

extern BfmeKeyGenERN *g_bfmeKeyGenERN;

void bfmeSendERN(void *first, BfmeObjERN *obj);

char __stdcall bfmeApplyERN(void *first, void *handle)
{
	BfmeThingERN *thing = g_bfmeGlobalERN->bfmeSlot26ERN(handle);

	if (thing == 0)
		return 0;

	static int s_bfmeKeyERN =
		g_bfmeKeyGenERN->bfmeNameToKeyERN("CastleBehavior");

	BfmeModERN *mod = thing->bfmeFindERN(s_bfmeKeyERN);

	if (mod == 0)
		return 0;

	BfmeHandleERN owner;
	BfmeObjERN *ptr = owner.m_bfmePtrERN;

	bfmeSendERN(first, ptr);

	char result = mod->bfmeTestERN(ptr) != 0;

	if (ptr != 0)
		ptr->bfmeReleaseERN(1);
	owner.m_bfmePtrERN = 0;

	return result;
}

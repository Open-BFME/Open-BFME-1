#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
// stlport
#include <vector>

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp. This TU
// previously spelled it ?TheBfmeGameLogic@@3PAURva00367E30Logic@@A,
// ?g_bfmeObjFBA@@3PAUBfmeGlobFBA@@A and ?g_bfmeObjFBD@@3PAVBfmeGlobFBD@@A --
// three names for the same address, so three unresolvable symbols. All three
// now reference the one canonical spelling and read their fields through these
// TU-local views of the retail layout.
class GameLogic;

extern GameLogic *TheGameLogic;

struct BfmeGlobFBA
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeMax;
};

static __forceinline BfmeGlobFBA *g_bfmeObjFBA()
{
	return (BfmeGlobFBA *)TheGameLogic;
}

struct BfmeThingFBA
{
	float bfmeGoFBA(void *a);
	void bfmeUpdFBA(void *a);
	unsigned char m_bfmeHead[0x358];
	float m_bfmeF;
	unsigned int m_bfmeN;
};

float BfmeThingFBA::bfmeGoFBA(void *a)
{
	if (m_bfmeN < g_bfmeObjFBA()->m_bfmeMax)
		bfmeUpdFBA(a);
	return m_bfmeF;
}

class BfmeGlobFBB
{
public:
	char bfmeCallFBB(void *x, void *a, void *y);
};

// The retail global at 0x012ED700 is EA's `ActionManager *TheActionManager`
// (see game/GameEngine/Source/Common/System/game_engine_subsystems.h). This TU
// previously spelled it ?g_bfmeObjFBB@@3PAVBfmeGlobFBB@@A; it now references the
// one canonical spelling and reads through this TU-local view of the pointee.
class ActionManager;
extern ActionManager *TheActionManager;

struct BfmeThingFBB
{
	bool bfmeGoFBB(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfme8;
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfme10;
};

bool BfmeThingFBB::bfmeGoFBB(void *a)
{
	return ((BfmeGlobFBB *)TheActionManager)->bfmeCallFBB(m_bfme8, a, m_bfme10) == m_bfmeC;
}

class BfmeObjFBC
{
public:
	char bfmeCallFBC(void *x, void *a, int z, void *y);
};

struct BfmeThingFBC
{
	bool bfmeGoFBC(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfme8;
	BfmeObjFBC *m_bfmeObj;
	char m_bfme10;
	unsigned char m_bfmePad[3];
	void *m_bfme14;
};

bool BfmeThingFBC::bfmeGoFBC(void *a)
{
	return m_bfmeObj->bfmeCallFBC(m_bfme8, a, 0, m_bfme14) == m_bfme10;
}

struct BfmeObjFBD
{
	bool bfmeAskFBD();
};

class BfmeGlobFBD
{
public:
	BfmeObjFBD *bfmeFindFBD(void *p);
};

static __forceinline BfmeGlobFBD *g_bfmeObjFBD()
{
	return (BfmeGlobFBD *)TheGameLogic;
}

struct BfmeThingFBD
{
	bool bfmeGoFBD();
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

bool BfmeThingFBD::bfmeGoFBD()
{
	BfmeObjFBD *o = g_bfmeObjFBD()->bfmeFindFBD(m_bfmeP);
	if (o && o->bfmeAskFBD())
		return true;
	return false;
}

struct BfmeItemFBG
{
	void bfmeRunFBG(int f);
};

struct BfmeThingFBG
{
	void bfmeGoFBG();
	unsigned char m_bfmeHead[8];
	BfmeItemFBG *m_bfmeArr[4];
};

void BfmeThingFBG::bfmeGoFBG()
{
	for (int i = 0; i < 4; ++i)
	{
		BfmeItemFBG *p = m_bfmeArr[i];
		if (p)
			p->bfmeRunFBG(0);
	}
}

class Object
{
};

static __forceinline void setFilterVptr(void *filter, unsigned int value)
{
	*(unsigned int *)filter = value;
}

class __declspec(novtable) PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() { setFilterVptr(this, (unsigned int)__identifier("??_7PartitionFilter@@6B@")); }
	virtual bool allow(Object *);
	virtual int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class __declspec(novtable) Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
	{
		setFilterVptr(this, (unsigned int)__identifier("??_7Rva0025ED50ObjectFilter@@6B@"));
		m_object = object;
	}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual bool allow(Object *);
	Object *m_object;
};

class __declspec(novtable) Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() { setFilterVptr(this, (unsigned int)__identifier("??_7Rva0025ED50RootFilter@@6B@")); }
	virtual ~Rva0025ED50RootFilter() {}
	virtual bool allow(Object *);
};

class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, int flags, bool match)
	{
		setFilterVptr(this, (unsigned int)__identifier("??_7PartitionFilterRelationship@@6B@"));
		m_object = object;
		m_flags = flags;
		m_match = match;
	}
	virtual ~PartitionFilterRelationship() {}
	virtual bool allow(Object *);
	virtual int getPlayerMask();
	Object *m_object;
	int m_flags;
	bool m_match;
};

typedef void (__cdecl *VftSlot)(void);

// The retail vftables the four filter constructors install, spelled with their
// real decorated names (targets/game/reverse/dir32_addresses.csv records
// ??_7PartitionFilter@@6B@ at 0x01083B5C and ??_7PartitionFilterRelationship@@6B@
// at 0x01085DC0). Each class has three virtuals, so the vftable is three
// const slots; declaring them through __identifier() binds the defining names
// directly, with no linker aliasing. The declarations follow the
// class definitions: MSVC rejects them ahead of a class that implicitly declares
// its own vftable.
extern "C" const VftSlot __identifier("??_7PartitionFilter@@6B@")[3];
extern "C" const VftSlot __identifier("??_7Rva0025ED50ObjectFilter@@6B@")[3];
extern "C" const VftSlot __identifier("??_7Rva0025ED50RootFilter@@6B@")[3];
extern "C" const VftSlot __identifier("??_7PartitionFilterRelationship@@6B@")[3];

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vptr;
	Overridable *m_nextOverride;
};

class BfmeFBAThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x3f4];
	float m_float3FC;
};

class BfmeFBAObjectView
{
public:
	const BfmeFBAThingTemplate *getTemplate() const
	{
		return *(BfmeFBAThingTemplate * const *)((const char *)this + 4);
	}
};

struct BfmeFBAResultEntry
{
	Object *m_object;
	unsigned int m_distanceBits;
};

struct BfmeFBAResultData
{
	std::vector<BfmeFBAResultEntry> m_entries;
	std::vector<BfmeFBAResultEntry>::iterator m_current;
	int m_references;
};

struct BfmeWideResult
{
	BfmeFBAResultData *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
	{
		if (--value->m_references == 0)
			delete value;
	}

	Object *next() const
	{
		if (value->m_current == value->m_entries.end())
			return 0;
		Object *object = (value->m_current++)->m_object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int position, int radius, int mode,
		int filter, int includeSelf);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

struct Rva00367E30Logic
{
	unsigned char m_pad000[0x3c];
	unsigned int m_frame;
};

static __forceinline Rva00367E30Logic *TheBfmeGameLogic()
{
	return (Rva00367E30Logic *)TheGameLogic;
}

void BfmeThingFBA::bfmeUpdFBA(void *a)
{
	BfmeWideResult result = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
		(int)((char *)this + 0x38), *(int *)&a, 0,
		(int)PartitionFilterRelationship((Object *)this, 1, false).link(
			Rva0025ED50RootFilter().link(&Rva0025ED50ObjectFilter((Object *)this))),
		0);
	float total = 0.0f;
	Object *nearby;
	while ((nearby = result.next()) != 0)
	{
		const BfmeFBAThingTemplate *objectTemplate =
			((BfmeFBAObjectView *)nearby)->getTemplate();
		if (objectTemplate == 0)
		{
			__asm {
				fld total
				xor eax, eax
				fadd dword ptr [eax + 0x3fc]
				fstp total
			}
			continue;
		}
		if (objectTemplate->m_nextOverride != 0)
			objectTemplate = (const BfmeFBAThingTemplate *)
				objectTemplate->m_nextOverride->getFinalOverride();
		total += objectTemplate->m_float3FC;
	}
	m_bfmeF = total;
	m_bfmeN = TheBfmeGameLogic()->m_frame + 25;
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common
// stlport
// Retail 0x0058D770, 90 bytes: byte-for-byte the shape of the matched rank
// helper 0x004B24F0 (Rva004B24F0.cpp). It reads an object's experience-level
// node through TheExperienceLevelSystem (ILT 0x0000EDC7) and returns that
// node's rank through ILT 0x000012A8, or 0 when the ILT 0x0000DFC1 gate fails.
// The object arrives in EAX: its only caller, the 0x00594FD0 dump, loads EAX
// and calls directly, so the helper is static and a stub caller makes the
// compiler emit that private convention. Identity stays address-derived.

#include <list>
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "Thing/GameLogicObjectLookup.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtbl;
	Overridable *m_nextOverride;		//retail +0x04
};

class ThingTemplateRankView : public Overridable
{
public:
	char m_pad08[0xd0 - 0x08];
	unsigned int m_kindOfD0;			//retail +0xd0
	char m_padD4[0x4d0 - 0xd4];
	int m_order4D0;						//retail +0x4d0
};

template <class T>
class OVERRIDE
{
public:
	operator const T *() const { return operator*(); }
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

	const T *m_overridable;
};

class Object
{
public:
	const ThingTemplateRankView *getTemplate() const { return m_template; }

	void *m_vtbl;
	OVERRIDE<ThingTemplateRankView> m_template;	//retail +0x04
	char m_pad08[0x74 - 0x08];
	int m_id;							//retail +0x74
	char m_pad78[0x210 - 0x78];
	class Gen_001b2030 *m_210;			//retail +0x210
};

struct Iterator004B25D0
{
	void *a;
	void *b;
	Iterator004B25D0() {}
	Iterator004B25D0(const Iterator004B25D0 &other) : a(other.a), b(other.b) {}
};

// The ABI view of the list lookup, whose matched ledger row names this type.
struct Rva0037F190Result;

class ExperienceLevelSystem
{
public:
	void rva0037F190(Rva0037F190Result *, Object *);
	bool at0037E810(Iterator004B25D0);
	int at0037D810(Iterator004B25D0);
	struct Rva0037F220Iterator rva0037F220(struct Rva0037F220Iterator);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

struct BfmeFlagHolder;
class BfmeFlagCandidate;
struct BfmeThingEGA;
bool __stdcall bfmeMpSkirmishFlagGate(BfmeFlagHolder *, BfmeFlagCandidate *);
void *__stdcall bfmeGoEGAa(void *, BfmeThingEGA *);

typedef bool (ExperienceLevelSystem::*MpSkirmishFlagGateCall)(Iterator004B25D0);
__forceinline MpSkirmishFlagGateCall Rva0037E810Binding()
{
	union { bool (__stdcall *raw)(BfmeFlagHolder *, BfmeFlagCandidate *); MpSkirmishFlagGateCall member; } fn;
	fn.raw = bfmeMpSkirmishFlagGate;
	return fn.member;
}

typedef int (ExperienceLevelSystem::*GoEGAaCall)(Iterator004B25D0);
__forceinline GoEGAaCall Rva0037D810Binding()
{
	union { void *(__stdcall *raw)(void *, BfmeThingEGA *); GoEGAaCall member; } fn;
	fn.raw = bfmeGoEGAa;
	return fn.member;
}

// ?rank0058D770@@YAHPAVObject@@@Z
static __declspec(noinline) int rank0058D770(Object *object)
{
	Iterator004B25D0 node;
	TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&node, object);
	MpSkirmishFlagGateCall check = Rva0037E810Binding();
	if (!(TheExperienceLevelSystem->*check)(node))
		return 0;
	GoEGAaCall rank = Rva0037D810Binding();
	return (TheExperienceLevelSystem->*rank)(node);
}

// Retail 0x0058B610, 415 bytes: a static helper with a private register
// convention (object in ESI, rank out-pointer in EDI, fraction out-pointer in
// EBX), called directly by the 0x00593440 and 0x00595E60 dumps. It stores the
// object's experience rank, then the fraction of the way from this level's
// threshold (ILT 0x0000BC21) to the next level's, clamped to [0,1], or -1
// when there is no reachable next level. Identity stays address-derived.
struct Rva0037F220Iterator
{
	void *m_sentinel;
	void *m_current;
	Rva0037F220Iterator() {}
	Rva0037F220Iterator(const Rva0037F220Iterator &other) : m_sentinel(other.m_sentinel), m_current(other.m_current) {}
};

class Gen_001b2030
{
public:
	bool m(int);

	char m_pad00[0x0c];
	float m_0c;							//retail +0x0c
};

class BfmeSinkBUB
{
public:
	bool bfmeAskBUB(void *);
};

struct BfmeThingEGB;
void *__stdcall bfmeGoEGAb(void *, BfmeThingEGB *);

typedef int (ExperienceLevelSystem::*GoEGAbCall)(Iterator004B25D0);
__forceinline GoEGAbCall Rva0037D840Binding()
{
	union { void *(__stdcall *raw)(void *, BfmeThingEGB *); GoEGAbCall member; } fn;
	fn.raw = bfmeGoEGAb;
	return fn.member;
}


// ?rva0058B610@@YA_NPAVObject@@PAHPAM@Z
static __declspec(noinline) bool rva0058B610(Object *object, int *rank, float *fraction)
{
	Iterator004B25D0 node;
	TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&node, object);
	MpSkirmishFlagGateCall check = Rva0037E810Binding();
	if (!(TheExperienceLevelSystem->*check)(node))
		return false;
	GoEGAaCall rankOf = Rva0037D810Binding();
	*rank = (TheExperienceLevelSystem->*rankOf)(node);
	Rva0037F220Iterator nextRaw = TheExperienceLevelSystem->rva0037F220(*(Rva0037F220Iterator *)&node);
	const Iterator004B25D0 &next = *(Iterator004B25D0 *)&nextRaw;
	if ((TheExperienceLevelSystem->*check)(next)
		&& ((BfmeSinkBUB *)TheExperienceLevelSystem)->bfmeAskBUB(object))
	{
		int cap;
		if (!object->m_210->m((int)&cap) || *rank < cap)
		{
			float experience = object->m_210->m_0c;
			GoEGAbCall threshold = Rva0037D840Binding();
			float low = (float)(TheExperienceLevelSystem->*threshold)(node);
			float high = (float)(TheExperienceLevelSystem->*threshold)(next);
			if (low < high)
			{
				*fraction = (experience - low) / (high - low);
				if (*fraction < 0.0f)
					*fraction = 0.0f;
				else if (*fraction > 1.0f)
					*fraction = 1.0f;
				goto done;
			}
		}
	}
	*fraction = -1.0f;
done:
	return *rank > 1 || *fraction >= 0.0f;
}

// This caller exists only to make the compiler emit the helper's private
// convention, as retail's 0x00593440 and 0x00595E60 callers do.
// ?rva0058B610Caller@@YAMPAVObject@@@Z absent-from-retail
float rva0058B610Caller(Object *object)
{
	int rank;
	float fraction;
	if (!rva0058B610(object, &rank, &fraction))
		return 0.0f;
	return fraction + rank;
}

// Retail 0x00594FD0, 308 bytes (ret 4 at +0x131, int3 after): the helper's
// only caller. The matched BfmeHostBU::bfmeDieBU (BfmeConv1919.cpp) calls it
// through ILT 0x0003C0AB on TheAptPalantir's BfmeSubBU member. It keeps a
// list of {object id, rank, 0} entries: a qualifying object (template word
// +0xD0 bit 0x2000000 and a selected portrait) not yet listed is inserted in
// template +0x4D0 order, or appended once TheGameLogic +0x3C reaches 6.
struct BfmeRankEntry
{
	int id;
	int rank;
	int zero;
};

class BfmeHostBU;

class BfmeSubBU
{
public:
	void bfmeUnlinkBU(BfmeHostBU *host);

	int m_00;
	_STL::list<BfmeRankEntry> m_list;	//retail +0x04
};

class BfmeSubBU;

struct GameLogicRankView
{
	char m_pad00[0x3c];
	unsigned int m_3c;					//retail +0x3c
};

extern GameLogic *TheGameLogic;

class ThingTemplatePortraitShim;
class Image;
const Image * __cdecl _bfme_getSelectedPortraitImage(
	const ThingTemplatePortraitShim *portraitTemplate,
	const ThingTemplatePortraitShim *objectTemplate);

void BfmeSubBU::bfmeUnlinkBU(BfmeHostBU *host)
{
	Object *object = (Object *)host;

	if (!(object->getTemplate()->m_kindOfD0 & 0x2000000))
		return;

	if (!_bfme_getSelectedPortraitImage((const ThingTemplatePortraitShim *)object->getTemplate(), (const ThingTemplatePortraitShim *)object))
		return;

	_STL::list<BfmeRankEntry>::iterator it;
	for (it = m_list.begin(); it != m_list.end(); ++it)
	{
		if ((*it).id == object->m_id)
			return;
	}

	BfmeRankEntry entry;
	entry.id = object->m_id;
	entry.rank = rank0058D770(object);
	entry.zero = 0;

	if (((GameLogicRankView *)TheGameLogic)->m_3c < 6)
	{
		int order = object->getTemplate()->m_order4D0;
		_STL::list<BfmeRankEntry>::iterator end = m_list.end();
		// The foldable `this &&` term keeps retail's unrotated loop (test at
		// the head, back-edge jmp); a plain condition gets rotated.
		for (it = m_list.begin(); this && it != end; ++it)
		{
			Object *other = TheGameLogic->findObjectByID((*it).id);
			if (other && order < other->getTemplate()->m_order4D0)
				break;
		}
		m_list.insert(it, entry);
	}
	else
		m_list.push_back(entry);
}

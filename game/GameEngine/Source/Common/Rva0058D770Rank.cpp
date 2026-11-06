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

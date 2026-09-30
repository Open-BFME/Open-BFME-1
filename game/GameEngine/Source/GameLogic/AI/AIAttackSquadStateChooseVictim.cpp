// ?chooseVictim@AIAttackSquadState@@QAEPAVObject@@XZ
// byte-exact: 0 differing bytes of 949 (probe.py EXACT, modulo relocation slots)
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?chooseVictim@AIAttackSquadState@@QAEPAVObject@@XZ   retail 0x0017D2F0..0x0017D6A5 (949 bytes)
//
// IDENTITY.  Two matched callers in AIAttackSquadStateOnEnter.cpp name the
// symbol out of landed code (onEnter and update), which outranks every
// heuristic.  The Zero Hour twin is AIStates.cpp:5928.  The lift's arity
// (targets/game/reverse/lift_arity.csv:96) is consistent and 949 bytes runs
// through the final ret, so the extent is right too.
//
// WHAT IS BFME-ONLY HERE.  Three blocks have no counterpart in the twin:
//   +0x5B   a cached last-damage-source fast path keyed on Object+0x3A4,
//   +0xE3   a nearest-in-squad scan that replaces the twin's difficulty switch,
//   +0x20E  a byte_28-gated PartitionManager fallback with five chained filters.
// The 0x5B fast path clears Object+0x3A4 when the cached object is gone, so the
// field is a per-owner cache slot and not a member the ZH layout records.
//
// THE FRAME IS CLOSED.  sub esp,0xF0 with three SEH-pushed slots and four
// saved registers puts the body at E-0x10C.  Every local slot in that frame is
// accounted for: this-spill E-0xE8, best victim E-0xEC, weapon E-0xF0, distance
// temp E-0xF4, best distance E-0xF8, in-range flag E-0xF9, the five filter
// objects E-0xE4/E-0xCC/E-0xC0/E-0x94/E-0x84 plus the 24-byte kind-of temp at
// E-0xAC, the live-object vector pointer E-0xD0, the object-id array at
// E-0x4C and the SEH trystate dword at E-0x04.  The filter sizes add up
// exactly to the gap before the array, so nothing is unaccounted for.
//
// The 0.25f pooled at __real@3e800000 (0x01083B6C) is not in symbols.csv; it
// is a plain float literal here, and the build's pooled-constant resolution
// places it.
//
// The four link() calls all have rel1 in ecx.  That is why the chain is spelled
// as four statements on the root instead of the nested rel1.link(a.link(b))
// form the sibling TUs use: a nested chain would move the receiver.
//
// EH.  The three unwind stores are 0 / 1 / 4, and the one that gates the
// AcceptByKindOf call is only there because that ctor can throw.  Retail's own
// body for it (0x000C3DD0) is a straight run of dword copies with no EH frame
// and no call, so it provably cannot: declaring it throw() is what removes
// retail-absent state 2 and the 8 bytes that used to shift the whole tail.
// Tried and INERT here: `#define _STLP_NO_EXCEPTIONS 1` before <bitset> (the
// eh_levers `stlp` lever) leaves this body's bytes unchanged.
//
// The two x87 distance expressions are deliberately spelled differently, and
// both go through named per-axis Reals.  Loop 1 squares the sum of two bare
// products; loop 2 scales each product by 0.25f on the right.  Written as one
// expression, in either term order, MSVC 7.1 canonicalises the commutative add
// and emits owner.y first where retail loads owner.x (measured: 4 bytes at
// +0x170..+0x17F).  The constant stays a literal for the same reason -- see
// docs/shape_levers.md, "An x87 product loads its operands in the wrong order".
#include <bitset>
#include <float.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;
};

class Object;

// ?TheBfmeGameLogic@@3PAURva00367E30Logic@@A.  The lookup is the
// ?findObjectByID@GameLogic@@QAEPAVObject@@H@Z ILT at 0x0001F253, reached
// through this singleton in all three call sites.
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class Rva00367E30Logic : public GameLogic
{
};

extern Rva00367E30Logic *TheBfmeGameLogic;

// ?bfmeCheckAttackView@Pathfinder@@QAEHPAVObject@@PAX@Z, matched at
// 0x003EA960 in PathfinderAttackViewForwarders.cpp.  It returns a signed
// count and fills the caller's buffer, which is why the call site compares the
// result with jle and why the array holds ObjectIDs rather than Object*.
class Pathfinder
{
public:
	int bfmeCheckAttackView(Object *object, void *targetPosition);
};

// ?TheAI@@3PAVAI@@A; the Goal-Object LOS reads the pathfinder at +0x0C.
class AI
{
public:
	unsigned char m_unreconstructed_00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

// ?isWithinAttackRange@Weapon@@QBE_NPBVObject@@0H@Z, matched at 0x001E8930.
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// DamageInfoInput::m_sourceID is the only member this body reads; the Zero
// Hour DamageInfoInput derives from Snapshot, which is why the id is not at +0.
class DamageInfo
{
public:
	unsigned char m_unreconstructed_00[0x08];
	Int m_sourceID;
};

// Retail reaches getLastDamageInfo through vtable slot 15 (call [eax+0x3C]).
class BodyModuleInterface
{
public:
#define BMI_SLOT(n) virtual void slot##n() = 0;
	BMI_SLOT(00) BMI_SLOT(04) BMI_SLOT(08) BMI_SLOT(0c) BMI_SLOT(10)
	BMI_SLOT(14) BMI_SLOT(18) BMI_SLOT(1c) BMI_SLOT(20) BMI_SLOT(24)
	BMI_SLOT(28) BMI_SLOT(2c) BMI_SLOT(30) BMI_SLOT(34) BMI_SLOT(38)
#undef BMI_SLOT
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};

// ?getMoodMatrixValue@AIUpdateInterface@@QBEIXZ, pinned at 0x0001BB3F.  The
// receiver is Object+0x204, the AIUpdateInterface the landed onEnter/update
// bodies call.
class AIUpdateInterface
{
public:
	UnsignedInt getMoodMatrixValue() const;
};

// Object+0x208 is only null-tested and then asked a yes/no question whose
// result is tested in AL.  `char` is the return type that reaches the ledger:
// MSVC 7.1 decorates plain char as `D` (its table has C for signed char and
// D for char), so this mangles to ?bfmeBusyNW@BfmeCheckerNW@@QAEDXZ, which is
// the pin already at 0x00006EEC -- the same declaration the landed
// BfmeConv1785.cpp (0x0017D280, a neighbour of this body) uses for the same
// ILT.  An `unsigned char` return would mangle to E and leave the call
// unresolved.
class BfmeCheckerNW
{
public:
	char bfmeBusyNW(void);
};

// ?getFinalOverride@Overridable@@QBEPBV1@Z, pinned at 0x000022BB.  The chain
// node's next pointer is at +4, so the view carries its own vptr slot.  The
// return type is this class's own pointer, which is the spelling symbols.csv
// already carries for that ILT; a `const void *` return mangles to PBX and
// resolves to nothing.
class Overridable
{
public:
	void *m_vtable;
	Overridable *m_next;
	const Overridable *getFinalOverride() const;
};

// The +0xC8 kind-of byte and the +0xCC kind-of word are the same pair the
// matched PartitionFilterRejectBuildings::allow reads off the resolved
// template (PartitionFilterRejectBuildings.cpp).
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_08[0xc8 - 0x08];
	volatile char m_kindOfStructureByte;
	unsigned char m_unreconstructed_c9[3];
	UnsignedInt m_kindOfWord1;
};

// Object layout: every offset below is read by this body.  The first four are
// witnessed by the landed AIAttackSquadStateOnEnter.cpp Object view (+0x1C on
// State, +0x90 status, +0x204 m_ai, +0x344 private status) and by
// PartitionFilterRejectBuildings.cpp (+0x04 template, +0x38 position).
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);

	void *m_vtable;					// +0x00
	ThingTemplate *m_thingTemplate;	// +0x04
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;				// +0x38
	unsigned char m_unreconstructed_44[0x90 - 0x44];
	UnsignedInt m_status;			// +0x90
	unsigned char m_unreconstructed_94[0x200 - 0x94];
	BodyModuleInterface *m_bodyModule;	// +0x200
	AIUpdateInterface *m_ai;			// +0x204
	void *dword_208;					// +0x208
	unsigned char m_unreconstructed_20c[0x344 - 0x20c];
	Bool m_privateStatus;			// +0x344
	unsigned char m_unreconstructed_345[0x3a4 - 0x345];
	Int dword_3A4;					// +0x3a4, last-known damage source id
};

// ?bfmeCompact@Gen_0018BC70@@QAEPAVBfmeVecAK@@_N@Z, matched at 0x0018BC70.
// The receiver is the goal squad (StateMachine+0x54 in the Zero Hour twin) and
// the return value is the squad's live-object vector, walked as Object* here.
class BfmeVecAK
{
public:
	Object **m_bfmeStart;
	Object **m_bfmeFinish;
	Object **m_bfmeEnd;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
};

// ?bfmeAskEQ@BfmeThingEQ@@QAEEPAX@Z, matched at 0x009F2A70.  Retail asks the
// filter chain root, so the first relationship filter is viewed as the asker.
class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *what);
};

// The $0MA decoration on BitFlags is established by the typed retail Player
// ILT and by PlayerCountObjects.cpp; the same width-only view and the
// kInit-ctor spelling are the landed precedent in
// ScriptEngine/TeamCommandQuery002FBC90.cpp (three matched bodies) and
// System/CrateSystem.cpp.  The single-bit ctor is inline because retail builds
// the mask in place here (xor/store/or at +0x260), not through a call.
template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

// BFME's kind-of list runs past Zero Hour's, so the mask is the wide
// 192-bit/24-byte one retail stores.  Only the width is provable here (six
// dwords at +0x260), not the names past the shim's list, so -- as
// CrateSystem.cpp does -- this is a width-only KindOfType rather than an
// invented enumerator.  Index 129 is what the emitted `or eax,2` on word 4
// fixes (129 = 4*32+1); no evidence names it.
enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_COUNT = 192
};

typedef BitFlags<KINDOF_COUNT> KindOfMaskType;

#define MAKE_KINDOF_MASK(k) KindOfMaskType(KindOfMaskType::kInit, (k))

// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B at 0x012ED8B8, six zero dwords.
extern const KindOfMaskType KINDOFMASK_NONE;

// ?link@PartitionFilter@@QAEPAV1@PAV1@@Z, pinned at 0x009F2AE0.  The body
// walks to the tail of the m_next chain and appends, so each of the four calls
// below leaves the chain root as the receiver.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

extern "C" void *bfmeVftPartitionFilterRelationship[];
#pragma comment(linker, "/alternatename:_bfmeVftPartitionFilterRelationship=??_7PartitionFilterRelationship@@6B@")
extern const void *g_010956C4[];
extern "C" void *bfmeVftPartitionFilterSameMapStatus[];
#pragma comment(linker, "/alternatename:_bfmeVftPartitionFilterSameMapStatus=??_7PartitionFilterSameMapStatus@@6B@")

static __forceinline void setFilterVptr(void *filter, UnsignedInt value)
{
	*reinterpret_cast<UnsignedInt *>(filter) = value;
}

// 0x01085DC0, the table the landed AIFindAllyNear.cpp installs for this class.
class __declspec(novtable) PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
	{
		setFilterVptr(this, (UnsignedInt)bfmeVftPartitionFilterRelationship);
		m_object = object;
		m_flags = flags;
		m_match = match;
	}
	virtual ~PartitionFilterRelationship() {}

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

// 0x010956C4.  BFME gives this same 20-byte shape a second table in other TUs
// (AIMeleeReAcquireState_update.cpp, Rva00203DB0AiCompare.cpp and
// Rva00189E80ObjectVisionQuery.cpp), so the address is per-TU, not per-class.
// The trailing member is a dword here, which is why it is not spelled as
// PartitionFilterRelationship's Bool.
class __declspec(novtable) Rva0017D2F0DwordTailFilter : public PartitionFilter
{
public:
	Rva0017D2F0DwordTailFilter(const Object *object, Int flags, int state)
	{
		setFilterVptr(this, (UnsignedInt)g_010956C4);
		m_object = object;
		m_flags = flags;
		m_state = state;
	}
	virtual ~Rva0017D2F0DwordTailFilter() {}

	const Object *m_object;
	Int m_flags;
	int m_state;
};

// 0x01085DD0, installed by the landed AIFindAllyNear.cpp for this 12-byte shape.
class __declspec(novtable) Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object)
	{
		setFilterVptr(this, (UnsignedInt)bfmeVftPartitionFilterSameMapStatus);
		m_object = object;
	}
	virtual ~Rva0025ED50ObjectFilter() {}

	Object *m_object;
};

// ??0PartitionFilterRejectBuildings@@QAE@PBVObject@@@Z, matched at 0x001DCE00.
// Its own body installs 0x0109FB64 and stores this+4=0, this+8=argument and a
// byte at +0xC, which is what fixes the 16-byte layout here.
class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	PartitionFilterRejectBuildings(const Object *object);
	virtual ~PartitionFilterRejectBuildings() {}

	const Object *m_self;
	Bool m_acquireEnemies;
};

// ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z, ILT at
// 0x000382FD to the matched 0x000C3DD0, which copies two 24-byte masks --
// [esp+4] into this+8 and [esp+0xC] into this+0x20 -- and so fixes both the
// 56-byte size and which mask lands where.  Retail pushes the empty mask
// first, so the leading parameter is the mustBeClear one.  The constructor is
// out of line because retail calls it out of line, and it is throw() because
// retail's own body at 0x000C3DD0 is a straight run of dword copies with no EH
// frame and no call -- it provably cannot throw.  Saying so is what removes the
// unwind state retail does not have before this call (at body +0x28C), and with
// it the 8 bytes that shifted the whole tail.
class __declspec(novtable) PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const KindOfMaskType &mustBeClear,
		const KindOfMaskType &mustBeSet) throw();
	virtual ~PartitionFilterAcceptByKindOf() {}

	KindOfMaskType m_mustBeClear;
	KindOfMaskType m_mustBeSet;
};

// StateMachine: m_owner at +0x10 and the goal squad at +0x54 are both read
// straight out of the machine pointer.
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
	unsigned char m_unreconstructed_14[0x54 - 0x14];
	Gen_0018BC70 *m_goalSquad;
};

// State: the vptr at +0 and m_machine at +0x1c are witnessed by the landed
// onEnter/update bodies.  chooseVictim makes no virtual call on this, so the
// vptr is a plain slot here rather than a real vtable.
class State
{
public:
	void *m_vtable;
	Int m_ID;
	unsigned char m_unreconstructed_08[0x1c - 0x08];
	StateMachine *m_machine;
};

class AIAttackSquadState : public State
{
public:
	Object *chooseVictim(void);

	unsigned char m_unreconstructed_20[0x28 - 0x20];
	Bool byte_28;
};

// Zero Hour AIUpdate.h MoodMatrixParameters.  BFME tests 0x2100 for the sleep
// gate where the twin tests MM_Mood_Sleep alone, so 0x2000 is an added BFME
// mood bit; the name for it is not recoverable from the evidence here.
enum MoodMatrixParameters
{
	MM_Controller_AI = 0x00000002,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200
};

enum { BFME_MOOD_02000 = 0x00002000 };

Object *AIAttackSquadState::chooseVictim(void)
{
	Gen_0018BC70 *victimSquad = m_machine->m_goalSquad;
	if (victimSquad == 0)
		return 0;

	Object *owner = m_machine->m_owner;
	UnsignedInt moodVal = owner->m_ai->getMoodMatrixValue();

	// BFME fast path: if the owner's cached last-damage source is still a live
	// member of the goal squad, attack that one.  The clear sits in the `else`
	// arm, which is what retail's block layout shows: both skip branches and
	// only those reach the store at +0x9C, while a search that runs and misses
	// jumps past it.
	// The id goes through a named local.  This is the scratch-rotation lever
	// from docs/shape_levers.md ("Scratch registers rotate"): a value passed
	// straight from memory to a call argument takes one rotation step fewer
	// than a local copy of it, and every short-lived temp from here to the end
	// of the body lands one register along.  tools/rotation_sweep.py found
	// this toggle (EXACT, -50 bytes) and the local spelling was measured at
	// 0 differing bytes of 949, so it is written out rather than left as the
	// sweep's identity inline.
	const Int cachedID = owner->dword_3A4;
	Object *cached = TheBfmeGameLogic->findObjectByID(cachedID);
	if (cached != 0 && !(cached->m_privateStatus & 1))
	{
		BfmeVecAK *live = victimSquad->bfmeCompact(true);
		for (Object *const *it = live->m_bfmeStart; it != live->m_bfmeFinish; ++it)
		{
			if (cached == *it)
				return cached;
		}
	}
	else
	{
		owner->dword_3A4 = 0;
	}

	// Zero Hour mood gate, apart from the widened sleep mask.  The sleep test
	// is INVERTED and its `return 0` sits in the else arm; the passive test is
	// inverted too, so both inner null returns become plain early exits.  That
	// shape is what lets MSVC merge the three `return 0`s into the single block
	// retail has at +0xbf -- placed AFTER the passive arm, and reached by a
	// forward `jne` from the sleep test and by fall-through from the
	// `test ecx,ecx`.  Every other spelling tried puts the shared block after
	// the arm instead and costs 20-25 bytes.
	if (moodVal & MM_Controller_AI)
	{
		if (!(moodVal & (MM_Mood_Sleep | BFME_MOOD_02000)))
		{
			if (!(moodVal & MM_Mood_Passive))
			{
				// fall through to the scan
			}
			else
			{
				BodyModuleInterface *bmi = owner->m_bodyModule;
				if (bmi == 0)
					return 0;
				const DamageInfo *di = bmi->getLastDamageInfo();
				if (di == 0)
					return 0;
				return TheBfmeGameLogic->findObjectByID(di->m_sourceID);
			}
		}
		else
		{
			return 0;
		}
	}

	// BFME replaces the twin's difficulty switch with a nearest-in-squad scan.
	Weapon *weapon = owner->getCurrentWeapon(0);
	BfmeVecAK *live = victimSquad->bfmeCompact(true);
	// bestDist is declared before best: retail stores the FLT_MAX immediate
	// first (+0x106) and its slot (E-0xF8) is the lower of the two, so the
	// declaration order -- not just the initialiser -- is what reproduces both
	// the store order and the slot assignment.
	Real bestDist = FLT_MAX;
	Object *best = 0;
	Bool inAttackRange = false;

	for (Object *const *it = live->m_bfmeStart; it != live->m_bfmeFinish; ++it)
	{
		Object *cand = *it;

		if (cand->dword_208 != 0
			&& ((BfmeCheckerNW *)cand->dword_208)->bfmeBusyNW())
			continue;

		ThingTemplate *base = cand->m_thingTemplate;
		ThingTemplate *effective;
		if (base == 0)
			effective = 0;
		else if (base->m_next != 0)
			effective = (ThingTemplate *)base->m_next->getFinalOverride();
		else
			effective = base;
		if ((effective->m_kindOfWord1 & 0x200000) != 0)
			continue;

		if ((cand->m_status & 0x8000) != 0 && (cand->m_status & 0x20000) == 0)
			continue;

		// The 2-D squared distance, through named per-axis Reals.  Retail's
		// x87 code at +0x16E loads owner.x (+0x38) first and squares the y
		// product first; naming the two differences is what pins that order.
		// Written as one expression -- in either term order -- MSVC 7.1
		// canonicalises the commutative add and emits owner.y first
		// (measured: 61 diffs either way, +0x170..+0x17F unresolved).
		const Real ddx = owner->m_position.x - cand->m_position.x;
		const Real ddy = owner->m_position.y - cand->m_position.y;
		Real dist = ddx * ddx + ddy * ddy;

		if (weapon != 0 && weapon->isWithinAttackRange(owner, cand, 0))
		{
			inAttackRange = true;
			dist = dist * 0.25f;
		}

		if (cand->m_privateStatus & 1)
			continue;

		if (dist < bestDist)
		{
			bestDist = dist;
			best = cand;
		}
	}

	// BFME fallback: ask the partition manager, but only once the state has
	// latched byte_28, nothing in range has been found, and there is a weapon.
	// The polarity is retail's: +0x1F2 is `je` to the epilogue, so the query
	// runs when byte_28 is SET (an earlier draft read that branch the other
	// way round and was wrong).
	if (this->byte_28 && !inAttackRange && weapon != 0)
	{
		PartitionFilterRelationship relationship(owner, 1, false);
		Rva0017D2F0DwordTailFilter relationship2(owner, 2, 0);
		PartitionFilterRejectBuildings rejectBuildings(owner);
		// The empty mask is the FIRST argument and the built one the second:
		// retail pushes the temporary's address (+0x27B) before the
		// ?KINDOFMASK_NONE address (+0x280), and the 24-byte blocks land at
		// this+8 and this+0x20 in that order.  Index 129 is what the
		// `or eax,2` on word 4 fixes (129 = 4*32+1).
		PartitionFilterAcceptByKindOf acceptByKindOf(KINDOFMASK_NONE, MAKE_KINDOF_MASK(129));
		Rva0025ED50ObjectFilter objectFilter(owner);

		relationship.link(&relationship2);
		relationship.link(&objectFilter);
		relationship.link(&acceptByKindOf);
		relationship.link(&rejectBuildings);

		// The query fills this with object IDs, not Object*: the loop feeds
		// each entry straight to findObjectByID.  Its declared length is the
		// one number in this body that no byte pins down -- 16 is what makes
		// the frame close exactly (64 bytes from E-0x4C to E-0x0C, with the
		// AcceptByKindOf ending at E-0x4D), so it is the strongest value the
		// frame allows.
		UnsignedInt ids[16];
		// The receiver goes through a named local: written inline, MSVC
		// materialises TheAI and the +0x0C pathfinder pointer after the
		// array address, where retail loads both first (+0x2E8/+0x2EE).
		Pathfinder *pathfinder = TheAI->m_pathfinder;
		Int count = pathfinder->bfmeCheckAttackView(owner, ids);

		for (Int i = 0; i < count; i++)
		{
			Object *cand = TheBfmeGameLogic->findObjectByID(ids[i]);
			if (cand == 0)
				continue;
			if (!((BfmeThingEQ *)&relationship)->bfmeAskEQ(cand))
				continue;
			if (!weapon->isWithinAttackRange(owner, cand, 0))
				continue;

			// Each term carries its own 0.25f here: retail scales inside the
			// products (two fmul [0x01083B6C] before the faddp), not once on
			// the sum.  The two squared differences go through named Reals
			// because the full expression reassociates the commutative add and
			// then loads the y difference first, where retail loads x; naming
			// them pins the order and buys 4 bytes.
			const Real ddx = owner->m_position.x - cand->m_position.x;
			const Real ddy = owner->m_position.y - cand->m_position.y;
			Real dist = ddx * ddx * 0.25f + ddy * ddy * 0.25f;

			if (cand->m_privateStatus & 1)
				continue;

			if (dist < bestDist)
			{
				bestDist = dist;
				best = cand;
			}
		}
	}

	return best;
}

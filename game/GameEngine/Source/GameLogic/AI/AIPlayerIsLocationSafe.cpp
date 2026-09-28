// cl: /DNDEBUG /MD /EHsc
// ?isLocationSafe@AIPlayer@@QAE_NPBUCoord3D@@PBVThingTemplate@@@Z
// readable body of ?isLocationSafe@AIPlayer@@QAE_NPBUCoord3D@@PBVThingTemplate@@@Z:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::isLocationSafe, retail 0x00163030, 388 bytes, `ret 8` at +0x181.
// This is the EXACT body: 388 bytes with no non-relocation byte difference
// outside the relocation slots.
//
// Identity.  symbols.csv pins the named ILT 0x0003E504 here, and the matched
// caller ?isSupplySourceSafe@AIPlayer@@QAE_NH@Z calls it at 0x00166A10, so
// the class, the name and the two-argument __thiscall signature (which the
// `ret 8` fixes) are all witnessed.  The filter set is NOT Zero Hour's: BFME
// retail builds six filters on the stack, links them with five calls to
// PartitionFilter::link (0x009F2AE0) and hands the head to
// PartitionManager::getClosestObject (0x009F26A0).  The Zero Hour source at
// GeneralsMD/.../AI/AIPlayer.cpp:998 is the array-of-filters version with a
// seventh PartitionFilterRejectByObjectStatus; it is the readable ancestor,
// not this body.
//
// ============================================================================
// THE SHAPE LEVER: the six filters are UNNAMED TEMPORARIES built inline in the
// getClosestObject argument list
// ============================================================================
// This is what fifteen earlier verdicts missed, and it is the whole reason the
// body now matches.  With the six filters written as named locals (the shape
// every earlier bank used) VC7.1 emits `lea eax,[S+0x40] ; push eax` where
// retail emits `push esi`, and `lea ecx,[S+0x78]` where retail emits
// `mov ecx,eax`: 393 bytes, 249 non-relocation differences, and `this` in ESI
// instead of EDI.  The reason is measurable, not stylistic.
//
// For a NAMED local, VC7.1 knows the address is the frame constant S+0x40, so
// after the out-of-line constructor returns it folds the live value back to
// that constant (`lvjCopyProp`) and the register is never allocated.  For an
// UNNAMED TEMPORARY the value's definition is the constructor call itself, and
// VC7.1 keeps the return register: it emits `mov esi,eax` straight after the
// first call and `push eax` where retail pushes `esi`.  That single change
// cascades into retail's whole register plan:
//
//   * ESI holds &filterHarvesters across the second constructor call, so it is
//     a callee-saved register that must be saved at +0x58 (`push esi`, and
//     `pop esi` at +0x16A on the true path; the false path at +0x2E jumps over
//     the pop and both paths read the same saved fs:[0] word).
//   * `this` cannot be in ESI any more, so it moves to EDI (`push edi` in the
//     prologue, `mov edi,ecx`), and its single use is the m_player read at
//     +0x102.
//   * the second constructor's return stays in EAX until the first link call,
//     which is why the m_player read at +0x102 goes to EDX rather than to EAX.
//     With named locals the compiler is free to use EAX there and in fact does.
//
// Net: 393 -> 388 bytes and 249 -> 0 non-relocation differences, with all 101
// instructions matching.  The sibling idiom is already landed and documented
// at game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_allowedToStealthAt002ACD90.cpp
// ("Rva0025ED50RootFilter().link(&PartitionFilterAcceptByKindOf(...))") and at
// game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva002622D0Collect.cpp.
//
// ============================================================================
// the result spelling
// ============================================================================
// The comparison result is named before it is returned.  `return enemy == 0;`
// emits `neg eax ; sbb eax,eax ; inc eax` (5 bytes); naming it in a Bool local
// emits `neg eax ; sbb al,al ; inc al` (6 bytes), which is what retail has, and
// the extra byte is exactly retail's 388 against 387.  `const Bool r = ...;
// return r;`, `Bool r; r = ...; return r;`, `return (Bool)(enemy == 0);`,
// `return enemy == 0 ? true : false;` and the if/return pair all measure
// identical; the named local is the one kept.  The idiom is the same one the
// landed StringBase::startsWith uses for `return _memicmp(...) == 0;`.
//
// ============================================================================
// frame map -- machine-derived, not estimated
// ============================================================================
// Traced with an esp simulation over the real callee ret arities
// (0x00160BE0 ret 8, 0x009F2AE0 ret 4, 0x009F26A0 ret 0x10), which closes on
// both epilogue paths, and cross-checked against FuncInfo 0x00DF3ABC
// (`python3 tools/eh_info.py 0x00163030`: handler 0x00C0554C, six unwind
// states with cleanup receivers -0x7c -0x44 -0xa0 -0x8c -0x94 -0xbc).  Let
// S = esp just after `sub esp, 0xb0`; the six cleanup receivers put the frame
// base at ebp = S+0xbc, and the frame is exactly [S, S+0xb0).  Every object
// slot below is read off that trace and this build agrees with all of them:
//
//   S+0x00..S+0x17  the 24-byte KindOf mask temporary, reused by filterTeam
//   S+0x18          radius (fld tthing+0x70 ; fadd [AiData+0x84])
//   S+0x1C..S+0x27  Rva010956E4Filter, vtable 0x010956E4, two Bools
//   S+0x28..S+0x2F  Rva01083B80Filter, vtable 0x01083B80
//   S+0x30..S+0x3F  Rva0109685CFilter, vtable 0x0109685C
//   S+0x40..S+0x77  the 0x38-byte reject-by-KindOf filter
//   S+0x78..S+0xAF  the same class again
//
// The eight objects tile 0xB0 exactly, so retail performs exactly ONE stack
// slot reuse: the 0x14-byte team filter takes the mask temporary's slot.  The
// mask's last write is at +0xE4 and the team's first at +0x125, so the
// intervals really are disjoint, and the mask temporary has no EH cleanup of
// its own while all six filters do -- the -0xbc receiver (state 5, ILT
// 0x00160D10) is one of the same one-store vtable-reset stubs as the other
// five.  The `lea edx,[S+0x00]` handed to both constructor calls is the same
// slot, and the radius is stored at S+0x18 and reloaded from S+0x18 at
// +0x181, which is a third independent confirmation of the esp model.
//
// ============================================================================
// the constructor's body is deliberately visible in this TU
// ============================================================================
// All fifteen earlier banks declared the reject-by-KindOf constructor
// extern and got a 0xC4 frame against retail's 0xB0.  Defining it here,
// out of line, is what lets VC7.1 see that it copies both masks and retains
// neither, free the mask temporary's 0x18 bytes and reproduce the exact frame.
// It is the same callee-visibility lever docs/shape_levers.md records under
// "Filter construction: visible non-retaining constructors", where the same
// move at 0x002622D0 let VC7.1 reuse a six-word mask temporary for the
// relationship filter.  Nothing about a lifetime is faked: the body below is
// the complete 102-byte body at 0x00160BE0, and the landed row for it is
// ??0Rva00160BE0VptrZeroBlockObject@@QAE@ABUVptrZeroBlock24@@0@Z in
// game/GameEngine/Source/Common/VptrZeroPrefixBlockCtors.cpp.
//
// ============================================================================
// filter identities
// ============================================================================
// The four small filters store their vtable as a literal rather than through a
// vtable symbol.  That is deliberate: dir32_addresses.csv records
// ??_7PartitionFilterPlayer@@6B@ at 0x0109688C while retail stores 0x0109685C,
// and it has no entry at all for 0x010956E4, 0x01083B80 or 0x0109689C, so a
// vtable symbol here would be a name whose address the gate would derive from
// this very body and therefore could not check.  tools/vtable_lookup.py names
// none of those four, so their classes keep address-derived names; what IS
// proved is the layout each one must have, from its stores in this body plus
// the frame map above.
//
// 0x0109686C, the reject-by-KindOf vtable, is different: vtable_lookup ties it
// to PartitionFilterRejectByKindOf (its destructor ILT 0x00034F04 and its
// scalar deleting destructor 0x00161300 are named rows for that class), the
// constructor at 0x00160BE0 installs it, and the MATCHED
// PartitionFilterRejectByKindOf::allow reads its two masks at this+0x08 and
// this+0x20 -- the two offsets the constructor copies to.  Class and layout
// are both witnessed, so that one carries the real name; only the mask
// parameter TYPE is a view (a 24-byte block, see below).
//
// Link order, each call's `this` being the later filter and its argument the
// earlier one: S+0x78 <- S+0x40 <- S+0x1C <- S+0x30 <- S+0x28 <- S+0x00,
// read off the five link receivers at +0x152 +0x15c +0x166 +0x170 and the
// receivers' S-relative addresses.
//
// The affiliation 0xA is ALLOW_ALLIES|ALLOW_NEUTRAL: Zero Hour's PlayerList.h
// gives 0x02 and 0x08, and the EA source passes exactly that expression
// (AIPlayer.cpp:1032).  The third getClosestObject argument is 3, i.e.
// FROM_BOUNDINGSPHERE_3D (PartitionManager.h:155), pushed at +0x55.
//
// ============================================================================
// the mask type and the two KindOf bits
// ============================================================================
// The mask is a plain 24-byte block: the landed 0x00160BE0 body copies exactly
// 24 bytes to +0x08 and 24 to +0x20, and the constructor objects are 0x38
// bytes.  KindOfMaskType is BitFlags<KINDOF_COUNT>, which is not 24 bytes in
// the shim tree, so the block below is the honest view -- the same choice
// Rva002622D0Collect.cpp makes with its own typedef.
//
// The two bits are 1<<14 and 1<<16, both in dword 0, read straight off the
// `or eax,0x4000` at +0x9A and the `or eax,0x10000` at +0xD0.  The
// bfmekindof shim numbers KINDOF_DOZER 14 and KINDOF_HARVESTER 15, and its
// AIRCRAFT 12 is confirmed by the matched TunnelTracker::updateNemesis, so
// retail's enum has one more kind than the shim somewhere before these two
// and the NAMES are not proved.  The numbers are, and they are all this body
// uses.
//
// The mask spelling (memset the six dwords, then set one bit) is the one the
// matched AIPlayer::findSupplyCenter body uses (AIPlayerFindSupplyCenter.cpp,
// 886 B exact) and the only one that keeps retail's register-form
// `or eax, 0x4000`.  Six tracked field assignments fold the OR to a constant
// store and a real std::bitset<192> emits a zeroing loop; both were measured.
//
// The result shape is retail's: `if (tthing == 0) return false;` then an
// unconditional tail, which is the `xor al,al` at +0x2C with the `jmp` to the
// epilogue and the `neg eax / sbb al,al / inc al` normalisation.

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;

class ThingTemplate
{
public:
	Real getBoundingCircleRadius(void) const
	{
		return *(const Real *)((const char *)this + 0x70);
	}
};

class AiData
{
public:
	char m_unmodelled000[0x84];
	Real m_supplyCenterSafeRadius;						// +0x84
};

class AI
{
public:
	char m_unmodelled000[0x14];
	AiData *m_aiData;									// +0x14
};

extern AI *TheAI;

// The 24-byte block the reject-by-KindOf constructor takes twice by const
// reference: two 192-bit KindOf masks, six dwords.  Address-derived name, the
// same spelling game/GameEngine/Source/Common/VptrZeroPrefixBlockCtors.cpp
// uses for the standalone definition of the constructor that takes it.
struct VptrZeroBlock24
{
	enum BogusInitType { kInit = 0 };

	unsigned int bits[6];

	VptrZeroBlock24(void)
	{
		bits[0] = 0;
		bits[1] = 0;
		bits[2] = 0;
		bits[3] = 0;
		bits[4] = 0;
		bits[5] = 0;
	}

	VptrZeroBlock24(BogusInitType, Int bit)
	{
		memset(bits, 0, sizeof(bits));
		bits[bit >> 5] |= (1U << (bit & 31));
	}
};

extern const VptrZeroBlock24 KINDOFMASK_NONE;

// The immediates are 1<<14 and 1<<16 in dword 0 of the mask.  The shim's enum
// has one fewer kind than retail's (see the header), so these numbers -- not
// the names KINDOF_HARVESTER / KINDOF_DOZER -- are what the body proves.
enum BFME_KindOfFromRetailMasks
{
	KINDOF_FROM_RETAIL_MASK_14 = 14,
	KINDOF_FROM_RETAIL_MASK_16 = 16
};

#define MAKE_KINDOF_MASK(k) VptrZeroBlock24(VptrZeroBlock24::kInit, (k))

// PlayerList.h relationship flags: ALLOW_ALLIES 0x02, ALLOW_NEUTRAL 0x08.
enum AllowPlayerRelationship
{
	ALLOW_ALLIES = 0x02,
	ALLOW_NEUTRAL = 0x08
};

// PartitionManager.h:155, the immediate retail pushes at 0x00163055.
enum DistanceCalculationType
{
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionFilter
{
public:
	PartitionFilter(void) {}
	PartitionFilter *link(PartitionFilter *next);		///< 0x009F2AE0

	unsigned int m_vptr;								// +0x00
	PartitionFilter *m_next;							// +0x04
};

// vtable 0x0109686C.  tools/vtable_lookup.py ties that table to
// PartitionFilterRejectByKindOf (destructor ILT 0x00034F04, scalar deleting
// destructor 0x00161300), the constructor at 0x00160BE0 installs it, and the
// matched PartitionFilterRejectByKindOf::allow reads its two masks at +0x08 and
// +0x20 -- the two offsets copied to below.  Class and layout are witnessed.
// The constructor is defined HERE on purpose: seeing that it copies both masks
// and retains neither is what frees the mask temporary's 0x18 bytes and
// reproduces retail's exact 0xB0 frame (see the header).
class PartitionFilterRejectByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterRejectByKindOf(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second)
		: m_first(first), m_second(second)
	{
		m_next = 0;
		m_vptr = 0x0109686C;
	}

	~PartitionFilterRejectByKindOf(void)
	{
		m_vptr = 0x01083B5C;
	}

	VptrZeroBlock24 m_first;							// +0x08
	VptrZeroBlock24 m_second;							// +0x20
};

// vtable 0x010956E4; two Bools, stored true then false, which is Zero Hour's
// (allowNonBuildings, allowInsignificant) order.  Address-derived class name:
// tools/vtable_lookup.py names no class for that table.
class Rva010956E4Filter : public PartitionFilter
{
public:
	Rva010956E4Filter(Bool allowNonBuildings, Bool allowInsignificant)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x010956E4;
		m_allowNonBuildings = allowNonBuildings;
		m_allowInsignificant = allowInsignificant;
	}

	~Rva010956E4Filter(void)
	{
		m_vptr = 0x01083B5C;
	}

	Bool m_allowNonBuildings;							// +0x08
	Bool m_allowInsignificant;							// +0x09
};

// vtable 0x0109685C, m_player +0x08, m_match +0x0C.  Address-derived class
// name: retail's own constructor for this table, 0x00160BB0, is a 32-byte
// vtable-plus-zeroed-dword body taking one pointer, and it is a matched row of
// its own, so this body's (player, match) pair is a local view.
class Rva0109685CFilter : public PartitionFilter
{
public:
	Rva0109685CFilter(const Player *player, Bool match)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x0109685C;
		m_player = player;
		m_match = match;
	}

	~Rva0109685CFilter(void)
	{
		m_vptr = 0x01083B5C;
	}

	const Player *m_player;							// +0x08
	Bool m_match;										// +0x0C
};

// vtable 0x01083B80, the head only.  Address-derived class name: no ledger row
// names that table.
class Rva01083B80Filter : public PartitionFilter
{
public:
	Rva01083B80Filter(void) : PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x01083B80;
	}

	~Rva01083B80Filter(void)
	{
		m_vptr = 0x01083B5C;
	}
};

// vtable 0x0109689C, m_player +0x08, m_match +0x0C, m_affiliation +0x10.
// symbols.csv pins ??_7PartitionFilterPlayerAffiliation@@6B@ at this vtable.
class PartitionFilterPlayerAffiliation : public PartitionFilter
{
public:
	PartitionFilterPlayerAffiliation(const Player *player, UnsignedInt affiliation, Bool match)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x0109689C;
		m_player = player;
		m_match = match;
		m_affiliation = affiliation;
	}

	~PartitionFilterPlayerAffiliation(void)
	{
		m_vptr = 0x01083B5C;
	}

	const Player *m_player;							// +0x08
	Bool m_match;										// +0x0C
	UnsignedInt m_affiliation;							// +0x10
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

class AIPlayer
{
public:
	Bool isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing);

	char m_unmodelled000[0x0c];
	Player *m_player;									// +0x0C
};

Bool AIPlayer::isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing)
{
	if (tthing == 0)
		return false;

	// See if we have enemies.
	AiData *const aiData = TheAI->m_aiData;
	Real radius = tthing->getBoundingCircleRadius() +
		aiData->m_supplyCenterSafeRadius;

	// The six filters are UNNAMED TEMPORARIES, so they live to the end of the
	// full-expression and VC7.1 keeps each constructor's return value in a
	// register instead of folding the address back to the frame constant.
	// That is the whole shape; see the header for the measurement.
	Object *enemy = ThePartitionManager->getClosestObject(
		pos, radius, FROM_BOUNDINGSPHERE_3D,
		// only consider enemies, and not our own
		PartitionFilterPlayerAffiliation(m_player, ALLOW_ALLIES | ALLOW_NEUTRAL, false).link(
			// and only stuff that is not dead
			Rva01083B80Filter().link(
				// and only stuff that belongs to somebody else
				Rva0109685CFilter(m_player, false).link(
					// (optional) only stuff that is significant
					Rva010956E4Filter(true, false).link(
						PartitionFilterRejectByKindOf(
							MAKE_KINDOF_MASK(KINDOF_FROM_RETAIL_MASK_16),
							KINDOFMASK_NONE).link(
								&PartitionFilterRejectByKindOf(
									MAKE_KINDOF_MASK(KINDOF_FROM_RETAIL_MASK_14),
									KINDOFMASK_NONE)))))));

	const Bool noEnemyFound = (enemy == 0);
	return noEnemyFound;
}

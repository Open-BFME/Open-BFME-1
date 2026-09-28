// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?isLocationSafe@AIPlayer@@QAE_NPBUCoord3D@@PBVThingTemplate@@@Z:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::isLocationSafe, 0x00163030, 388 bytes.
//
// Identity: the matched caller ?isSupplySourceSafe@AIPlayer@@QAE_NH@Z
// (AIPlayer.cpp:1006) calls it and symbols.csv pins the named ILT at
// 0x0003E504 here.  Zero Hour's AIPlayer.cpp:1000 is the same function with an
// array-of-filters filter set; BFME retail instead builds six filters on the
// stack, links them with five calls to PartitionFilter::link (0x009F2AE0) and
// passes the head to ThePartitionManager->getClosestObject (0x009F26A0), so
// the link chain below is what retail's source actually said.
//
// Frame map, proved with an esp-accurate trace of the real callee ret arities
// (0x00160BE0 ret 8, 0x009F2AE0 ret 4, 0x009F26A0 ret 16).  Q is esp just
// after `sub esp, 0xb0`; the local frame is exactly [Q, Q+0xB0):
//
//   Q-0x0C        four bytes pushed at +0x58 with `push esi` and released by
//                 the matching `pop esi` at +0x16A.  The false path jumps over
//                 that pop and `add esp, 0xBC` still balances, which fixes the
//                 slot as the saved-esi spill for the harvesters pointer that
//                 `mov esi, eax` at +0x7D loads and `push esi` at +0x111
//                 consumes.  Retail therefore keeps `this` in edi, not esi.
//   Q-0x08, Q-0x04 saved edi, ebx
//   Q+0x00..Q+0x17 24-byte KindOf mask temporary, reused as filterTeam
//                  (vtable 0x0109689C at +0x00, m_next +0x04, m_player +0x08,
//                   m_match +0x0C, m_affiliation 0x0A at +0x10)
//   Q+0x18        radius (fld tthing+0x70 ; fadd [AiData+0x84])
//   Q+0x1C..Q+0x27 filterInsignificant, vtable 0x010956E4, two Bools
//   Q+0x28..Q+0x2F filterAlive, vtable 0x01083B80, no field past m_next
//   Q+0x30..Q+0x3F filterPlayer, vtable 0x0109685C
//   Q+0x40..Q+0x77 filterHarvesters, out-of-line ctor 0x00160BE0
//   Q+0x78..Q+0xAF filterDozer, the same ctor
//
// Cross-checks, all independent of the trace: the mask pointer handed to the
// 0x00160BE0 ctor is the same slot in both calls (lea edx,[Q+0x00] at
// 0x00163062 and again at 0x00163098); the radius is stored at Q+0x18 and
// reloaded from Q+0x18 at 0x00163151; 0x00163149 re-reads the *first* argument
// (pos) from X+4, not the second; and FuncInfo 0x00DF3ABC (tools/eh_info.py
// 0x00163030) gives exactly six cleanup receivers -0x7c, -0x44, -0xa0, -0x8c,
// -0x94 and -0xbc, i.e. construction order harvesters, dozer, insignificant,
// player, alive, team.  The -0xbc cleanup is one of the same one-store
// vtable-reset stubs (0x1083B5C) as the other five, so the object that reuses
// the mask slot IS filterTeam; the mask temporary itself has no cleanup at all,
// so its 0x18 bytes are free from the moment its constructor call returns.
//
// Filter identities.  The four small filters store their vtable as literals
// rather than through a vtable symbol.  That is deliberate: dir32_addresses.csv
// records ??_7PartitionFilterPlayer@@6B@ at 0x0109688C, retail stores
// 0x0109685C, and there is no entry at all for 0x010956E4 or 0x01083B80, so a
// vtable symbol here would be a name whose address the gate derives from this
// very body and therefore cannot check.  What is proved is the layout each
// class must have, from name_oracle's witnessed members and from the EA
// source's constructor argument lists:
//
//   0x0109686C  vtable_lookup ties this vtable to PartitionFilterRejectByKindOf
//               (symbols.csv note on ??1PartitionFilterRejectByKindOf@@MAE@XZ),
//               and the landed ctor is
//               ??0Rva00160BE0VptrZeroBlockObject@@QAE@ABUVptrZeroBlock24@@0@Z --
//               two 24-byte masks by const reference, which is exactly Zero
//               Hour's PartitionFilterRejectByKindOf(const KindOfMaskType &,
//               const KindOfMaskType &) with m_mustBeSet at +0x08 and
//               m_mustBeClear at +0x20, the two offsets the ctor copies to.
//   0x0109685C  witnessed at +0x0008 m_player, +0x000c m_match -- the same
//               layout as name_oracle's PartitionFilterPlayer, and the landed
//               Rva001DCBB0Filter ctor (Rva001DCBB0FilterCtor.cpp) builds that
//               layout from an Object* by storing getControllingPlayer() at +8.
//   0x010956E4  PartitionFilterInsignificantBuildings per the EA source
//               (AIPlayer.cpp:1043); its two Bools are true then false, the
//               Zero Hour (allowNonBuildings, allowInsignificant) order.
//   0x01083B80  PartitionFilterAlive per the EA source (AIPlayer.cpp:1035);
//               retail stores no field past m_next.
//   0x0109689C  PartitionFilterPlayerAffiliation; this one IS the
//               dir32_addresses.csv vtable, witnessed at +0x0008 m_player,
//               +0x000c m_match, +0x0010 m_affiliation.
//
// Link order, each call's `this` being the later filter and its argument the
// earlier one:  dozer <- harvesters <- insignificant <- player <- alive
// <- team.  Read straight off the five `lea ecx,[...]` receivers at +0x122,
// +0x12C, +0x136 and +0x140 and the first ctor's return in eax.
//
// The mask spelling (memset the six dwords, then set one bit) is the one the
// matched AIPlayer::findSupplyCenter body uses (AIPlayerFindSupplyCenter.cpp,
// 886 B exact), and it is the only one that keeps retail's register-form
// `or eax, 0x4000`; a std::bitset<192> member instead emits a zeroing loop
// (measured 365 B) and a tracked-field zeroing folds the OR into a constant
// store.
//
// The affiliation 0xA is ALLOW_ALLIES|ALLOW_NEUTRAL: Zero Hour's PlayerList.h
// gives 0x02 and 0x08, and the EA source passes exactly that expression
// (AIPlayer.cpp:1032).  The third getClosestObject argument is 3, i.e.
// FROM_BOUNDINGSPHERE_3D (PartitionManager.h:155), not the 2D value the EA
// source's array-of-filters shape used.
//
// The result shape, measured both ways.  Retail normalises with
// `neg eax / sbb al,al / inc al` and sinks the false result into the null test
// at the top of the body (+0x2C `xor al,al`, then a `jmp` to +0x16B that skips
// the `pop esi` only the true path pushed).  Two spellings were compiled:
//
//   A  if (tthing != 0) { ... return enemy == 0; } return false;   <- THIS ONE
//      391 B, 269 non-reloc diffs, finish_measure quality 0.2912,
//      probe shape 0.871.
//   B  if (tthing == 0) return false; ... return enemy == 0;
//      390 B, 309 non-reloc diffs, finish_measure quality 0.1933,
//      probe shape 0.901.
//
// B is the shape retail actually has -- it is the only one of the two that
// emits `sbb al,al` and puts the `xor al,al` at +0x2C -- but A measures better
// because B's byte-normalising tail shifts the whole epilogue and costs 40
// more differing bytes.  A is banked because the ranker scores on diffs; B is
// recorded here so the next attempt can start from it once the frame below is
// fixed, at which point its shape advantage should start to pay.
//
// Open, and measured not to be reachable from the source shape: this build
// keeps `this` in esi, so it never needs the mid-body saved-esi spill, and it
// gives filterTeam a fresh slot at Q+0x40 instead of reusing the dead mask
// temporary's 0x18 bytes at Q+0x00, so the frame is 0xC4 rather than 0xB0 and
// every frame-relative displacement downstream is displaced by 0x14.  Every one
// of the 720 orderings of the six declarations, five link spellings, both
// enclosing-scope shapes, all four return spellings, both radius-local
// positions, unused scalar locals of three types, a static mask factory and a
// std::bitset<192> mask were compiled and measured; the frame stays 0xC4 (0xC0
// with the radius local removed).
//
// A variant that scores higher on paper was rejected on purpose.  Letting the
// four small filters store their vtable through a vtable symbol instead of a
// literal drops to 253 diffs / quality 0.3325, but four of those sixteen
// "matches" are DIR32 slots the gate masks, and the address for each symbol
// would be derived from this body, so the score would be measuring a value the
// check cannot see and the class names are not vtable-proven (see above).

#include <string.h>

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

// The 24-byte block the landed 0x00160BE0 ctor takes twice by const
// reference.  Both arguments are 192-bit KindOf masks, six dwords.
//
// The kInit/idx constructor is upstream BitFlags(BogusInitType, Int idx1)
// (inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/
// Common/BitFlags.h), whose body is m_bits.set(idx) on a std::bitset<192>.
// Modelling it on the parameter type itself keeps a mask a plain temporary of
// exactly the parameter type, so it binds to the by-reference argument with
// full-expression lifetime.
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

// 1 << 14 and 1 << 16, read straight off the `or eax` immediates at 0x0016306A
// and 0x001630A0.  They are NOT named here: the shim KindOf.h numbers
// KINDOF_FROM_RETAIL_OR_10000 14 and KINDOF_FROM_RETAIL_OR_4000 15, so BFME's real enum carries one more
// kind before HARVESTER than the shim does, and the immediates -- not the
// header -- are what pins these two.
enum BFME_KindOfFromRetailMasks
{
	KINDOF_FROM_RETAIL_OR_4000 = 14,
	KINDOF_FROM_RETAIL_OR_10000 = 16
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
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

// The already-matched shared ctor at 0x00160BE0 (VptrZeroPrefixBlockCtors.cpp)
// is PartitionFilterRejectByKindOf's; declared under its landed name so the
// call resolves to the existing definition, and rebased onto PartitionFilter
// here (identical vptr@0/next@4 head) so the result can call ::link().
class Rva00160BE0VptrZeroBlockObject : public PartitionFilter
{
public:
	__declspec(nothrow) Rva00160BE0VptrZeroBlockObject(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second);
	~Rva00160BE0VptrZeroBlockObject(void)
	{
		m_vptr = 0x01083B5C;
	}

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

class PartitionFilterInsignificantBuildings : public PartitionFilter
{
public:
	PartitionFilterInsignificantBuildings(Bool allowNonBuildings, Bool allowInsignificant)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x010956E4;
		m_allowNonBuildings = allowNonBuildings;
		m_allowInsignificant = allowInsignificant;
	}

	~PartitionFilterInsignificantBuildings(void)
	{
		m_vptr = 0x01083B5C;
	}

	Bool m_allowNonBuildings;
	Bool m_allowInsignificant;
};

// vtable 0x0109685C, m_player +0x08, m_match +0x0C.
class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x0109685C;
		m_player = player;
		m_match = match;
	}

	~PartitionFilterPlayer(void)
	{
		m_vptr = 0x01083B5C;
	}

	const Player *m_player;
	Bool m_match;
};

class PartitionFilterAlive : public PartitionFilter
{
public:
	PartitionFilterAlive(void) : PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x01083B80;
	}

	~PartitionFilterAlive(void)
	{
		m_vptr = 0x01083B5C;
	}
};

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

	const Player *m_player;
	Bool m_match;
	UnsignedInt m_affiliation;
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

	Real radius = tthing->getBoundingCircleRadius() +
		TheAI->m_aiData->m_supplyCenterSafeRadius;

	Rva00160BE0VptrZeroBlockObject filterHarvesters(
		MAKE_KINDOF_MASK(KINDOF_FROM_RETAIL_OR_4000), KINDOFMASK_NONE);

	Rva00160BE0VptrZeroBlockObject filterDozer(
		MAKE_KINDOF_MASK(KINDOF_FROM_RETAIL_OR_10000), KINDOFMASK_NONE);

	PartitionFilterInsignificantBuildings filterInsignificant(true, false);
	PartitionFilterPlayer filterPlayer(m_player, false);
	PartitionFilterAlive filterAlive;
	PartitionFilterPlayerAffiliation filterTeam(
		m_player, ALLOW_ALLIES | ALLOW_NEUTRAL, false);

	PartitionFilter *filters = filterTeam.link(
		filterAlive.link(
			filterPlayer.link(
				filterInsignificant.link(
					filterDozer.link(&filterHarvesters)))));

	Object *enemy = ThePartitionManager->getClosestObject(
		pos, radius, FROM_BOUNDINGSPHERE_3D, filters);
	return enemy == 0;
}

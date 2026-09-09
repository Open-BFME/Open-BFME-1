// ?isLocationSafe@AIPlayer@@QAE_NPBUCoord3D@@PBVThingTemplate@@@Z
// partial score=0.55 date=2026-09-09
// Open-BFME5 conversions.
//
// AIPlayer::isLocationSafe, retail RVA 0x00163030, 388 bytes, SEH-framed.
//
// Retail is NOT the ZH array-of-filters shape (the body still present in
// AIPlayer.cpp compiles to 421 bytes, no SEH frame, because it uses the real
// GameLogic/PartitionManager.h filter classes and the array+NULL-terminator
// getClosestObject overload).  Retail instead builds six PartitionFilter
// objects on the stack and links them into a singly linked list with five
// calls to the already-matched PartitionFilter::link (0x009F2AE0), then
// passes the list head to the already-matched
// ThePartitionManager->getClosestObject (0x009F26A0, HHHH signature, real
// pin ?getClosestObject@PartitionManager@@QAEPAVObject@@PBUCoord3D@@MHPAVPartitionFilter@@@Z).
//
// The unwind map (FuncInfo 0x011f3abc) has six states -- six destructible
// filters, all resetting to the base vtable 0x01083B5C on unwind (dtors
// Gen_00160c60/00149f50/00149f10/000c3e80/00160d10, all a plain
// "mov [ecx], 0x1083b5c; ret").  Construction order (state 0 -> 5):
//
//   0: filterHarvesters  KindOf ctor 0x00160BE0 (already matched as
//      Rva00160BE0VptrZeroBlockObject), mask bit 46 (or eax,0x4000)
//   1: filterDozer        same ctor, mask bit 48 (or eax,0x10000)
//   2: filterInsignificant  vtable 0x010956E4, two Bool fields (true,false)
//      -- matches PartitionFilterInsignificantBuildings(true,false) exactly.
//   3: (unidentified)      vtable 0x0109685C, a pointer (AIPlayer+0xc,
//      i.e. m_player) plus one Bool(false) field.  Real ZH
//      PartitionFilterRejectByObjectStatus takes two masks, not a player
//      pointer, so this is a BFME-local filter; named by address pending a
//      real identity.
//   4: filterAlive         vtable 0x01083B80, no extra fields -- matches
//      PartitionFilterAlive() (no ctor args) exactly.
//   5: filterTeam          vtable 0x0109689C, m_player (+0x14), Bool match
//      = false (+0x18), UnsignedInt affiliation = 0xA (+0x1c) --
//      0xA == ALLOW_ALLIES|ALLOW_NEUTRAL, matches
//      PartitionFilterPlayerAffiliation(m_player, ALLOW_ALLIES|ALLOW_NEUTRAL,
//      false) exactly.
//
// Link nesting (matches the five d_009f2ae0 calls in order):
//   filterTeam.link(filterAlive.link(filterUnknownV685C.link(
//       filterInsignificant.link(filterDozer.link(&filterHarvesters)))))
//
// The null check is on the SECOND parameter (tthing), not pos -- confirmed
// by stack-offset arithmetic against the caller frame.  Radius reads
// tthing's embedded GeometryInfo bounding-circle radius (this+0x70, see
// Code/GameEngine/Source/Common/System/Geometry.cpp's this+0x18 note for the
// embedded GeometryInfo) before TheAI->getAiData()->m_supplyCenterSafeRadius
// (TheAI+0x14 -> AiData, +0x84), matching retail's fld/fadd read order.

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
	char m_bfmePad[0x84];
	Real m_supplyCenterSafeRadius;
};

class AI
{
public:
	char m_bfmePad[0x14];
	AiData *m_aiData;
};

extern AI *TheAI;

class PartitionFilter
{
public:
	PartitionFilter(void) {}
	PartitionFilter *link(PartitionFilter *next);

	unsigned int m_vptr;
	PartitionFilter *m_next;
};

struct VptrZeroBlock24
{
	unsigned int m_dword_00;
	unsigned int m_dword_04;
	unsigned int m_dword_08;
	unsigned int m_dword_0C;
	unsigned int m_dword_10;
	unsigned int m_dword_14;
};

// Already-matched shared ctor at 0x00160BE0 (VptrZeroPrefixBlockCtors.cpp);
// declare-only so the call resolves to the existing definition.  Rebased
// onto PartitionFilter here (identical vptr@0/next@4 head) so the result
// can call ::link() without a cast.
class Rva00160BE0VptrZeroBlockObject : public PartitionFilter
{
public:
	Rva00160BE0VptrZeroBlockObject(const VptrZeroBlock24 &first, const VptrZeroBlock24 &second);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

// Pinned as ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B (BFME 192-bit
// KindOfMask, 24 bytes -- matches VptrZeroBlock24's size).
template <unsigned int NUMBITS> class BitFlags;
extern const BitFlags<192> KINDOFMASK_NONE;

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

// Unidentified BFME-local filter, vtable 0x0109685C: a player pointer plus
// one Bool.  Not ZH's PartitionFilterRejectByObjectStatus (that takes two
// masks, no player).  Named by address pending a real identity.
class BfmeFilterV0109685C : public PartitionFilter
{
public:
	BfmeFilterV0109685C(const Player *player, Bool flag)
		: PartitionFilter()
	{
		m_next = 0;
		m_vptr = 0x0109685C;
		m_player = player;
		m_flag = flag;
	}

	~BfmeFilterV0109685C(void)
	{
		m_vptr = 0x01083B5C;
	}

	const Player *m_player;
	Bool m_flag;
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

	char m_bfmeBeforePlayer[0xc];
	Player *m_player;
};

Bool AIPlayer::isLocationSafe(const Coord3D *pos, const ThingTemplate *tthing)
{
	if (!tthing)
		return false;

	Real radius = tthing->getBoundingCircleRadius() + TheAI->m_aiData->m_supplyCenterSafeRadius;

	VptrZeroBlock24 harvesterMask;
	harvesterMask.m_dword_00 = 0;
	harvesterMask.m_dword_08 = 0;
	harvesterMask.m_dword_0C = 0;
	harvesterMask.m_dword_10 = 0;
	harvesterMask.m_dword_14 = 0;
	unsigned int harvesterBit = 0;
	harvesterBit |= 0x4000;
	harvesterMask.m_dword_04 = harvesterBit;

	Rva00160BE0VptrZeroBlockObject filterHarvesters(
		harvesterMask, reinterpret_cast<const VptrZeroBlock24 &>(KINDOFMASK_NONE));

	VptrZeroBlock24 dozerMask;
	dozerMask.m_dword_00 = 0;
	dozerMask.m_dword_08 = 0;
	dozerMask.m_dword_0C = 0;
	dozerMask.m_dword_10 = 0;
	dozerMask.m_dword_14 = 0;
	unsigned int dozerBit = 0;
	dozerBit |= 0x10000;
	dozerMask.m_dword_04 = dozerBit;

	Rva00160BE0VptrZeroBlockObject filterDozer(
		dozerMask, reinterpret_cast<const VptrZeroBlock24 &>(KINDOFMASK_NONE));

	PartitionFilterInsignificantBuildings filterInsignificant(true, false);
	BfmeFilterV0109685C filterUnknownV685C(m_player, false);
	PartitionFilterAlive filterAlive;
	PartitionFilterPlayerAffiliation filterTeam(m_player, 0xA, false);

	PartitionFilter *filters = filterTeam.link(
		filterAlive.link(
			filterUnknownV685C.link(
				filterInsignificant.link(
					filterDozer.link(&filterHarvesters)))));

	Object *enemy = ThePartitionManager->getClosestObject(pos, radius, 3, filters);
	if (enemy)
		return false;
	return true;
}

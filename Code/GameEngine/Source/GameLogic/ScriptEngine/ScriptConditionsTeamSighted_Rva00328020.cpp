// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x00328020, 738 bytes. ScriptConditions::evaluate (0x0032D720,
// ScriptConditions vtable slot 9) dispatches condition 133 here through ILT
// 0x0001CA0D with (param0, param1, param2) and returns its Bool.
//
// The body looks param0's team up by name, maps param1's relationship to a
// PartitionFilterRelationship allow mask, walks param2's player mask and, for
// every team member with a positive vision range, asks ThePartitionManager for
// the closest object of that player inside that range through six filters.
// The condition's original name is not proven, so the method keeps the address.
//
// The filters are temporaries of one full-expression, as in the landed
// Rva00265150 and Rva0025ED50 callers: MSVC 7.1 builds them innermost first,
// links them, and destroys them before the result is tested, which is the
// order retail's EH states 0..5 record. The Rva001DCBB0Filter link reuses its
// out-of-line constructor's return value, which only a temporary does.
// The null member guard is ZH's own team-walk idiom (pObj/pCur checks
// throughout ScriptConditions.cpp); the compiler folds the test, but it moves
// the team pointer into ESI and its reload onto the outer back edge.

#include <bitset>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

class Object;
class Player;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	Int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	Real m_real;						// this+0x0C
	AsciiString m_string;					// this+0x10
};

// The BFME Object DLINK skeleton from reference/shims/objectdlink: vptr at +0,
// the DLINK base at +4, the vbptr-carrying base at +0x68. The pad carries the
// position at +0x38, where every landed partition caller reads it.
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;					// Object+0x38
	unsigned char m_afterPosition[0x64 - 0x40];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];

	const Coord3D *getPosition(void) const { return &m_position; }
	Real getVisionRange(void) const;
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

// BFME filters: virtual destructor, allow, getPlayerMask, then next at +4.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags(BogusInitType, Int idx1, Int idx2)
	{
		m_bits._Unchecked_set((size_t)idx1);
		m_bits._Unchecked_set((size_t)idx2);
	}
};

// BFME's KindOfMaskType is 192 bits: KINDOFMASK_NONE is pinned as
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B at VA 0x012ED8B8, six zero dwords.
typedef BitFlags<192> KindOfMaskType;

// vtable 0x01083B70. Its out-of-line ctor 0x000C3DD0 (ILT 0x000382FD, pinned
// ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z) copies the
// two masks to +0x08 and +0x20; LevelGrantSpecialPower::actionAt00260180
// calls it under this name. Inlined here.
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva001DCBB0Filter : public PartitionFilter
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	virtual ~Rva001DCBB0Filter() {}
	virtual Bool allow(Object *);

	Player *m_player;
	unsigned char m_match;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ENEMIES = 1,
		ALLOW_NEUTRAL = 2,
		ALLOW_ALLIES = 4
	};

	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}
	virtual ~PartitionFilterPlayer() {}
	virtual Bool allow(Object *);

	const Player *m_player;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		Int distanceCalculation, PartitionFilter *filters);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;	// slot 17, vtable+0x44

	/// address-derived name -- forwards to TheScriptEngine's virtual at +0x4C
	UnsignedShort unidentified_0034DB40(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern const KindOfMaskType KINDOFMASK_NONE;

class ScriptConditions
{
protected:
	Bool evaluateRva00328020(Parameter *pTeamParm, Parameter *pAllianceParm, Parameter *pPlayerParm);
};

// ?evaluateRva00328020@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateRva00328020(Parameter *pTeamParm,
	Parameter *pAllianceParm, Parameter *pPlayerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	Int relationDescriber;
	switch (pAllianceParm->getInt()) {
		case 0:
			relationDescriber = PartitionFilterRelationship::ALLOW_ENEMIES;
			break;
		case 1:
			relationDescriber = PartitionFilterRelationship::ALLOW_NEUTRAL;
			break;
		case 2:
			relationDescriber = PartitionFilterRelationship::ALLOW_ALLIES;
			break;
		default:
			relationDescriber = -1;
			break;
	}

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	if (!mask)
		return false;

	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj)
				continue;
			if (obj->getVisionRange() > 0.0f)
			{
				// KindOf bits 88 and 133 are not named here.
				Bool found = ThePartitionManager->getClosestObject(obj->getPosition(),
					obj->getVisionRange(), 0,
					PartitionFilterPlayer(player, true).link(
					PartitionFilterRelationship(obj, relationDescriber, false).link(
					Rva0025ED50RootFilter().link(
					Rva001DCBB0Filter(obj, 0).link(
					Rva0025ED50ObjectFilter(obj).link(
					&PartitionFilterAcceptByKindOf(KINDOFMASK_NONE,
						KindOfMaskType(KindOfMaskType::kInit, 88, 133)))))))) != 0;
				if (found)
					return true;
			}
		}
	}

	return false;
}

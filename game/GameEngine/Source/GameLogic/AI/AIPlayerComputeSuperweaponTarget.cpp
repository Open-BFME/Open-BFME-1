// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?computeSuperweaponTarget@AIPlayer@@UAE_NPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z: game/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// Retail 0x00166A80 (898 bytes, ret 0x10): AIPlayer::computeSuperweaponTarget.
// Identity: AIPlayer vtable slot 4, reached through ILT 0x0003F4F9 from the
// matched AISkirmishPlayer::computeSuperweaponTarget fallback. The body is the
// Generals original (inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/
// GameEngine/Source/GameLogic/AI/AIPlayer.cpp) plus BFME's findPositionAround
// nudge for one special power type. The override returns Bool, so the base
// does too, but retail never loads al: like the Generals void body it falls
// off the end.
//
// Same-TU visibility: retail compiles this body in AIPlayer.cpp beside
// getPlayerStructureBounds (0x00163C70) and getPlayerSuperweaponValue
// (0x00164130). With both bodies visible and out of line, VC7.1 can see that
// neither keeps the bounds or position address, so it keeps bounds.hi.x in
// st(0), caches width/height, and hoists pos.x/pos.z out of the inner grid
// loop exactly as retail does. getPlayerSuperweaponValue is the matched
// source of AIPlayerGetPlayerSuperweaponValue.cpp; getPlayerStructureBounds
// is the Generals body on the same BFME team/object layouts (0x00163C70 is
// still a dump; this copy is not claimed).

#include <math.h>

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	Coord3D() {}
};

class Player;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Int calcCostToBuild(const Player *player, Int playerIndex = -1) const;

	unsigned char m_pad[0xc0];
	unsigned int m_kindof;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	const T *operator*() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}
	operator const T *() const
	{
		return operator*();
	}

private:
	const T *m_overridable;
};

class Object;

class BfmeObjectVirtualTail
{
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
	OVERRIDE<ThingTemplate> m_template;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template;
	}

	Bool isSignificantlyAboveTerrain() const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}

	unsigned char m_tail[0x40];
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS * (OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
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

	OBJCLASS *cur() const
	{
		return m_cur;
	}

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}

	void *m_vptr;
	unsigned char m_pad04[8];
	Object *m_head;
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head), m_unused(0) {}
	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
	Int m_unused;
};

class TeamPrototype
{
public:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}

	unsigned char m_pad[0x274];
	Team *m_teamInstanceList;
};



class BfmeTeamListNode
{
public:
	BfmeTeamListNode *m_next;
	BfmeTeamListNode *m_prev;
	TeamPrototype *m_proto;
};

class Player
{
public:
	class PlayerTeamList
	{
	public:
		class const_iterator
		{
		public:
			const_iterator() {}
			const_iterator(BfmeTeamListNode *node) : m_node(node) {}
			TeamPrototype *operator*() const { return m_node->m_proto; }
			Bool operator!=(const const_iterator &that) const { return m_node != that.m_node; }
			const_iterator &operator++() { m_node = m_node->m_next; return *this; }

		private:
			BfmeTeamListNode *m_node;
		};

		const_iterator begin() const
		{
			return const_iterator(m_head->m_next);
		}

		const_iterator end() const
		{
			return const_iterator(m_head);
		}

	private:
		BfmeTeamListNode *m_head;
	};

	const PlayerTeamList *getPlayerTeams() const
	{
		return (const PlayerTeamList *)((const char *)this + 0x288);
	}
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;


extern "C" __declspec(dllimport) double __cdecl ceil(double);

__forceinline Real fast_float_ceil(Real f)
{
	return (Real)ceil((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

struct Coord2D
{
	Real x, y;
};

struct Region2D
{
	Coord2D lo, hi;
	Real width(void) const { return hi.x - lo.x; }
	Real height(void) const { return hi.y - lo.y; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
struct FindPositionOptions
{
	FindPositionOptions(void)
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}

	Int flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

Bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType(void) const
	{
		return ((const SpecialPowerTemplate *)getFinalSpecialPower())->m_type;
	}

	// One-level override walk: the inlined step, then the out-of-line
	// friend_getFinalOverride (ILT 0x00048C61) retail calls.
	const Overridable *getFinalSpecialPower(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	unsigned char m_pad08[0x14 - 0x08];
	Int m_type;
};

// Special power type ordinal retail compares against (enumerator name unknown).
enum { BFME_SPECIAL_POWER_TYPE_4E = 0x4e };

class TerrainLogic
{
public:
	virtual void _tl_00() = 0;
	virtual void _tl_01() = 0;
	virtual void _tl_02() = 0;
	virtual void _tl_03() = 0;
	virtual void _tl_04() = 0;
	virtual void _tl_05() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) = 0;
};

extern TerrainLogic *TheTerrainLogic;

class AIPlayer
{
public:
	virtual Bool computeSuperweaponTarget(const SpecialPowerTemplate *power,
		Coord3D *retPos, Int playerNdx, Real weaponRadius);

	static void getPlayerStructureBounds(Region2D *bounds, Int playerNdx);

protected:
	static Int getPlayerSuperweaponValue(Coord3D *center, Int playerNdx, Real radius);
};


__declspec(noinline) void AIPlayer::getPlayerStructureBounds(Region2D *bounds, Int playerNdx)
{
	Player::PlayerTeamList::const_iterator it;
	Bool firstObject = true;
	Bool firstStructure = true;
	bounds->hi.x = bounds->lo.x = bounds->hi.y = bounds->lo.y = 0;
	Region2D objBounds;
	objBounds.hi.x = objBounds.lo.x = objBounds.hi.y = objBounds.lo.y = 0;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerNdx);
	if (pPlayer == 0)
		return;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it)
	{
		TeamPrototype *proto = *it;
		for (BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList(); !members.done(); members.advance())
			{
				Object *pObj = members.cur();
				if (!pObj)
					continue;
				if ((pObj->getTemplate()->m_kindof & 0x80) != 0)	// KINDOF_STRUCTURE
				{
					Coord3D pos = *pObj->getPosition();
					if (firstObject) {
						objBounds.lo.x = objBounds.hi.x = pos.x;
						objBounds.lo.y = objBounds.hi.y = pos.y;
						firstObject = false;
					} else {
						if (objBounds.lo.x > pos.x) objBounds.lo.x = pos.x;
						if (objBounds.lo.y > pos.y) objBounds.lo.y = pos.y;
						if (objBounds.hi.x < pos.x) objBounds.hi.x = pos.x;
						if (objBounds.hi.y < pos.y) objBounds.hi.y = pos.y;
					}
					if (firstStructure) {
						bounds->lo.x = bounds->hi.x = pos.x;
						bounds->lo.y = bounds->hi.y = pos.y;
						firstStructure = false;
					} else {
						if (bounds->lo.x > pos.x) bounds->lo.x = pos.x;
						if (bounds->lo.y > pos.y) bounds->lo.y = pos.y;
						if (bounds->hi.x < pos.x) bounds->hi.x = pos.x;
						if (bounds->hi.y < pos.y) bounds->hi.y = pos.y;
					}
				}
			}
		}
	}
	if (!firstStructure) {
		*bounds = objBounds;
	}
}

__declspec(noinline) Int AIPlayer::getPlayerSuperweaponValue(Coord3D *searchCenter, Int playerIndex,
	Real searchRadius)
{
	if (searchRadius < 4 * 10.0f)
		searchRadius = 4 * 10.0f;
	Player::PlayerTeamList::const_iterator it;
	Real cash = 0;
	Real radSqr = searchRadius * searchRadius;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerIndex);
	if (pPlayer == 0)
		return 0;
	for (it = pPlayer->getPlayerTeams()->begin();
		it != pPlayer->getPlayerTeams()->end();
		++it)
	{
		TeamPrototype *proto = *it;
		for (BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList();
			!iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList();
				!members.done(); members.advance())
			{
				Object *pObj = members.cur();
				if (!pObj)
					continue;
				if ((pObj->getTemplate()->m_kindof & 0x1000) != 0)
				{
					if (pObj->isSignificantlyAboveTerrain())
						continue;
				}
				Coord3D pos = *(pObj->getPosition());
				Real dx = searchCenter->x - pos.x;
				Real dy = searchCenter->y - pos.y;
				if (dx * dx + dy * dy < radSqr)
				{
					Real dist = sqrt(dx * dx + dy * dy);
					Real factor = 1.0f - (dist / (2 * searchRadius));
					Real cost = pObj->getTemplate()->calcCostToBuild(pPlayer);
					if ((pObj->getTemplate()->m_kindof & 0x20000) != 0)
						cost = cost / 10;
					if (cost > 3000)
						cost = cost / 10;
					cash += factor * cost;
				}
			}
		}
	}
	return cash;
}

#pragma warning(disable : 4715)

Bool AIPlayer::computeSuperweaponTarget(const SpecialPowerTemplate *power,
	Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	Region2D bounds;
	getPlayerStructureBounds(&bounds, playerNdx);

	if (weaponRadius < 1.0f) {
		weaponRadius = 1.0f; // sanity to avoid divide by 0.
	}

	Int xCount, yCount;
	bounds.lo.x += weaponRadius;
	bounds.hi.x -= weaponRadius;
	if (bounds.hi.x < bounds.lo.x) {
		bounds.hi.x = bounds.lo.x = (bounds.hi.x + bounds.lo.x) / 2.0f;
	}
	if (bounds.hi.y < bounds.lo.y) {
		bounds.hi.y = bounds.lo.y = (bounds.hi.y + bounds.lo.y) / 2.0f;
	}

	xCount = REAL_TO_INT_CEIL(bounds.width() / weaponRadius) + 1;
	yCount = REAL_TO_INT_CEIL(bounds.height() / weaponRadius) + 1;

	if (xCount > 10) xCount = 10;
	if (yCount > 10) yCount = 10;

	Int cash = -1;
	Coord3D pos;
	Coord3D bestPos;
	Int i, j;

	for (i = 0; i < xCount; i++) {
		for (j = 0; j < yCount; j++) {
			pos.x = bounds.lo.x + (bounds.width() * i) / xCount;
			pos.y = bounds.lo.y + (bounds.height() * j) / yCount;
			pos.z = 0;
			Int curCash = getPlayerSuperweaponValue(&pos, playerNdx, 2 * weaponRadius);
			if (curCash > cash) {
				cash = curCash;
				bestPos = pos;
			}
		}
	}

	Coord3D veryBestPos;
	xCount = 11;
	yCount = 11;
	cash = -1;
	Int count = 0;
	for (i = 0; i < xCount; i++) {
		for (j = 0; j < yCount; j++) {
			pos.x = bestPos.x + (i - 5) * (weaponRadius / 10);
			pos.y = bestPos.y + (j - 5) * (weaponRadius / 10);
			pos.z = 0;
			Int curCash = getPlayerSuperweaponValue(&pos, playerNdx, weaponRadius);
			if (curCash > cash) {
				cash = curCash;
				veryBestPos = pos;
				count = 1;
			} else if (curCash == cash) {
				veryBestPos.x += pos.x;
				veryBestPos.y += pos.y;
				count++;
			}
		}
	}
	if (count > 1) {
		veryBestPos.x /= count;
		veryBestPos.y /= count;
	}

	if (power->getSpecialPowerType() == BFME_SPECIAL_POWER_TYPE_4E) {
		FindPositionOptions fpOptions;
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 300.0f;
		findPositionAround(&veryBestPos, &fpOptions, &veryBestPos);
	}

	veryBestPos.z = TheTerrainLogic->getGroundHeight(veryBestPos.x, veryBestPos.y);
	*retPos = veryBestPos;
}

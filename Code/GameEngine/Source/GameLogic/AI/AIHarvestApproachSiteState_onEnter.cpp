// cl: /DNDEBUG /MD /EHsc- /ICode/Libraries/Source/WWVegas/WWMath
// AIHarvestApproachSiteState::onEnter, retail 0015F760 (459 bytes).
// Identity: constructor 0015FD00 names AIHarvestApproachSiteState and installs
// vtable VA010966F8; slot +10 routes through 00001870 to this body.
// Hub entry/adjustDestination ABI: docs/analysis/0x00172600.md.
// 001A62D0 is a thiscall query with FOUR dword arguments and RET10h, witnessed
// by its full 58-byte body and this caller. The two zero pushes at +44/+46
// belong to that query, not the intervening receiver vslot +1C (ST0 result).
// Opaque query/receiver names avoid the old two-argument TerrainLogic::find pin.
// Query result +18 gates the retry loop; its +1C/+20/+24 vector is copied
// BEFORE random call +CB. Destination Z is the offset alone; X/Y add goal.
// Retry accepts adjustDestination TRUE and both cell/bridge predicates FALSE.
// Real Coord3D implementations below reproduce the 24-byte frame and copies.


typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }
inline Coord3DBase &Coord3DBase::operator=(const Coord3DBase &that) {
 struct Raw { unsigned int x,y,z; }; *(Raw*)this=*(const Raw*)&that; return *this;
}
inline Coord3D &Coord3D::operator=(const Coord3D &that) { Coord3DBase *base=this; *base=that; return *this; }
inline Coord3D &Coord3D::Scale(float n) {x*=n;y*=n;z*=n;return *this;}

class LocomotorSet
{
};

class HarvestTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03(int) = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Real slot1C() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11(int) = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot44(int) = 0;

};

template <int N>
class AIUpdateVirtualSlots : public AIUpdateVirtualSlots<N - 1>
{
public:
	virtual void unusedSlot(char (*)[N]) = 0;
};

template <>
class AIUpdateVirtualSlots<0>
{
};

class AIUpdateInterface : public AIUpdateVirtualSlots<81>
{
public:
	virtual HarvestTarget *getHarvestTarget() = 0;

	LocomotorSet &getLocomotorSet()
	{
		return *(LocomotorSet *)((char *)this + 0x1a8);
	}
};

class Object
{
public:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
	AIUpdateInterface *getAI() const { return m_ai; }
};

class StateMachine
{
public:
	char m_pad00[0x10];
	Object *m_owner;
	Object *getOwner() const { return m_owner; }
};

class HarvestRecord
{
public:
	char m_pad00[0x10];
	int m_owner;
	char m_pad14[4];
	unsigned char m_isFinished;
	unsigned char m_pad19[3];
	Coord3D m_field1c;
};

extern void j_000226ab();
extern void j_00027ffc();
extern void j_0003ce25();
extern void j_00012a99();

class TerrainLogic {};

class Rva001A62D0Call {
public: HarvestRecord *invoke(const Coord3D *, Real, int, int);
};

class Pathfinder
{
public:
	Bool adjustDestination(Object *o, const LocomotorSet &l, Coord3D *d, const Coord3D *g) {
        struct Call { Bool invoke(Object *, const LocomotorSet &, Coord3D *, const Coord3D *); };
        typedef Bool (Call::*Fn)(Object *, const LocomotorSet &, Coord3D *, const Coord3D *);
        union { void (*raw)(); Fn fn; } u; u.raw=j_00027ffc;
        return (reinterpret_cast<Call *>(this)->*u.fn)(o,l,d,g);
    }
	Bool bfmeGroundCellThreshold(const Coord3D *position, Bool b) {
        struct Call { Bool invoke(const Coord3D *, Bool); };
        typedef Bool (Call::*Fn)(const Coord3D *, Bool);
        union { void (*raw)(); Fn fn; } u; u.raw=j_0003ce25;
	        return (reinterpret_cast<Call *>(this)->*u.fn)(position,b);
    }
	char bfmeAnyBridgeAt(const Coord3D *position) {
        struct Call { char invoke(const Coord3D *); };
        typedef char (Call::*Fn)(const Coord3D *);
        union { void (*raw)(); Fn fn; } u; u.raw=j_00012a99;
	        return (reinterpret_cast<Call *>(this)->*u.fn)(position);
    }
};

class AI
{
public:
	char m_pad00[0x0c];
	Pathfinder *m_pathfinder;

	Pathfinder *pathfinder()
	{
		return m_pathfinder;
	}
};

class AIInternalMoveToState
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
};

class AIHarvestApproachSiteState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

	char m_pad04[0x18];
	StateMachine *m_machine;
	char m_pad20[4];
	Coord3D m_goalPosition;
	Object *getMachineOwner() const { return m_machine->getOwner(); }
};

extern TerrainLogic *TheTerrainLogic;
#define TheAI (*(AI **)0x012EF214)
extern Real GetGameLogicRandomValueReal(Real, Real, char *, int);


StateReturnType AIHarvestApproachSiteState::onEnter()
{
	register HarvestTarget *targetPointer;
	register Coord3D *position;
	register HarvestRecord *record;
	register int attempt;
	targetPointer = m_machine->m_owner->m_ai->getHarvestTarget();
	if (targetPointer == 0)
		return STATE_FAILURE;
	HarvestTarget &target = *targetPointer;

	position = (Coord3D *)((char *)m_machine + 0x24);
	if (position == 0)
		return STATE_FAILURE;

	typedef HarvestRecord *(Rva001A62D0Call::*FindCall)(const Coord3D *, Real, int, int);
	union { void (*raw)(); FindCall fn; } findCall;
	findCall.raw = j_000226ab;
	record = (reinterpret_cast<Rva001A62D0Call *>(TheTerrainLogic)->*findCall.fn)(
		position, target.slot1C(), 0, 0);
	if (record == 0)
	{
		target.slot11(1);
		return STATE_FAILURE;
	}

	target.slot44(record->m_owner);
	m_goalPosition = *position;
	if (!record->m_isFinished)
		return AIInternalMoveToState::onEnter();

	Coord3D offset(record->m_field1c);
#line 95 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIHarvest.cpp"
	Real scale = GetGameLogicRandomValueReal(0.5f, 5.0f, __FILE__, __LINE__);
	offset.Scale(scale);

	attempt = 0;
	for (; attempt < 5; ++attempt)
	{
		Coord3D destination;
		destination.z = offset.z;
		destination.x = m_goalPosition.x + offset.x;
		destination.y = m_goalPosition.y + offset.y;
		if (TheAI->pathfinder()->adjustDestination(getMachineOwner(),
			getMachineOwner()->getAI()->getLocomotorSet(),
			&destination, 0) &&
			!TheAI->pathfinder()->bfmeGroundCellThreshold(&destination, 0) &&
			!TheAI->pathfinder()->bfmeAnyBridgeAt(&destination))
		{
			m_goalPosition = destination;
			return AIInternalMoveToState::onEnter();
		}

		offset.x *= 0.5f;
		offset.y *= 0.5f;
		offset.z *= 0.5f;
	}

	return AIInternalMoveToState::onEnter();
}

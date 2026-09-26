// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// AIFearState::onEnter, retail RVA 0x00189800 (456 bytes).
// Hub ABI: docs/analysis/0x00172600.md. Geometry storage is 0x5C bytes;
// copy at 000FFD10 and cleanup at 000FFCA0 use the same local +2C.
// Normalizer body below is the existing coord3d.cpp implementation (79 bytes),
// visible but not inlined: its actual non-escaping behavior lets VC7.1 discard
// dead direction.x/y stores. Both normalizer and this caller byte-match.
// Native coordinate copy and getMachineOwner()->getAI() recover register
// allocation. 20.0f is read from retail literal VA010977E0 (41A00000).
// The constructor at 0x0017F4F0 installs vtable 0x0109A458 and stores the
// AIFearState name. Its vtable slot +0x10 reaches this body through a thunk.

// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
template<int N> class Rva00189800Flags {
public:
 bool test(unsigned int n) const { if (bits._M_getword(n) & bits._S_maskbit(n)) return true; return false; }
 void set(unsigned int n) { bits._Unchecked_set(n); }
private: _STL::bitset<N> bits;
};
typedef bool Bool;

enum StateReturnType
{
	STATE_FAILURE = -2
};

#include "coord3d.h"
#include <math.h>
inline __declspec(noinline) void Coord3D::normalize() {
 float len=(float)sqrt(x*x+y*y+z*z);
 if(len != 0.0f) { float scale=1.0f/len; x*=scale; y*=scale; z*=scale; }
}

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D &Coord3D::Scale(float scale) { x*=scale; y*=scale; z*=scale; return *this; }
inline Coord3D &Coord3D::Add(const Coord3DBase &that) { x+=that.x; y+=that.y; z+=that.z; return *this; }
inline Coord3D &Coord3D::Sub(const Coord3DBase &that) { x-=that.x; y-=that.y; z-=that.z; return *this; }
inline Coord3D &Coord3D::Sub(const Coord3DBase &left, const Coord3DBase &right) { x=left.x-right.x; y=left.y-right.y; z=left.z-right.z; return *this; }

inline Coord3D::Coord3D(const Coord3D &that) { x=that.x; y=that.y; z=that.z; }


extern void j_0002b355();
extern void j_000309f4();

class GeometryInfo;
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &source);
	virtual ~GeometryInfo();
	float getMaxHeightAbovePosition() const;

private:
	unsigned char m_body[0x58];
};


class AIUpdateInterfaceVTable
{
#define BFME_VTABLE_SLOT(offset) virtual void slot##offset();
	BFME_VTABLE_SLOT(000) BFME_VTABLE_SLOT(004) BFME_VTABLE_SLOT(008) BFME_VTABLE_SLOT(00C)
	BFME_VTABLE_SLOT(010) BFME_VTABLE_SLOT(014) BFME_VTABLE_SLOT(018) BFME_VTABLE_SLOT(01C)
	BFME_VTABLE_SLOT(020) BFME_VTABLE_SLOT(024) BFME_VTABLE_SLOT(028) BFME_VTABLE_SLOT(02C)
	BFME_VTABLE_SLOT(030) BFME_VTABLE_SLOT(034) BFME_VTABLE_SLOT(038) BFME_VTABLE_SLOT(03C)
	BFME_VTABLE_SLOT(040) BFME_VTABLE_SLOT(044) BFME_VTABLE_SLOT(048) BFME_VTABLE_SLOT(04C)
	BFME_VTABLE_SLOT(050) BFME_VTABLE_SLOT(054) BFME_VTABLE_SLOT(058) BFME_VTABLE_SLOT(05C)
	BFME_VTABLE_SLOT(060) BFME_VTABLE_SLOT(064) BFME_VTABLE_SLOT(068) BFME_VTABLE_SLOT(06C)
	BFME_VTABLE_SLOT(070) BFME_VTABLE_SLOT(074) BFME_VTABLE_SLOT(078) BFME_VTABLE_SLOT(07C)
	BFME_VTABLE_SLOT(080) BFME_VTABLE_SLOT(084) BFME_VTABLE_SLOT(088) BFME_VTABLE_SLOT(08C)
	BFME_VTABLE_SLOT(090) BFME_VTABLE_SLOT(094) BFME_VTABLE_SLOT(098) BFME_VTABLE_SLOT(09C)
	BFME_VTABLE_SLOT(0A0) BFME_VTABLE_SLOT(0A4) BFME_VTABLE_SLOT(0A8) BFME_VTABLE_SLOT(0AC)
	BFME_VTABLE_SLOT(0B0) BFME_VTABLE_SLOT(0B4) BFME_VTABLE_SLOT(0B8) BFME_VTABLE_SLOT(0BC)
	BFME_VTABLE_SLOT(0C0) BFME_VTABLE_SLOT(0C4) BFME_VTABLE_SLOT(0C8) BFME_VTABLE_SLOT(0CC)
	BFME_VTABLE_SLOT(0D0) BFME_VTABLE_SLOT(0D4) BFME_VTABLE_SLOT(0D8) BFME_VTABLE_SLOT(0DC)
	BFME_VTABLE_SLOT(0E0) BFME_VTABLE_SLOT(0E4) BFME_VTABLE_SLOT(0E8) BFME_VTABLE_SLOT(0EC)
	BFME_VTABLE_SLOT(0F0) BFME_VTABLE_SLOT(0F4) BFME_VTABLE_SLOT(0F8) BFME_VTABLE_SLOT(0FC)
	BFME_VTABLE_SLOT(100) BFME_VTABLE_SLOT(104) BFME_VTABLE_SLOT(108) BFME_VTABLE_SLOT(10C)
	BFME_VTABLE_SLOT(110) BFME_VTABLE_SLOT(114) BFME_VTABLE_SLOT(118) BFME_VTABLE_SLOT(11C)
	BFME_VTABLE_SLOT(120) BFME_VTABLE_SLOT(124) BFME_VTABLE_SLOT(128) BFME_VTABLE_SLOT(12C)
	BFME_VTABLE_SLOT(130) BFME_VTABLE_SLOT(134) BFME_VTABLE_SLOT(138) BFME_VTABLE_SLOT(13C)
	BFME_VTABLE_SLOT(140) BFME_VTABLE_SLOT(144) BFME_VTABLE_SLOT(148) BFME_VTABLE_SLOT(14C)
	BFME_VTABLE_SLOT(150) BFME_VTABLE_SLOT(154) BFME_VTABLE_SLOT(158) BFME_VTABLE_SLOT(15C)
	BFME_VTABLE_SLOT(160) BFME_VTABLE_SLOT(164) BFME_VTABLE_SLOT(168) BFME_VTABLE_SLOT(16C)
	BFME_VTABLE_SLOT(170) BFME_VTABLE_SLOT(174) BFME_VTABLE_SLOT(178) BFME_VTABLE_SLOT(17C)
	BFME_VTABLE_SLOT(180) BFME_VTABLE_SLOT(184) BFME_VTABLE_SLOT(188) BFME_VTABLE_SLOT(18C)
	BFME_VTABLE_SLOT(190) BFME_VTABLE_SLOT(194) BFME_VTABLE_SLOT(198) BFME_VTABLE_SLOT(19C)
	BFME_VTABLE_SLOT(1A0) BFME_VTABLE_SLOT(1A4) BFME_VTABLE_SLOT(1A8) BFME_VTABLE_SLOT(1AC)
	BFME_VTABLE_SLOT(1B0) BFME_VTABLE_SLOT(1B4) BFME_VTABLE_SLOT(1B8) BFME_VTABLE_SLOT(1BC)
	BFME_VTABLE_SLOT(1C0) BFME_VTABLE_SLOT(1C4) BFME_VTABLE_SLOT(1C8) BFME_VTABLE_SLOT(1CC)
	BFME_VTABLE_SLOT(1D0) BFME_VTABLE_SLOT(1D4) BFME_VTABLE_SLOT(1D8) BFME_VTABLE_SLOT(1DC)
	BFME_VTABLE_SLOT(1E0) BFME_VTABLE_SLOT(1E4) BFME_VTABLE_SLOT(1E8) BFME_VTABLE_SLOT(1EC)
	BFME_VTABLE_SLOT(1F0) BFME_VTABLE_SLOT(1F4) BFME_VTABLE_SLOT(1F8)
#undef BFME_VTABLE_SLOT
};

extern void j_0003bcff();

class AIUpdateInterface : public AIUpdateInterfaceVTable
{
public:
	virtual void chooseLocomotorSet(unsigned int set);
	void requestPath(Coord3D *destination, Bool isFinalGoal) {
        struct Call { void invoke(Coord3D *, Bool); };
        typedef void (Call::*Fn)(Coord3D *, Bool);
        union { void (*raw)(); Fn fn; } u;
        u.raw=j_0003bcff;
        (reinterpret_cast<Call *>(this)->*u.fn)(destination,isFinalGoal);
    }
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xAC - 0x44];
	GeometryInfo m_geometry;
	unsigned char m_pad108[8];
	Rva00189800Flags<320> m_modelConditionFlags;
	unsigned char m_pad138[0x204 - 0x138];
	AIUpdateInterface *m_ai;

	void notifyModelConditionChanged();
	AIUpdateInterface *getAI() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_position; }
};

class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	Object *getGoalObject();
	Object *getOwner() const { return m_owner; }
};

class AIInternalMoveToState
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	StateMachine *getMachine() const { return m_machine; }

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[0x2C];
	Bool m_adjustDestinations;
};


class AIFearState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	unsigned int m_okToRepathTimes;
	Bool m_checkForPath;
	unsigned char m_pad55[3];
	Bool m_extra;
};

class Pathfinder
{
public:
	void removeGoal(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_pad00[0x0C];
	Pathfinder *m_pathfinder;
};

extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern AI *TheAI;
extern void j_0000e570();
extern void j_00015d02();
extern void j_0002191d();
extern void j_00021e27();
extern void j_0002b355();
extern void j_0002bd82();
extern void j_000309f4();
extern void j_0003a17a();
extern void j_0003bcff();

typedef void (__cdecl *CritterDesyncLog)(void *, const char *, ...);


StateReturnType AIFearState::onEnter()
{
	AIFearState *self = this;
	if (Glo012F0239 && TheCRCParameterCheck)
		((CritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
			"CritterDesync: setAdjustDestination(FALSE) 13");

	Object *owner;
	self->m_adjustDestinations = false;
	Object *goal;
	AIUpdateInterface *ai;
	owner = (Object *)self->m_machine->m_owner;
	goal = (Object *)self->m_machine->getGoalObject();
	ai = self->getMachineOwner()->getAI();
	if (!goal || !ai)
		return STATE_FAILURE;

	GeometryInfo geometry(goal->m_geometry);
	float goalZ = goal->m_position.z;
	float ownerZ = owner->m_position.z;
	if (ownerZ - goalZ >
		reinterpret_cast<const GeometryInfo *>(&geometry)->getMaxHeightAbovePosition())
	{
		return STATE_FAILURE;
	}

	ai->chooseLocomotorSet(4);
	if (!owner->m_modelConditionFlags.test(63))
	{
		owner->m_modelConditionFlags.set(63);
		owner->notifyModelConditionChanged();
	}

	self->m_okToRepathTimes = 1;
	self->m_checkForPath = true;
	self->m_extra = false;
	Pathfinder *pathfinder = TheAI->pathfinder();
	pathfinder->removeGoal((Object *)owner);

	Coord3D destination = owner->m_position;
	Coord3D direction;
	direction.Sub(destination, goal->m_position);
	direction.normalize();
	direction.Scale(20.0f);
	destination.Add(direction);
	ai->requestPath(&destination, true);

	return AIInternalMoveToState::onEnter();
}


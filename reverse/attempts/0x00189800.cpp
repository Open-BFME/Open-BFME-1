// ?onEnter@AIFearState@@UAE?AW4StateReturnType@@XZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AIFearState::onEnter, retail RVA 0x00189800.
// The constructor at 0x0017F4F0 installs vtable 0x0109A458 and stores the
// AIFearState name. Its vtable slot +0x10 reaches this body through a thunk.

typedef bool Bool;

enum StateReturnType
{
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void normalize();
};

extern void j_0002b355();
extern void j_000309f4();

class AIFearGeometryInfo;
class AIFearGeometryInfo
{
public:
	AIFearGeometryInfo(const AIFearGeometryInfo &source);
	~AIFearGeometryInfo();
	float getMaxHeightAbovePosition() const;

private:
	void *m_vtable;
	unsigned char m_body[0x58];
};

#pragma comment(linker, "/alternatename:??0AIFearGeometryInfo@@QAE@ABV0@@Z=?j_0002b355@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AIFearGeometryInfo@@QAE@XZ=?j_000309f4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getMaxHeightAbovePosition@AIFearGeometryInfo@@QBEMXZ=?getMaxHeightAbovePosition@GeometryInfo@@QBEMXZ")

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
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

class AIUpdateInterface : public AIUpdateInterfaceVTable
{
public:
	virtual void chooseLocomotorSet(unsigned int set);
	void requestPath(Coord3D *destination, Bool adjustsDestination);
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xAC - 0x44];
	AIFearGeometryInfo m_geometry;
	unsigned char m_pad108[0x0C];
	unsigned int m_modelConditionFlags;
	unsigned char m_pad118[0x204 - 0x118];
	AIUpdateInterface *m_ai;

	void notifyModelConditionChanged();
};

struct BfmeFearObject
{
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0xAC - 0x44];
	AIFearGeometryInfo m_geometry;
	unsigned char m_pad108[0x0C];
	unsigned int m_modelConditionFlags;
	unsigned char m_pad118[0x204 - 0x118];
	AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	Object *getGoalObject();
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[0x2C];
	Bool m_adjustDestinations;
};

#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ=?j_00021e27@@YAXXZ")

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

struct BfmeFearStateMachineFields
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

struct BfmeFearStateFields
{
	unsigned char m_pad00[0x1C];
	BfmeFearStateMachineFields *m_machine;
	unsigned char m_pad20[0x2C];
	Bool m_adjustDestinations;
	unsigned char m_pad4D[3];
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

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern float g_010977E0;
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

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
typedef void (__fastcall *NotifyModelConditionChanged)(Object *);
typedef StateReturnType (__fastcall *StateOnEnter)(AIInternalMoveToState *);

StateReturnType AIFearState::onEnter()
{
	AIFearState *self = this;
	if (g_012F0239 && g_012ED4FC)
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(FALSE) 13");

	BfmeFearObject *owner;
	self->m_adjustDestinations = false;
	BfmeFearObject *goal;
	AIUpdateInterface *ai;
	owner = (BfmeFearObject *)self->m_machine->m_owner;
	goal = (BfmeFearObject *)self->m_machine->getGoalObject();
	ai = ((BfmeFearObject *)self->m_machine->m_owner)->m_ai;
	if (!goal || !ai)
		return STATE_FAILURE;

	AIFearGeometryInfo geometry(goal->m_geometry);
	float goalZ = goal->m_position.z;
	float ownerZ = owner->m_position.z;
	if (ownerZ - goalZ >
		reinterpret_cast<const GeometryInfo *>(&geometry)->getMaxHeightAbovePosition())
	{
		return STATE_FAILURE;
	}

	ai->chooseLocomotorSet(4);
	if ((owner->m_modelConditionFlags & 0x80000000) == 0)
	{
		owner->m_modelConditionFlags |= 0x80000000;
		((NotifyModelConditionChanged)j_0002191d)((Object *)owner);
	}

	self->m_okToRepathTimes = 1;
	self->m_checkForPath = true;
	self->m_extra = false;
	Pathfinder *pathfinder = (*reinterpret_cast<AI **>(0x012EF214))->pathfinder();
	pathfinder->removeGoal((Object *)owner);

	Coord3D destination = owner->m_position;
	Coord3D direction;
	direction.x = destination.x - goal->m_position.x;
	direction.y = destination.y - goal->m_position.y;
	direction.z = destination.z - goal->m_position.z;
	((void (__fastcall *)(Coord3D *))j_0002bd82)(&direction);
	destination.x += direction.x * *(const float *)0x010977E0;
	destination.y += direction.y * *(const float *)0x010977E0;
	destination.z += direction.z * *(const float *)0x010977E0;
	ai->requestPath(&destination, true);

	return ((StateOnEnter)j_00021e27)((AIInternalMoveToState *)self);
}

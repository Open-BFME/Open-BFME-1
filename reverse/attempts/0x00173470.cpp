// ?onEnter@AIMoveToState@@UAE?AW4StateReturnType@@XZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Real C++ reconstruction of AIMoveToState::onEnter.
// Retail boundary: 0x00173470..0x001735B1 inclusive (322 bytes), exclusive
// end 0x001735B2.  The 0x00173430 constructor stores vtable 0x01098F08;
// its source constructor names AIMoveToState and initializes the +0x50 flag.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class StateMachine;
class AIUpdateInterface;
class ThingTemplate;

extern void j_000022bb(void);

struct Overridable
{
	void *m_vftable;
	Overridable *m_nextOverride;
};

struct ThingTemplate
{
	void *m_vftable;
	Overridable *m_override;
	unsigned char m_unknown_008[0xc0];
	UnsignedInt m_flags;
};

struct GeometryInfo
{
	Real getMaxHeightAbovePosition() const;
};

struct Object
{
	void *m_vftable;
	ThingTemplate *m_template;
	unsigned char m_unknown_008[0x30];
	Coord3D m_position;
	unsigned char m_unknown_044[0x30];
	UnsignedInt m_id;
	unsigned char m_unknown_078[0x18c];
	AIUpdateInterface *m_ai;

	AIUpdateInterface *getAI()
	{
		return m_ai;
	}

	UnsignedInt getID() const
	{
		return m_id;
	}

	Coord3D *getPosition() const
	{
		return (Coord3D *)((unsigned char *)this + 0x38);
	}

	GeometryInfo *getGeometryInfo()
	{
		return (GeometryInfo *)((unsigned char *)this + 0xac);
	}
};

struct StateMachine
{
	unsigned char m_unknown_000[0x10];
	Object *m_owner;
	unsigned char m_unknown_014[0x10];
	Coord3D m_goalPosition;

	Coord3D *getGoalPosition()
	{
		return &m_goalPosition;
	}
};

struct AIUpdateInterface
{
	unsigned char m_unknown[0x164];

	Int getIgnoredObstacleID();
};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void j_000022bb(void);
extern void j_0000e570(void);
extern void j_0001a36b(void);
extern void j_0003a17a(void);

typedef void (__cdecl *CritterDesyncLog)(void *, const char *);
typedef Object *(__fastcall *GetGoalObject)(StateMachine *);
typedef Int (__fastcall *GetIgnoredObstacleID)(AIUpdateInterface *);

class AIInternalMoveToState
{
protected:
	unsigned char m_stateFields04[0x18];
	StateMachine *m_machine;
	unsigned char m_stateFields20[4];
	Coord3D m_goalPosition;
	unsigned char m_stateFields30[0x1c];
	Bool m_adjustDestinations;

public:
	virtual StateReturnType onEnter();
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType AIMoveToState::onEnter()
{
	register AIUpdateInterface *ai;

	if (g_012F0239 && g_012ED4FC)
		((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
			"CritterDesync: setAdjustDestination(TRUE) 4");

	m_adjustDestinations = 1;
	ai = m_machine->m_owner->getAI();
	if (((GetGoalObject)j_0000e570)(m_machine))
	{
		if (ai && ((GetGoalObject)j_0000e570)(m_machine)->getID() ==
			((GetIgnoredObstacleID)j_0001a36b)(ai))
		{
			if (g_012F0239 && g_012ED4FC)
				((CritterDesyncLog)j_0003a17a)(g_012ED4FC,
					"CritterDesync: setAdjustDestination(FALSE) 5");
			m_adjustDestinations = 0;
		}
	}

	register StateMachine *machine;
	if (((GetGoalObject)j_0000e570)(m_machine))
	{
		m_goalPosition = *(((GetGoalObject)j_0000e570)(m_machine)->getPosition());
		machine = m_machine;
		ThingTemplate **templateSlot =
			(ThingTemplate **)((unsigned char *)machine->m_owner + 4);
		const ThingTemplate *ownerTemplate = *templateSlot;
		if (ownerTemplate && ownerTemplate->m_override)
		{
			typedef ThingTemplate *(__fastcall *GetFinalOverride)(Overridable *);
			ownerTemplate = ((GetFinalOverride)j_000022bb)(
				ownerTemplate->m_override);
		}
		if (ownerTemplate && (ownerTemplate->m_flags & 0x02000000))
		{
			Real halfHeight = ((GetGoalObject)j_0000e570)(m_machine)
				->getGeometryInfo()->getMaxHeightAbovePosition() * 0.5f;
			m_goalPosition.z += halfHeight;
			if (((GetGoalObject)j_0000e570)(m_machine)->getPosition()->z <
				m_goalPosition.z)
				m_goalPosition.z += halfHeight;
		}
	}
	else
	{
		machine = m_machine;
		m_goalPosition = *machine->getGoalPosition();
	}

	return AIInternalMoveToState::onEnter();
}

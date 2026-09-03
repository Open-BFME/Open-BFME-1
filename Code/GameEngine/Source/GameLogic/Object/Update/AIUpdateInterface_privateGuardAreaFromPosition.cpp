// cl: /DNDEBUG /MD
//
// Retail 0x002794E0: AIUpdateInterface::privateGuardAreaFromPosition.  This
// is the BFME script variant of guard-area: it retains the area pointer but
// takes an optional waypoint position for the location used by the guard
// state.  A null position uses the unit's current position.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_AREA = 3,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_GUARD = 0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class PolygonTrigger;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType t) const;

private:
	virtual void slot00();
	void *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;

	unsigned char m_unmodelled_08[0x94 - 8];
	unsigned char m_flags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateGuardAreaFromPosition(const PolygonTrigger *area,
		GuardMode guardMode, CommandSourceType cmdSource,
		const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	Coord3D m_locationToGuard;
	UnsignedInt m_objectToGuard;
	unsigned char m_unmodelled_68[0x6C - 0x68];
	const PolygonTrigger *m_areaToGuard;
};

void AIUpdateInterface::privateGuardAreaFromPosition(const PolygonTrigger *area,
	GuardMode guardMode, CommandSourceType cmdSource, const Coord3D *position)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_AREA;
	else
		m_guardTargetType[0] = GUARDTARGET_AREA;

	m_guardMode = guardMode;
	m_areaToGuard = area;
	Coord3D localPosition;
	if (!position)
		area->getCenterPoint(&localPosition);
	else
		localPosition = *position;
	m_locationToGuard = localPosition;
	m_objectToGuard = 0;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

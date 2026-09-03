// cl: /DNDEBUG /MD
//
// Retail 0x00279230: the Zero Hour guard-position clone retained in the BFME
// image.  BFME's neighbouring implementation uses guard-target value 2; this
// translation unit models the older position value 0 and the player-only
// terrain clipping present in this body.

typedef bool Bool;

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
	GUARDTARGET_LOCATION = 0,
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;

	Bool isInRegionNoZ(const Coord3D *position) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType type) const;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void getExtent(Region3D *extent) const;
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual Coord3D findClosestEdgePoint(const Coord3D *position) const;
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateGuardPosition(const Coord3D *position,
		GuardMode guardMode, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	Coord3D m_locationToGuard;
};

void AIUpdateInterface::privateGuardPosition(const Coord3D *position,
	GuardMode guardMode, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_LOCATION;
	else
		m_guardTargetType[0] = GUARDTARGET_LOCATION;

	Coord3D adjusted = *position;
	if (cmdSource == CMD_FROM_PLAYER)
	{
		Region3D extent;
		TheTerrainLogic->getExtent(&extent);
		if (!extent.isInRegionNoZ(&adjusted))
			adjusted = TheTerrainLogic->findClosestEdgePoint(&adjusted);
	}

	m_locationToGuard = adjusted;
	m_guardMode = guardMode;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

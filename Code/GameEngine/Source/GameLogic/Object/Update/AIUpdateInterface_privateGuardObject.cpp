// cl: /DNDEBUG /MD
// readable body of ?privateGuardObject@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Retail 0x002793C0: AIUpdateInterface::privateGuardObject. Same +0x94 /
// isMobile / isKindOf(PROJECTILE) guards as privateGetRepaired, then the
// two-slot guard-target type, object ID at +0x74, setState(0x10).

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
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_GUARD = 0x10
};

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

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;
	unsigned char m_unmodelled_78[0x94 - 0x78];
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
	GuardMode m_guardMode;
	GuardTargetType m_guardTargetType[2];
	unsigned char m_unmodelled_58[0x64 - 0x58];
	UnsignedInt m_objectToGuard;
};

void AIUpdateInterface::privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType cmdSource)
{
	if (m_object->m_flags & 0x20)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_OBJECT;
	else
		m_guardTargetType[0] = GUARDTARGET_OBJECT;

	m_guardMode = guardMode;
	m_objectToGuard = objectToGuard->m_id;
	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

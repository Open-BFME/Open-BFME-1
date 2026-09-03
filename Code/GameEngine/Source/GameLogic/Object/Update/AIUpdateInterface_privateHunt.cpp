// cl: /DNDEBUG /MD
// readable body of ?privateHunt@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Retail 0x00279100: AIUpdateInterface::privateHunt. isMobile, inlined
// isKindOf(KINDOF_PROJECTILE), +0x94 flag, then clear and tail-call
// setState(0x11).

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

enum StateID
{
	BFME_AI_HUNT = 0x11
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[0xC8 - 8];
	UnsignedInt m_kindof[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual void slot00();
	ThingTemplate *m_template;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateHunt(CommandSourceType cmdSource);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;
};

void AIUpdateInterface::privateHunt(CommandSourceType cmdSource)
{
	if (!m_object->isMobile())
		return;

	Object *obj = m_object;
	ThingTemplate *tmpl = obj->m_template;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	if (tmpl->m_kindof[0] & 0x2000000)
		return;

	if (obj->m_flags & 0x20)
		return;

	m_stateMachine->clear();
	m_lastCommandSource = cmdSource;
	m_stateMachine->setState(BFME_AI_HUNT);
}

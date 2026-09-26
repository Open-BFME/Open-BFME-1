// ??0ActiveBody@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.35 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Probe of retail 0x00211A50 (601B). symbols.csv pins this RVA as
// ??0ActiveBody@@ and ??0BodyModule@@. WorkerAIUpdate ctor is already
// matched at 0x002C9ED0 (417B thunk). This body calls ObjectModule via
// ILT 0x000170E4 and writes vtables at +0/+0xC/+0x10 like every Body module.

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

private:
	Thing *m_thing;
	const ModuleData *m_moduleData;
};

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class BodyModule : public BehaviorModule, public BodyModuleInterface, public ModuleInterface
{
public:
	BodyModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData)
	{
	}
};

class ActiveBodyModuleData
{
public:
	virtual void anchor();
	float m_maxHealth;
	float m_initialHealth;
};

class ActiveBody : public BodyModule
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	const ActiveBodyModuleData *getActiveBodyModuleData() const
	{
		return *reinterpret_cast<const ActiveBodyModuleData *const *>((const char *)this + 8);
	}
	void validateArmorAndDamageFX() const;
	void setCorrectDamageState();

private:
	float m_currentHealth;
	float m_prevHealth;
	float m_maxHealth;
	float m_initialHealth;
	float m_currentSubdualDamage;
	int m_curDamageState;
	unsigned int m_nextDamageFXTime;
	int m_lastDamageFXDone;
	char m_lastDamageInfo[0x40];
	unsigned int m_lastDamageTimestamp;
	unsigned int m_lastHealingTimestamp;
	bool m_frontCrushed;
	bool m_backCrushed;
	bool m_lastDamageCleared;
	bool m_indestructible;
	void *m_particleSystems;
	void *m_curArmorSet;
	void *m_curDamageFX;
};

// ??0ActiveBody@@QAE@PAVThing@@PBVModuleData@@@Z
ActiveBody::ActiveBody(Thing *thing, const ModuleData *moduleData)
	: BodyModule(thing, moduleData),
	  m_curDamageFX(0),
	  m_curArmorSet(0),
	  m_frontCrushed(false),
	  m_backCrushed(false),
	  m_lastDamageTimestamp(0xffffffff),
	  m_lastHealingTimestamp(0xffffffff),
	  m_curDamageState(0),
	  m_nextDamageFXTime(0),
	  m_lastDamageFXDone(-1),
	  m_lastDamageCleared(false),
	  m_particleSystems(0),
	  m_currentSubdualDamage(0),
	  m_indestructible(false)
{
	m_currentHealth = getActiveBodyModuleData()->m_initialHealth;
	m_prevHealth = getActiveBodyModuleData()->m_initialHealth;
	m_maxHealth = getActiveBodyModuleData()->m_maxHealth;
	m_initialHealth = getActiveBodyModuleData()->m_initialHealth;
	validateArmorAndDamageFX();
	setCorrectDamageState();
}

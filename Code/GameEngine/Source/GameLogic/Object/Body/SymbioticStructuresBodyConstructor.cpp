// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);
	virtual ~ActiveBody();

private:
	unsigned char m_unmodelled_14[0xE0 - 0x14];
};

class SymbioticStructureLinks
{
public:
	SymbioticStructureLinks()
	{
		// Retail preserves the repeated final clear, so these writes must remain observable.
		m_unmodelled_08 = 0;
		m_unmodelled_04 = 0;
		m_unmodelled_00 = 0;
		m_unmodelled_08 = 0;
	}

private:
	volatile unsigned int m_unmodelled_00;
	volatile unsigned int m_unmodelled_04;
	volatile unsigned int m_unmodelled_08;
};

class SymbioticStructuresBody : public ActiveBody
{
public:
	SymbioticStructuresBody(Thing *thing, const ModuleData *moduleData);
	virtual ~SymbioticStructuresBody();

private:
	SymbioticStructureLinks m_links;
};

SymbioticStructuresBody::SymbioticStructuresBody(
	Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData)
{
}

SymbioticStructuresBody::~SymbioticStructuresBody()
{
}

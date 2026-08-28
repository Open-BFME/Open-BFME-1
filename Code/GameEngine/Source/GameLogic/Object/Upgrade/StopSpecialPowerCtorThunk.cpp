// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: StopSpecialPower module ctor.
// SpecialPowerModule MI + zero at +0x2c.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
};

class StopSpecialPower : public SpecialPowerModule
{
public:
	StopSpecialPower( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_pad14[0x18];
	unsigned int m_2c;
};

// ??0StopSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
StopSpecialPower::StopSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
	m_2c = 0;
}
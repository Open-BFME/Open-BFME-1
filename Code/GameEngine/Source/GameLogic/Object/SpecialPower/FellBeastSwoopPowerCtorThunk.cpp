// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FellBeastSwoopPower module ctor.
// SpecialPower-style MI base (4 vtbls at +0/+0xC/+0x10/+0x20), then zero at +0xE8.

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

class SpecialPowerModuleExtra
{
public:
	virtual void specialPowerExtraAnchor();

private:
	unsigned char m_pad[0xC];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class FellBeastSwoopPowerBase : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public SpecialPowerModuleExtra,
	public ModuleInterface
{
public:
	FellBeastSwoopPowerBase(Thing *thing, const ModuleData *moduleData);
};

class FellBeastSwoopPower : public FellBeastSwoopPowerBase
{
public:
	FellBeastSwoopPower(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0xC4]; // 0x24 .. 0xE7
	unsigned char m_e8;
};

// ??0FellBeastSwoopPower@@QAE@PAVThing@@PBVModuleData@@@Z
FellBeastSwoopPower::FellBeastSwoopPower(Thing *thing, const ModuleData *moduleData)
	: FellBeastSwoopPowerBase(thing, moduleData)
{
	m_e8 = 0;
}

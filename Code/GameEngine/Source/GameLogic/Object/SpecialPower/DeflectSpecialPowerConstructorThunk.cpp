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

class DeflectSpecialPowerIface1
{
public:
	virtual void deflectSpecialPowerIface1Anchor();
};

class DeflectSpecialPowerIface2
{
public:
	virtual void deflectSpecialPowerIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class DeflectSpecialPowerIface3
{
public:
	virtual void deflectSpecialPowerIface3Anchor();
};

class DeflectSpecialPowerIface4
{
public:
	virtual void deflectSpecialPowerIface4Anchor();

private:
	unsigned char m_pad[0x10];
};

class WeaponModeSpecialPowerUpdateBase : public BehaviorModule,
	public DeflectSpecialPowerIface1,
	public DeflectSpecialPowerIface2,
	public DeflectSpecialPowerIface3,
	public DeflectSpecialPowerIface4
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *, const ModuleData *);
};

class DeflectSpecialPowerIface5
{
public:
	virtual void deflectSpecialPowerIface5Anchor();
};

class DeflectSpecialPower : public WeaponModeSpecialPowerUpdateBase,
	public DeflectSpecialPowerIface5
{
public:
	DeflectSpecialPower(Thing *, const ModuleData *);

private:
	unsigned char m_byte3C;
	unsigned char m_byte3D;
};

// ??0DeflectSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
DeflectSpecialPower::DeflectSpecialPower(Thing *thing, const ModuleData *moduleData)
	: WeaponModeSpecialPowerUpdateBase(thing, moduleData)
{
	m_byte3C = 0;
	m_byte3D = 0;
}

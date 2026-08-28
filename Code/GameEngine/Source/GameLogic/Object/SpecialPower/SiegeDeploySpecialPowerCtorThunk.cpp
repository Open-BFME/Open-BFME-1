// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeDeploySpecialPower constructor.

class Thing;
class ModuleData;

extern "C" char SiegeDeploySpecialPower_vtbl0;
extern "C" char SiegeDeploySpecialPower_vtbl0C;
extern "C" char SiegeDeploySpecialPower_vtbl10;
extern "C" char SiegeDeploySpecialPower_vtbl20;
extern "C" char SiegeDeploySpecialPower_vtbl24;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
private:
	unsigned char m_data[8];
};

class SiegeDeploySpecialPowerIface1 { public: virtual void slot(); };
class SiegeDeploySpecialPowerIface2
{
public:
	virtual void slot();
private:
	unsigned char m_data[0x0c];
};
class SiegeDeploySpecialPowerIface3 { public: virtual void slot(); };
class SiegeDeploySpecialPowerIface4 { public: virtual void slot(); };

class SiegeDeploySpecialPowerBase : public BehaviorModule,
	public SiegeDeploySpecialPowerIface1,
	public SiegeDeploySpecialPowerIface2,
	public SiegeDeploySpecialPowerIface3,
	public SiegeDeploySpecialPowerIface4
{
public:
	SiegeDeploySpecialPowerBase(Thing *, const ModuleData *);
	virtual ~SiegeDeploySpecialPowerBase();
private:
	unsigned char m_data[0x10];
};

class __declspec(novtable) SiegeDeploySpecialPower : public SiegeDeploySpecialPowerBase
{
public:
	SiegeDeploySpecialPower(Thing *, const ModuleData *);
	virtual ~SiegeDeploySpecialPower();
private:
	volatile unsigned int m_f38;
	volatile unsigned int m_f3c;
	volatile unsigned int m_f40;
	volatile unsigned int m_f44;
	volatile unsigned int m_f48;
	volatile unsigned int m_f4c;
	volatile unsigned int m_f50;
	volatile unsigned int m_f54;
	volatile unsigned int m_f58;
	volatile unsigned int m_f5c;
	volatile bool m_f60;
	volatile unsigned int m_f64;
	volatile unsigned int m_f68;
	volatile unsigned int m_f6c;
	volatile bool m_f70;
};

// ??0SiegeDeploySpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeDeploySpecialPower::SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData)
	: SiegeDeploySpecialPowerBase(thing, moduleData)
{
	m_f38 = 0;
	m_f3c = 0;
	m_f40 = 0;
	m_f44 = 0;
	*(void *volatile *)this = &SiegeDeploySpecialPower_vtbl0;
	*(void *volatile *)((char *)this + 0x0c) = &SiegeDeploySpecialPower_vtbl0C;
	*(void *volatile *)((char *)this + 0x10) = &SiegeDeploySpecialPower_vtbl10;
	*(void *volatile *)((char *)this + 0x20) = &SiegeDeploySpecialPower_vtbl20;
	*(void *volatile *)((char *)this + 0x24) = &SiegeDeploySpecialPower_vtbl24;
	m_f48 = 0;
	m_f4c = 0;
	m_f50 = 0;
	m_f54 = 0;
	m_f58 = 0;
	m_f5c = 0;
	m_f60 = false;
	m_f64 = 0;
	m_f68 = 0;
	m_f6c = 0;
	m_f70 = false;
}

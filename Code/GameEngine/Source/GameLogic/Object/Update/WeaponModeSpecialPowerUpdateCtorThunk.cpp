// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponModeSpecialPowerUpdate module ctor.
//
// Module-ctor skeleton with five vtbls -- +0/+0xC/+0x10/+0x20/+0x24 -- and no
// interim stores, so every interface base is novtable. The base at +0x10 carries
// the twelve bytes up to +0x20; the most-derived members begin at +0x28.
//
// The only body statement is the flag at +0x38, then the helper is put to sleep
// rather than woken: retail pushes 0x3FFFFFFF, not 1.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateIface1
{
public:
	virtual void weaponModeIface1Anchor();
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateIface2
{
public:
	virtual void weaponModeIface2Anchor();

	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateIface3
{
public:
	virtual void weaponModeIface3Anchor();
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateIface4
{
public:
	virtual void weaponModeIface4Anchor();
};

class WeaponModeSpecialPowerUpdateBase : public BehaviorModule
{
public:
	WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class WeaponModeSpecialPowerUpdate : public WeaponModeSpecialPowerUpdateBase,
	public WeaponModeSpecialPowerUpdateIface1,
	public WeaponModeSpecialPowerUpdateIface2,
	public WeaponModeSpecialPowerUpdateIface3,
	public WeaponModeSpecialPowerUpdateIface4
{
public:
	WeaponModeSpecialPowerUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	Object *getObject(void) const { return m_object; }

	unsigned char m_unreconstructed_28[0x10];
	bool m_38;									///< retail this+0x38
};

// ??0WeaponModeSpecialPowerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
WeaponModeSpecialPowerUpdate::WeaponModeSpecialPowerUpdate(Thing *thing, const ModuleData *moduleData)
	: WeaponModeSpecialPowerUpdateBase(thing, moduleData)
{
	m_38 = false;

	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

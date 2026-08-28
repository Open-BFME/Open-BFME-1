// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the retail FireWeaponCollide ctor.
//
// The BFME module hierarchy predates the ZH reference headers used by the sweep
// build.  In particular, BFME's Module has no Snapshot secondary base, so the
// retail object puts the derived interface vptr at +0x10 and its fields at
// +0x14/+0x18.  These TU-local declarations preserve that ABI without changing
// the shared reference headers.

class ModuleData;
class WeaponTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
private:
	unsigned char m_pad[0x74];

public:
	unsigned int m_weaponStatus;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
public:
	Module(const ModuleData *);
	virtual ~Module();

private:
	const ModuleData *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Module
{
public:
	ObjectModule(Thing *, const ModuleData *);

protected:
	Thing *getObject() const { return m_thing; }

private:
	Thing *m_thing;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData) : ObjectModule(thing, moduleData)
	{
	}
};

class FireWeaponCollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModule : public BehaviorModule, public FireWeaponCollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData) : BehaviorModule(thing, moduleData)
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class FireWeaponCollideModuleData
{
public:
	virtual ~FireWeaponCollideModuleData();

private:
	unsigned char m_pad[4];

public:
	const WeaponTemplate *m_collideWeaponTemplate;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
private:
	unsigned char m_pad[8];

public:
	unsigned int m_status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *, WeaponSlotType) const;
};

extern WeaponStore *TheWeaponStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class FireWeaponCollide : public CollideModule
{
public:
	FireWeaponCollide(Thing *, const ModuleData *);

private:
	const FireWeaponCollideModuleData *getFireWeaponCollideModuleData() const
	{
		return reinterpret_cast<const FireWeaponCollideModuleData *>(
			*reinterpret_cast<const ModuleData *const *>(reinterpret_cast<const char *>(this) + 4));
	}

	Weapon *m_collideWeapon;
	bool m_everFired;
};

// ??0FireWeaponCollide@@QAE@PAVThing@@PBVModuleData@@@Z
FireWeaponCollide::FireWeaponCollide(Thing *thing, const ModuleData *moduleData) :
	CollideModule(thing, moduleData),
	m_collideWeapon(0)
{
	m_collideWeapon = TheWeaponStore->allocateNewWeapon(
		getFireWeaponCollideModuleData()->m_collideWeaponTemplate, PRIMARY_WEAPON);
	m_collideWeapon->m_status = getObject()->m_weaponStatus;
	m_everFired = false;
}

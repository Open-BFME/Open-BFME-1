// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class WeaponTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();

private:
	unsigned char m_data[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();

private:
	unsigned char m_data[196];
};

class SpecialAbilityUpdate : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface
{
public:
	SpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SpecialAbilityUpdate();
};

template <class T>
class BFMERetailStringBase
{
public:
	BFMERetailStringBase(const BFMERetailStringBase &other);
	~BFMERetailStringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	T *m_data;
};

class BFMERetailAsciiString : public BFMERetailStringBase<char>
{
};

class WeaponFireSpecialAbilityUpdateModuleData
{
private:
	unsigned char m_pad[0x254];

public:
	BFMERetailAsciiString m_specialWeapon;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	virtual ~Weapon();
	void loadAmmoNow(const Thing *source);

	unsigned int m_template;
	unsigned int m_attackType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(BFMERetailAsciiString name) const;
	Weapon *allocateNewWeapon(const WeaponTemplate *weaponTemplate, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);

private:
	Weapon *m_weapon;
};

// ??0WeaponFireSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
WeaponFireSpecialAbilityUpdate::WeaponFireSpecialAbilityUpdate(
	Thing *thing, const ModuleData *moduleData)
	: SpecialAbilityUpdate(thing, moduleData),
	  m_weapon(0)
{
	const WeaponFireSpecialAbilityUpdateModuleData *data =
		reinterpret_cast<const WeaponFireSpecialAbilityUpdateModuleData *>(
			*reinterpret_cast<const ModuleData **>(
				reinterpret_cast<unsigned char *>(this) + 4));
	BFMERetailAsciiString specialWeapon(data->m_specialWeapon);
	const WeaponTemplate *weaponTemplate =
		TheWeaponStore->findWeaponTemplate(specialWeapon);
	if (weaponTemplate != 0)
	{
		m_weapon = TheWeaponStore->allocateNewWeapon(weaponTemplate, PRIMARY_WEAPON);
		m_weapon->m_attackType = 0;
		m_weapon->loadAmmoNow(*reinterpret_cast<Thing **>(
			reinterpret_cast<unsigned char *>(this) + 8));
	}
}

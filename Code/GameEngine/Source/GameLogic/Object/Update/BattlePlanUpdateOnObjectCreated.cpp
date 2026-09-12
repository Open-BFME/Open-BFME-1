// ?onObjectCreated@BattlePlanUpdate@@UAEXXZ
// BFME stores the module data at +0x04, its object at +0x08, and the audio
// members at the offsets used below. The local views keep those retail offsets
// while the method body follows the Zero Hour implementation.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport

#include "../../../../../reference/shims/stringinline/StringInline.h"

typedef bool Bool;
typedef int Int;

enum
{
	WEAPONSET_VETERAN = 0,
	PRIMARY_WEAPON = 0,
	LOCKED_TEMPORARILY = 1,
	TURRET_INVALID = -1
};

enum WhichTurretType
{
	WHICH_TURRET_INVALID = -1
};

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
class AIUpdateInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
	void setWeaponLock(Int weapon, Int lock);

	AIUpdateInterface *getAI(void) const
	{
		return *(AIUpdateInterface **)((unsigned char *)this + 0x204);
	}
};

class AudioEventRTS
{
public:
	void setEventName(AsciiString eventName);
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon(void) const;
	void setTurretEnabled(WhichTurretType turret, Bool enable);
};

#pragma comment(linker, "/alternatename:?getSpecialPowerModule@Object@@QBEPAVSpecialPowerModuleInterface@@PBVSpecialPowerTemplate@@@Z=?j_000401bf@@YAXXZ")
#pragma comment(linker, "/alternatename:?getWhichTurretForCurWeapon@AIUpdateInterface@@QBE?AW4WhichTurretType@@XZ=?j_000346a3@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTurretEnabled@AIUpdateInterface@@QAEXW4WhichTurretType@@_N@Z=?j_0002abbc@@YAXXZ")

class BattlePlanUpdateModuleData
{
public:
	unsigned char m_pad00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_pad0c[0x10];
	AsciiString m_bombardmentUnpackName;
	AsciiString m_bombardmentPackName;
	AsciiString m_bombardmentMessageLabel;
	AsciiString m_bombardmentAnnouncementName;
	AsciiString m_searchAndDestroyUnpackName;
	AsciiString m_searchAndDestroyIdleName;
	AsciiString m_searchAndDestroyPackName;
	AsciiString m_searchAndDestroyMessageLabel;
	AsciiString m_searchAndDestroyAnnouncementName;
	AsciiString m_holdTheLineUnpackName;
	AsciiString m_holdTheLinePackName;
	AsciiString m_holdTheLineMessageLabel;
	AsciiString m_holdTheLineAnnouncementName;
};

class BattlePlanUpdate
{
public:
	virtual void onObjectCreated(void);

	BattlePlanUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x2c];
	SpecialPowerModuleInterface *m_specialPowerModule;
	Bool m_invalidSettings;
};

class BfmeObjE10
{
public:
	void actionA(Int flag);
};

void BattlePlanUpdate::onObjectCreated(void)
{
	Object *obj = m_object;
	const BattlePlanUpdateModuleData *data = m_moduleData;

	if (!data->m_specialPowerTemplate)
	{
		m_invalidSettings = true;
		return;
	}

	m_specialPowerModule = obj->getSpecialPowerModule(data->m_specialPowerTemplate);

	((AudioEventRTS *)((unsigned char *)this + 0xb4))->setEventName(data->m_bombardmentUnpackName);
	((AudioEventRTS *)((unsigned char *)this + 0x274))->setEventName(data->m_bombardmentPackName);
	((AudioEventRTS *)((unsigned char *)this + 0x434))->setEventName(data->m_bombardmentAnnouncementName);
	((AudioEventRTS *)((unsigned char *)this + 0x194))->setEventName(data->m_searchAndDestroyUnpackName);
	((AudioEventRTS *)((unsigned char *)this + 0x354))->setEventName(data->m_searchAndDestroyPackName);
	((AudioEventRTS *)((unsigned char *)this + 0x6d4))->setEventName(data->m_searchAndDestroyIdleName);
	((AudioEventRTS *)((unsigned char *)this + 0x514))->setEventName(data->m_searchAndDestroyAnnouncementName);
	((AudioEventRTS *)((unsigned char *)this + 0x124))->setEventName(data->m_holdTheLineUnpackName);
	((AudioEventRTS *)((unsigned char *)this + 0x2e4))->setEventName(data->m_holdTheLinePackName);
	((AudioEventRTS *)((unsigned char *)this + 0x4a4))->setEventName(data->m_holdTheLineAnnouncementName);

	((BfmeObjE10 *)m_object)->actionA(WEAPONSET_VETERAN);
	AIUpdateInterface *ai = obj->getAI();
	if (ai)
	{
		obj->setWeaponLock(PRIMARY_WEAPON, LOCKED_TEMPORARILY);
	}

	ai = m_object->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->setTurretEnabled(tur, false);
		}
	}
}

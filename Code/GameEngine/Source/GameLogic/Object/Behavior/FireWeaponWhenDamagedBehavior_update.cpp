// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/FireWeaponWhenDamagedBehavior.h"
#include "GameLogic/Object.h"

class BfmeFireWeaponUpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
};

class BfmeFireWeaponBodyModule
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual BodyDamageType getDamageState() = 0;
};

struct BfmeFireWeaponObjectBody
{
	unsigned char m_unreconstructed_000[0x200];
	BfmeFireWeaponBodyModule *m_body;
};

static Weapon *getContinuousWeapon(const char *self, unsigned int offset)
{
	return *reinterpret_cast<Weapon *const *>(self + offset);
}

UpdateSleepTime FireWeaponWhenDamagedBehavior::update(void)
{
	const char *self = reinterpret_cast<const char *>(this);
	const BfmeFireWeaponUpgradeMux *upgrade = reinterpret_cast<const BfmeFireWeaponUpgradeMux *>(self + 0x24);
	if (!upgrade->isAlreadyUpgraded())
	{
		DEBUG_ASSERTCRASH(upgrade->isAlreadyUpgraded(), ("hmm, this should not be possible"));
		return UPDATE_SLEEP_FOREVER;
	}

	const Object *obj = getObject();
	const BfmeFireWeaponObjectBody *objectBody = reinterpret_cast<const BfmeFireWeaponObjectBody *>(obj);
	BodyDamageType bdt = objectBody->m_body->getDamageState();

	if (bdt == BODY_RUBBLE)
	{
		if (getContinuousWeapon(self, 0x4c) && getContinuousWeapon(self, 0x4c)->getStatus() == READY_TO_FIRE)
		{
			getContinuousWeapon(self, 0x4c)->forceFireWeapon(obj, obj->getPosition());
		}
	}
	else if (bdt == BODY_REALLYDAMAGED)
	{
		if (getContinuousWeapon(self, 0x48) && getContinuousWeapon(self, 0x48)->getStatus() == READY_TO_FIRE)
		{
			getContinuousWeapon(self, 0x48)->forceFireWeapon(obj, obj->getPosition());
		}
	}
	else if (bdt == BODY_DAMAGED)
	{
		if (getContinuousWeapon(self, 0x44) && getContinuousWeapon(self, 0x44)->getStatus() == READY_TO_FIRE)
		{
			getContinuousWeapon(self, 0x44)->forceFireWeapon(obj, obj->getPosition());
		}
	}
	else
	{
		if (getContinuousWeapon(self, 0x40) && getContinuousWeapon(self, 0x40)->getStatus() == READY_TO_FIRE)
		{
			getContinuousWeapon(self, 0x40)->forceFireWeapon(obj, obj->getPosition());
		}
	}

	return UPDATE_SLEEP_NONE;
}

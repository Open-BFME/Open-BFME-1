// ?onDie@FireWeaponWhenDeadBehavior@@UAEXPBVDamageInfo@@@Z
// partial score=0.6 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "GameLogic/Module/FireWeaponWhenDeadBehavior.h"

class Object;
class Player;
class BfmeKeyAMB;

enum UpdateSleepTime
{
	UPDATE_SLEEP_ONE = 1
};

class UpdateModule
{
public:
	void setWakeFrame(Object *object, UpdateSleepTime wakeDelay);
};

class BfmeGateAMB
{
public:
	bool bfmeAskAMB(void *object, const BfmeKeyAMB *key);
};

class BfmeUpgradeDispatch
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation,
		UpgradeMaskType &conflicting) const;
};

class BFMEActionObject
{
public:
	bool testStatus(int status) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
};

struct BfmeArgFV
{
	unsigned char m_bytes[4];
};

struct BfmeVec3FV
{
	float x;
	float y;
	float z;
};

class BfmeThingFV
{
public:
	void bfmeComputeFV(BfmeArgFV *argument, BfmeVec3FV *position);
};

class ObjectCreationListStore
{
public:
	void bfmeCreate(void *creationList, Object *object, void *position);
};

extern ObjectCreationListStore *TheObjectCreationListStore;

#pragma comment(linker, "/alternatename:??4DamageInfoInput@@QAEAAV0@ABV0@@Z=?j_0000617c@@YAXXZ")
#pragma comment(linker, "/alternatename:?setWakeFrame@UpdateModule@@QAEXPAVObject@@W4UpdateSleepTime@@@Z=?j_000157da@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAskAMB@BfmeGateAMB@@QAE_NPAXPAUBfmeKeyAMB@@@Z=?j_000357d8@@YAXXZ")
#pragma comment(linker, "/alternatename:?testStatus@BFMEActionObject@@QBE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeComputeFV@BfmeThingFV@@QAEXPAVBfmeArgFV@@PAVBfmeVec3FV@@@Z=?j_0002f734@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeCreate@ObjectCreationListStore@@QAEXPAXPAVObject@@0@Z=?j_00035e5e@@YAXXZ")

void FireWeaponWhenDeadBehavior::onDie(const DamageInfo *damageInfo)
{
	const char *self = reinterpret_cast<const char *>(this);
	const FireWeaponWhenDeadBehaviorModuleData *data =
		*reinterpret_cast<const FireWeaponWhenDeadBehaviorModuleData *const *>(self - 8);

	if (*reinterpret_cast<const int *>(self + 0x7c) > 0)
	{
		*reinterpret_cast<DamageInfoInput *>(const_cast<char *>(self + 0x24)) =
			*reinterpret_cast<const DamageInfoInput *>(reinterpret_cast<const char *>(damageInfo) + 4);
		*reinterpret_cast<unsigned int *>(const_cast<char *>(self + 0x70)) =
			*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(damageInfo) + 0x50);
		*reinterpret_cast<unsigned int *>(const_cast<char *>(self + 0x74)) =
			*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(damageInfo) + 0x54);
		*reinterpret_cast<unsigned char *>(const_cast<char *>(self + 0x78)) =
			*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(damageInfo) + 0x58);
		reinterpret_cast<UpdateModule *>(const_cast<char *>(self - 0x0c))->setWakeFrame(
			*reinterpret_cast<Object *const *>(self - 4), UPDATE_SLEEP_ONE);
		return;
	}

	if (!isUpgradeActive() && !*reinterpret_cast<const unsigned char *>(
		*reinterpret_cast<const char *const *>(self - 8) + 0x70))
		return;
	if (!reinterpret_cast<BfmeGateAMB *>(const_cast<char *>(
		reinterpret_cast<const char *>(data) + 0x84))->bfmeAskAMB(
		*reinterpret_cast<Object *const *>(self - 4), reinterpret_cast<const BfmeKeyAMB *>(damageInfo)))
		return;
	if ((*reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(
		*reinterpret_cast<Object *const *>(self - 4)) + 0x98) & 0x200000) != 0)
		return;
	if (!*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(data) + 0x71) &&
		reinterpret_cast<const BFMEActionObject *>(*reinterpret_cast<Object *const *>(self - 4))->testStatus(2))
		return;

	UpgradeMaskType activation, conflicting;
	reinterpret_cast<BfmeUpgradeDispatch *>(reinterpret_cast<char *>(this) - 8)->getUpgradeActivationMasks(
		activation, conflicting);
	if (reinterpret_cast<const UpgradeMaskType *>(
		reinterpret_cast<const char *>(*reinterpret_cast<Object *const *>(self - 4)) + 0x224)->testForAny(conflicting))
		return;
	Player *player = (*reinterpret_cast<Object *const *>(self - 4))->getControllingPlayer();
	if (player != 0 && reinterpret_cast<const UpgradeMaskType *>(
		reinterpret_cast<const char *>(player) + 0x8c)->testForAny(conflicting))
		return;

	void *creationList = *reinterpret_cast<void *const *>(reinterpret_cast<const char *>(data) + 0xb0);
	if (creationList == 0)
		return;
	BfmeVec3FV position;
	reinterpret_cast<BfmeThingFV *>(*reinterpret_cast<Object *const *>(self - 0x20))->bfmeComputeFV(
		reinterpret_cast<BfmeArgFV *>(const_cast<char *>(reinterpret_cast<const char *>(data) + 0x78)), &position);
	TheObjectCreationListStore->bfmeCreate(
		creationList, *reinterpret_cast<Object *const *>(self - 4), &position);
}

// ?isValidToExecute@VeterancyCrateCollide@@MBE_NPBVObject@@@Z
// partial score=0.88 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Module/VeterancyCrateCollide.h"
#include "GameLogic/Object.h"

class BfmeThing932D
{
public:
	char go();
};

class BfmeExperienceTrackerCall
{
public:
	Bool isTrainable() const;
};

class BfmeObjectCall
{
public:
	Bool isSignificantlyAboveTerrain() const;
	Player *getControllingPlayer() const;
	Bool isUsingAirborneLocomotor() const;
};

class BfmeVeterancyCrateData
{
public:
	unsigned char m_pad00[0x58];
	unsigned char m_addsOwnerVeterancy;
	unsigned char m_isPilot;
	unsigned char m_pad5a[2];
	Int m_affectsUpToLevel;
};

#pragma comment(linker, "/alternatename:?isValidToExecute@CrateCollide@@MBE_NPBVObject@@@Z=?j_00025ef5@@YAXXZ")
#pragma comment(linker, "/alternatename:?go@BfmeThing932D@@QAEDXZ=?j_0001fde3@@YAXXZ")
#pragma comment(linker, "/alternatename:?isTrainable@BfmeExperienceTrackerCall@@QBE_NXZ=?j_0002a239@@YAXXZ")
#pragma comment(linker, "/alternatename:?isSignificantlyAboveTerrain@BfmeObjectCall@@QBE_NXZ=?j_00019ff1@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeObjectCall@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?isUsingAirborneLocomotor@BfmeObjectCall@@QBE_NXZ=?j_0000a001@@YAXXZ")

VeterancyCrateCollide::VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}

VeterancyCrateCollide::~VeterancyCrateCollide()
{
}

class BfmeVeterancyValidation : public CrateCollide
{
	protected:
	virtual Bool validate(const Object *other) const;

	private:
	const BfmeVeterancyCrateData *getData() const
	{
		return *reinterpret_cast<const BfmeVeterancyCrateData *const *>(
			reinterpret_cast<const char *>(this) + 0x04);
	}

	const Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this) + 0x08);
	}
};

class BfmeCrateCollideCall
{
public:
	Bool isValidToExecute(const Object *other) const;
};

#pragma comment(linker, "/alternatename:?isValidToExecute@BfmeCrateCollideCall@@QBE_NPBVObject@@@Z=?j_00025ef5@@YAXXZ")
#pragma comment(linker, "/alternatename:?isValidToExecute@VeterancyCrateCollide@@MBE_NPBVObject@@@Z=?validate@BfmeVeterancyValidation@@MBE_NPBVObject@@@Z")

Bool BfmeVeterancyValidation::validate(const Object *other) const
{
	const BfmeVeterancyCrateData *data = getData();
	if (!data)
		return false;

	if (!reinterpret_cast<const BfmeCrateCollideCall *>(this)->isValidToExecute(other))
		return false;

	if ((*reinterpret_cast<const unsigned char *>(
		reinterpret_cast<const char *>(other) + 0x344) & 1) != 0)
		return false;

	if (reinterpret_cast<const BfmeObjectCall *>(other)->isSignificantlyAboveTerrain())
		return false;

	if (getData()->m_addsOwnerVeterancy != 0)
		return false;

	ExperienceTracker *tracker = *reinterpret_cast<ExperienceTracker *const *>(
		reinterpret_cast<const char *>(other) + 0x210);
	if (!tracker || !reinterpret_cast<const BfmeExperienceTrackerCall *>(tracker)->isTrainable())
		return false;

	if (!reinterpret_cast<BfmeThing932D *>(tracker)->go())
		return false;

	if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(tracker) + 0x28) > data->m_affectsUpToLevel)
		return false;

	if (data->m_isPilot != 0)
	{
		const Object *object = getObject();
		if (reinterpret_cast<const BfmeObjectCall *>(other)->getControllingPlayer()
			!= reinterpret_cast<const BfmeObjectCall *>(object)->getControllingPlayer())
			return false;
		if (reinterpret_cast<const BfmeObjectCall *>(other)->isUsingAirborneLocomotor())
			return false;
	}

	return true;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/VeterancyCrateCollide.h"

VeterancyCrateCollide::VeterancyCrateCollide(Thing *thing, const ModuleData *moduleData)
	: CrateCollide(thing, moduleData)
{
}

VeterancyCrateCollide::~VeterancyCrateCollide()
{
}

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

class BfmeCrateCollideCall
{
	public:
	Bool isValidToExecute(const Object *other) const;
};

#pragma comment(linker, "/alternatename:?go@BfmeThing932D@@QAEDXZ=?j_0001fde3@@YAXXZ")
#pragma comment(linker, "/alternatename:?isTrainable@BfmeExperienceTrackerCall@@QBE_NXZ=?j_0002a239@@YAXXZ")
#pragma comment(linker, "/alternatename:?isSignificantlyAboveTerrain@BfmeObjectCall@@QBE_NXZ=?j_00019ff1@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeObjectCall@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?isUsingAirborneLocomotor@BfmeObjectCall@@QBE_NXZ=?j_0000a001@@YAXXZ")
#pragma comment(linker, "/alternatename:?isValidToExecute@BfmeCrateCollideCall@@QBE_NPBVObject@@@Z=?j_00025ef5@@YAXXZ")
inline const BfmeVeterancyCrateData *getBfmeVeterancyCrateData(const VeterancyCrateCollide *module)
{
	return *reinterpret_cast<const BfmeVeterancyCrateData *const *>(
		reinterpret_cast<const char *>(module) + 0x04);
}

inline const Object *getBfmeVeterancyCrateObject(const VeterancyCrateCollide *module)
{
	return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(module) + 0x08);
}

Bool VeterancyCrateCollide::isValidToExecute(const Object *other) const
{
	const BfmeVeterancyCrateData *data = getBfmeVeterancyCrateData(this);
	if (!data)
		return false;

	if (!reinterpret_cast<const BfmeCrateCollideCall *>(this)->isValidToExecute(other))
		return false;

	if ((*reinterpret_cast<const unsigned char *>(
		reinterpret_cast<const char *>(other) + 0x344) & 1) != 0)
		return false;

	if (reinterpret_cast<const BfmeObjectCall *>(other)->isSignificantlyAboveTerrain())
		return false;

	if (getBfmeVeterancyCrateData(this) && getBfmeVeterancyCrateData(this)->m_addsOwnerVeterancy != 0)
		return false;

	ExperienceTracker *tracker = *reinterpret_cast<ExperienceTracker *const *>(
		reinterpret_cast<const char *>(other) + 0x210);
	if (!tracker || !reinterpret_cast<const BfmeExperienceTrackerCall *>(tracker)->isTrainable())
		goto invalid;

	if (!reinterpret_cast<BfmeThing932D *>(tracker)->go())
		goto invalid;

	if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(tracker) + 0x28) > data->m_affectsUpToLevel)
		goto invalid;

	if (data->m_isPilot != 0)
	{
		const Object *object = getBfmeVeterancyCrateObject(this);
		if (reinterpret_cast<const BfmeObjectCall *>(other)->getControllingPlayer()
			!= reinterpret_cast<const BfmeObjectCall *>(object)->getControllingPlayer())
			goto invalid;
		if (reinterpret_cast<const BfmeObjectCall *>(other)->isUsingAirborneLocomotor())
			goto invalid;
	}

	return true;

invalid:
	return false;
}

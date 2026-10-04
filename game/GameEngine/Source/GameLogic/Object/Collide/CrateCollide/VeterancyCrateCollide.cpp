// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
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

// Retail calls through ILT thunks at these addresses; the member pointers below
// carry the real signature so the call sites keep their exact code shape.
extern void j_0001fde3();
extern void j_0002a239();
extern void j_00019ff1();
extern void j_00020824();
extern void j_0000a001();
extern void j_00025ef5();

class BfmeThing932D
{
};

class BfmeExperienceTrackerCall
{
};

class BfmeObjectCall
{
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
};

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

	typedef Bool (BfmeCrateCollideCall::*CrateCall)(const Object *) const;
	union { void (*fn)(); CrateCall call; } uCrate = { j_00025ef5 };
	if (!((reinterpret_cast<const BfmeCrateCollideCall *>(this)->*uCrate.call)(other)))
		return false;

	if ((*reinterpret_cast<const unsigned char *>(
		reinterpret_cast<const char *>(other) + 0x344) & 1) != 0)
		return false;

	typedef Bool (BfmeObjectCall::*AboveTerrainCall)() const;
	union { void (*fn)(); AboveTerrainCall call; } uAbove = { j_00019ff1 };
	if ((reinterpret_cast<const BfmeObjectCall *>(other)->*uAbove.call)())
		return false;

	if (getBfmeVeterancyCrateData(this) && getBfmeVeterancyCrateData(this)->m_addsOwnerVeterancy != 0)
		return false;

	ExperienceTracker *tracker = *reinterpret_cast<ExperienceTracker *const *>(
		reinterpret_cast<const char *>(other) + 0x210);
	typedef Bool (BfmeExperienceTrackerCall::*TrainableCall)() const;
	union { void (*fn)(); TrainableCall call; } uTrainable = { j_0002a239 };
	if (!tracker || !(reinterpret_cast<const BfmeExperienceTrackerCall *>(tracker)->*uTrainable.call)())
		goto invalid;

	typedef char (BfmeThing932D::*GoCall)();
	union { void (*fn)(); GoCall call; } uGo = { j_0001fde3 };
	if (!(reinterpret_cast<BfmeThing932D *>(tracker)->*uGo.call)())
		goto invalid;

	if (*reinterpret_cast<const Int *>(reinterpret_cast<const char *>(tracker) + 0x28) > data->m_affectsUpToLevel)
		goto invalid;

	if (data->m_isPilot != 0)
	{
		typedef Player *(BfmeObjectCall::*ControllingPlayerCall)() const;
		union { void (*fn)(); ControllingPlayerCall call; } uPlayer = { j_00020824 };
		const Object *object = getBfmeVeterancyCrateObject(this);
		if ((reinterpret_cast<const BfmeObjectCall *>(other)->*uPlayer.call)()
			!= (reinterpret_cast<const BfmeObjectCall *>(object)->*uPlayer.call)())
			goto invalid;
		typedef Bool (BfmeObjectCall::*AirborneCall)() const;
		union { void (*fn)(); AirborneCall call; } uAir = { j_0000a001 };
		if ((reinterpret_cast<const BfmeObjectCall *>(other)->*uAir.call)())
			goto invalid;
	}

	return true;

invalid:
	return false;
}

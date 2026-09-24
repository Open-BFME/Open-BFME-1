// ?calcPhysicsXformTreads@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// partial score=0.3 date=2026-09-24
// ?calcPhysicsXformTreads@Drawable@@IAEXPBVLocomotor@@AAUPhysicsXformInfo@1@@Z
// cl: /DNDEBUG /DWIN32 /MD /GX- /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// cl: /DNDEBUG /DWIN32 /MD /EHsc- /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
#define Matrix4x4 Matrix4
#define Snapshot BfmeDrawableSnapshot
#include "PreRTS.h"
#include "Common/GameMemory.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "GameClient/Drawable.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"

// BFME layout witnesses place Drawable::m_object at +0xFC and
// Drawable::m_locoInfo at +0x138.  The retail body accesses only those fields.
struct Rva004143F0DrawableView
{
	char pad00[0xFC];
	Object *object;
	char pad100[0x38];
	DrawableLocoInfo *locoInfo;
};

void Drawable::calcPhysicsXformTreads(const Locomotor *locomotor, PhysicsXformInfo &info)
{
	Rva004143F0DrawableView *self = reinterpret_cast<Rva004143F0DrawableView *>(this);
	DrawableLocoInfo *&locoInfo = self->locoInfo;
	if (locoInfo == NULL)
		locoInfo = newInstance(DrawableLocoInfo);

	const Real accelPitchLimit = locomotor->getAccelPitchLimit();
	const Real pitchStiffness = locomotor->getPitchStiffness();
	const Real rollStiffness = locomotor->getRollStiffness();
	const Real pitchDamping = locomotor->getPitchDamping();
	const Real rollDamping = locomotor->getRollDamping();
	const Real uniformAxialDamping = locomotor->getUniformAxialDamping();

	Object *obj = self->object;
	if (obj == NULL || *reinterpret_cast<void **>(reinterpret_cast<char *>(obj) + 0x204) == NULL)
		return;

	locoInfo->m_pitchRate += -pitchStiffness * locoInfo->m_pitch - pitchDamping * locoInfo->m_pitchRate;
	locoInfo->m_rollRate += -rollStiffness * locoInfo->m_roll - rollDamping * locoInfo->m_rollRate;

	const Bool disabled = (reinterpret_cast<const UnsignedByte *>(obj)[0x344] & 1) != 0;
	if (!disabled)
	{
		locoInfo->m_pitch += locoInfo->m_pitchRate * uniformAxialDamping;
		locoInfo->m_roll += locoInfo->m_rollRate * uniformAxialDamping;

		locoInfo->m_accelerationPitchRate +=
			-pitchStiffness * locoInfo->m_accelerationPitch - pitchDamping * locoInfo->m_accelerationPitchRate;
		locoInfo->m_accelerationPitch += locoInfo->m_accelerationPitchRate;
		locoInfo->m_accelerationRollRate +=
			-rollStiffness * locoInfo->m_accelerationRoll - rollDamping * locoInfo->m_accelerationRollRate;
		locoInfo->m_accelerationRoll += locoInfo->m_accelerationRollRate;
	}
	else
	{
		locoInfo->m_accelerationPitch *= 0.5f;
		if (fabs(locoInfo->m_accelerationPitch) <= 0.0001f)
			locoInfo->m_accelerationPitch = 0.0f;
		locoInfo->m_accelerationRoll *= 0.5f;
		if (fabs(locoInfo->m_accelerationRoll) <= 0.0001f)
			locoInfo->m_accelerationRoll = 0.0f;
	}

	info.m_totalPitch = locoInfo->m_accelerationPitch + locoInfo->m_pitch;
	info.m_totalRoll = locoInfo->m_accelerationRoll + locoInfo->m_roll;

	if (locoInfo->m_accelerationPitch > accelPitchLimit)
		locoInfo->m_accelerationPitch = accelPitchLimit;
	else if (locoInfo->m_accelerationPitch < -accelPitchLimit)
		locoInfo->m_accelerationPitch = -accelPitchLimit;
	if (locoInfo->m_accelerationRoll > accelPitchLimit)
		locoInfo->m_accelerationRoll = accelPitchLimit;
	else if (locoInfo->m_accelerationRoll < -accelPitchLimit)
		locoInfo->m_accelerationRoll = -accelPitchLimit;

	if (!disabled)
	{
		const Real rudderDegree = locomotor->getRudderCorrectionDegree();
		const Real rudderRate = locomotor->getRudderCorrectionRate();
		const Real elevatorDegree = locomotor->getElevatorCorrectionDegree();
		const Real elevatorRate = locomotor->getElevatorCorrectionRate();
		info.m_totalYaw = rudderDegree * sin(locoInfo->m_yawModulator += rudderRate);
		info.m_totalPitch += elevatorDegree * cos(locoInfo->m_pitchModulator += elevatorRate);
	}

	info.m_totalZ = 0.0f;
}

// Retail 0x00170020: BFME AIIdleState::onEnter layout and side effects.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"

namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/ActionManager.h"
#include "Common/AudioHandleSpecialValues.h"
#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GlobalData.h"
#include "Common/Money.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"
#include "Common/XFerCRC.h"

#include "GameClient/ControlBar.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"

#include "GameLogic/AIDock.h"
#include "GameLogic/AIGuard.h"
#include "GameLogic/AIGuardRetaliate.h"
#include "GameLogic/AITNGuard.h"
#include "GameLogic/AIStateMachine.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Squad.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"

// BFME's State base stores machine at +0x1c; the Zero Hour declaration is four bytes larger.
struct BfmeAIIdleOnEnterOverride
{
	void *m_vtable;
	BfmeAIIdleOnEnterOverride *m_nextOverride;
};

struct BfmeAIIdleOnEnterTemplate
{
	void *m_vtable;
	BfmeAIIdleOnEnterOverride *m_nextOverride;
	unsigned char m_pad008[0x20 - 8];
	char *m_nameData;
	unsigned char m_pad024[0x4cd - 0x24];
	UnsignedByte m_bfmeIdleFlag;
};

struct BfmeAIIdleOnEnterFiringTracker
{
	unsigned char m_pad000[0x20];
	UnsignedInt m_field020;
};

struct BfmeAIIdleOnEnterObject
{
	unsigned char m_pad000[4];
	BfmeAIIdleOnEnterTemplate *m_template;
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad044[0x74 - 0x44];
	UnsignedInt m_id;
	unsigned char m_pad078[0x1ec - 0x78];
	BfmeAIIdleOnEnterFiringTracker *m_firingTracker;
	unsigned char m_pad1f0[0x204 - 0x1f0];
	AIUpdateInterface *m_ai;
};

struct BfmeAIIdleOnEnterMachine
{
	unsigned char m_pad000[0x10];
	BfmeAIIdleOnEnterObject *m_owner;
};

struct BfmeAIIdleOnEnterState
{
	unsigned char m_pad000[0x1c];
	StateMachine *m_machine;
	unsigned char m_pad020[4];
	UnsignedShort m_initialSleepOffset;
	Bool m_shouldLookForTargets;
	Bool m_inited;
};

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern char Rva006A16B0Empty[];
extern void j_000022bb(void);
extern void j_0003a17a(void);
extern void j_00001bae(void);

typedef void (__cdecl *BfmeAIIdleCritterDesyncLog)(
	CRCParameterCheck *, const char *, ...);
typedef int (__cdecl *BfmeAIIdleRandomValue)(int, int, char *, int);
typedef const BfmeAIIdleOnEnterOverride *(__fastcall *BfmeAIIdleGetFinalOverride)(
	const BfmeAIIdleOnEnterOverride *);

DECLARE_PERF_TIMER(AIIdleState)
StateReturnType AIIdleState::onEnter()
{
	USE_PERF_TIMER(AIIdleState)
	BfmeAIIdleOnEnterState &self = *(BfmeAIIdleOnEnterState *)this;
	BfmeAIIdleOnEnterObject *obj =
		((BfmeAIIdleOnEnterMachine *)self.m_machine)->m_owner;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
		ai->resetNextMoodCheckTime();
	self.m_inited = true;

	BfmeAIIdleOnEnterTemplate *templateObject = obj->m_template;
	if (templateObject && templateObject->m_nextOverride)
		templateObject = (BfmeAIIdleOnEnterTemplate *)
			((BfmeAIIdleGetFinalOverride)j_000022bb)(templateObject->m_nextOverride);
	if (templateObject->m_bfmeIdleFlag)
	{
		BfmeAIIdleOnEnterFiringTracker *tracker = obj->m_firingTracker;
		if (tracker)
			tracker->m_field020 = 0;
	}

	if (CRCParameterCheck *crc = TheCRCParameterCheck)
	{
		UnsignedInt id = obj->m_id;
		const char *name;
		templateObject = obj->m_template;
		if (templateObject && templateObject->m_nextOverride)
			templateObject = (BfmeAIIdleOnEnterTemplate *)
				((BfmeAIIdleGetFinalOverride)j_000022bb)(templateObject->m_nextOverride);
		if (templateObject->m_nameData)
			name = templateObject->m_nameData + 8;
		else
			name = Rva006A16B0Empty;
		((BfmeAIIdleCritterDesyncLog)j_0003a17a)(crc,
			"AIIdleState::onEnter() called for object %s(%d) at location %g,%g,%g.",
			name, id, (double)obj->m_position.x,
			(double)obj->m_position.y, (double)obj->m_position.z);
	}

	self.m_initialSleepOffset = (UnsignedShort)((BfmeAIIdleRandomValue)j_00001bae)(
		0, 10,
		(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp",
		0x7a2);
	return STATE_CONTINUE;
}

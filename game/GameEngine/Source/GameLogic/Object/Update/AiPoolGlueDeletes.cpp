// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// AiPoolGlueDeletes.cpp -------------------------------------------------
//
// Retail folds every class's pool-glue `operator delete(void *, MagicEnum)`
// onto one 12-byte body at 0x007EFFF0 that calls the CRT free import thunk,
// not ::operator delete (0x00881EB0), because the shipped header spells the
// glue `::operator delete(p)`. AIUpdate.cpp cannot carry the TU-scoped
// override while other rows in it are still red, so this TU carries it for
// the three AI classes exactly as Common/RTS/RtsPoolGlueDeletes.cpp does for
// the eleven Player.cpp ones.
// The override has to be in place before PreRTS.h pulls in the pool-glue
// users, so open GameMemory.h (which defines the macro) by hand first;
// PreRTS.h then re-includes these as no-ops.
#include "Lib/Basetype.h"
#include "Common/STLTypedefs.h"
#include "Common/Errors.h"
#include "Common/Debug.h"
#include "Common/AsciiString.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameCommon.h"
#include "Common/GameMemory.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
// MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE, which all three classes use,
// expands through this macro, so overriding it here reaches all of them.
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
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
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
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
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameLogic/Module/UpdateModule.h"	// TurretAI.h uses UpdateSleepTime
#include "GameLogic/AIStateMachine.h"
#include "GameLogic/TurretAI.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

// Taking the address of the placement delete is what forces MSVC to emit the
// inline body; the pointers themselves are constant-initialised data.
#define EMIT_POOL_GLUE_DELETE(cls) \
	void (*bfme_pool_glue_delete_##cls)(void *, cls::cls##MagicEnum) = &cls::operator delete;

EMIT_POOL_GLUE_DELETE( AIStateMachine )
EMIT_POOL_GLUE_DELETE( TurretAI )
EMIT_POOL_GLUE_DELETE( TurretAIData )

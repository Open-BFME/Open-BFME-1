// cl: /DNDEBUG /MD /EHa /Oy-
// BFME Debug::PreStaticInit: lazily constructs the Debug singleton held in
// the shared diagnostic-manager global (0x01336E5C) in memory from the debug
// allocator (Zero Hour placement-new idiom, debug_io_ods.cpp), then bumps the
// counter at +0x9C7C.  The Zero Hour twin (debug_debug.cpp) initialised a
// static instance instead; BFME calls ??0Debug@@AAE@XZ at 0x00889370.

#include <new>

void *DebugAllocMemory(unsigned numBytes);

class BfmeAwakenDebug;
extern BfmeAwakenDebug *TheBfmeAwakenDebug;

class Debug
{
	Debug();

	unsigned char m_unmodelled0000[0x9C7C];
	int m_unmodelled9C7C;
	unsigned char m_unmodelled9C80[0x9F5C - 0x9C80];

	static Debug *PreStaticInit();
};

#define TheDebugInstance (*(Debug **)&TheBfmeAwakenDebug)

Debug *Debug::PreStaticInit()
{
	if (!TheDebugInstance)
		TheDebugInstance = new (DebugAllocMemory(sizeof(Debug))) Debug();
	++TheDebugInstance->m_unmodelled9C7C;
	return TheDebugInstance;
}

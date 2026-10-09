// cl: /DNDEBUG /MD /EHs-c- /Oy- /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include

#include <windows.h>
class Debug;
#include "internal_except.h"

extern "C" void *__cdecl memset(void *, int, unsigned int);
void Rva008894F0VCall(void);
extern void *g_rva0088e970Found;
typedef void (__cdecl *RaiseExceptionProc)(DWORD, DWORD, DWORD, const DWORD *);

typedef char ExceptionRecordSizeCheck[sizeof(EXCEPTION_RECORD) == 80 ? 1 : -1];
typedef char ContextSizeCheck[sizeof(CONTEXT) == 716 ? 1 : -1];

// Open BFME 2: Code/Libraries/Source/WWVegas/WWDebug/DebugRaiseExceptionHook.cpp.
// ?d_0088e8d0@@YGXKKKPBK@Z
void __stdcall d_0088e8d0(DWORD code, DWORD flags, DWORD numArgs, const DWORD *args)
{
	if (((bool (__cdecl *)(void))Rva008894F0VCall)())
	{
		EXCEPTION_RECORD record;
		memset(&record, 0, sizeof(record));
		record.ExceptionCode = 0xE06D7363;

		DWORD raiseEbp, raiseEip, raiseEsp;
		__asm
		{
		here:
			lea eax, here
			mov raiseEip, eax
			mov raiseEbp, ebp
			mov raiseEsp, esp
		}

		CONTEXT context;
		memset(&context, 0, sizeof(context));
		context.Eip = raiseEip;
		context.Ebp = raiseEbp;
		context.Esp = raiseEsp;

		_EXCEPTION_POINTERS pointers;
		pointers.ExceptionRecord = &record;
		pointers.ContextRecord = &context;
		DebugExceptionhandler::ExceptionFilter(&pointers);
	}
	((RaiseExceptionProc)g_rva0088e970Found)(code, flags, numArgs, args);
}


// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PLAT~MIB/Include
#include <objbase.h>

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

extern "C" __declspec(dllimport) void __stdcall CoUninitialize(void);

struct BfmeObjECF
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		unsigned long(__stdcall *slot08)(BfmeObjECF *);
		void *slot0c;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1c;
		long(__stdcall *slot20)(BfmeObjECF *);
	};

	Vtable *vtable;
    // ?shutdown@BfmeObjECF@@QAEXXZ absent-from-retail
    void shutdown() {
        long result = vtable->slot20(this);
        if (result < 0) _com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
    }
};

extern BfmeObjECF *g_bfmeObjECF;
extern HWND g_bfmeObjECFFlag27C;
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Open BFME 2 donor Code/GameEngine/Source/Common/BfmeConv804.cpp.
void __cdecl rva00958ba0() {
    if (g_bfmeObjECF) {
        g_bfmeObjECF->shutdown();
        if (g_bfmeObjECF) {
            BfmeObjECF *browser = g_bfmeObjECF;
            g_bfmeObjECF = 0;
            browser->vtable->slot08(browser);
        }
        g_bfmeObjECFFlag27C = 0;
        CoUninitialize();
        _ReadWriteBarrier();
    }
}

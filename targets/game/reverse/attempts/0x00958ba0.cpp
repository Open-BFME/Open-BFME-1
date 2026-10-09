// ?rva00958ba0@@YAXXZ
// partial score=0.987 date=2026-10-09
// ?rva00958ba0@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

extern "C" __declspec(dllimport) void __stdcall CoUninitialize(void);

class BfmeObjECF
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
    void shutdown() {
        long result = vtable->slot20(this);
        if (result < 0) _com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
    }
};

extern BfmeObjECF *g_bfmeObjECF;
extern int g_bfmeObjECFFlag27C;
// Open BFME 2 donor Code/GameEngine/Source/Common/BfmeConv804.cpp.
void rva00958ba0() {
    if (g_bfmeObjECF) {
        g_bfmeObjECF->shutdown();
        if (g_bfmeObjECF) {
            BfmeObjECF *browser = g_bfmeObjECF;
            g_bfmeObjECF = 0;
            browser->vtable->slot08(browser);
        }
        g_bfmeObjECFFlag27C = 0;
        CoUninitialize();
    }
}

// ?rva00958ba0@@YAXXZ
// partial score=0.7 date=2026-09-06
// ?rva00958ba0@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

extern "C" __declspec(dllimport) void __stdcall Rva0135918CCall(void);

class BfmeObjECF
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		long(__stdcall *slot08)(BfmeObjECF *);
		void *slot0c;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1c;
		long(__stdcall *slot20)(BfmeObjECF *);
	};

	Vtable *vtable;
};

extern BfmeObjECF *g_bfmeObjECF;
extern int g_bfmeObjECFFlag27C;

void __cdecl rva00958ba0(void)
{
	BfmeObjECF *obj = g_bfmeObjECF;
	if (!obj)
		return;

	BfmeObjECF::Vtable *vt = obj->vtable;
	long result = vt->slot20(obj);
	if (result < 0)
		_com_issue_errorex(result, (IUnknown *)obj, g_bfmeIidTSA);

	obj = g_bfmeObjECF;
	if (!obj)
		return;

	g_bfmeObjECF = 0;
	obj->vtable->slot08(obj);

	g_bfmeObjECFFlag27C = 0;
	Rva0135918CCall();
}

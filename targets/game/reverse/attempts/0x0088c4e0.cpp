// ?purecallHandler@@YAHXZ
// partial score=0.9 date=2026-09-06
extern "C" __declspec(dllimport) void* __stdcall GetModuleHandleA(const char*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
int purecallHandler();
class Debug { static void PostStaticInit(); friend int purecallHandler(); };
void _bfme_debugRecordCallsite(int);
struct Rva0088C4E0Reporter {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void message(const char*);
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void finish(int);
};
struct Rva0088C4E0Debugger {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void begin();
	virtual void s25(); virtual void s26();
	virtual Rva0088C4E0Reporter* report(int, int);
};
extern Rva0088C4E0Debugger* Rva0088C4E0TheDebugger;
int purecallHandler()
{
	void* module = GetModuleHandleA(0);
	if (!GetProcAddress(module, "?PostStaticInit@Debug@@CAXXZ"))
	{
		static int (* const fallback)() = (int (*)())&Debug::PostStaticInit;
		return fallback();
	}
	_bfme_debugRecordCallsite(1);
	Rva0088C4E0TheDebugger->begin();
	Rva0088C4E0Reporter* r = Rva0088C4E0TheDebugger->report(0, 0);
	r->message("Pure virtual function called.");
	r->finish(1);
	return 0;
}

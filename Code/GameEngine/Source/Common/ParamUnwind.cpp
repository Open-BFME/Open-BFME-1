// cl: /EHsc
//
// Anonymous MSVC 7.1 unwind bodies. Retail labels them Unwind@; no parent
// identity survives. The --show guard is the SkirmishScreenShowError shape
// that emits `mov ecx,[ebp+disp]; jmp dtor` for a const-ref copied by value.
// walk() is the EBP-less thiscall that puts that const-ref at [ebp+4].

struct Gen_uw_0000d828 {
	int m;
	Gen_uw_0000d828();
	Gen_uw_0000d828(const Gen_uw_0000d828 &);
	~Gen_uw_0000d828();
};

struct Gen_uw_00016de7 {
	int m;
	Gen_uw_00016de7();
	Gen_uw_00016de7(const Gen_uw_00016de7 &);
	~Gen_uw_00016de7();
};

struct Gen_uwm_00001f05 {
	int m;
	Gen_uwm_00001f05();
	Gen_uwm_00001f05(const Gen_uwm_00001f05 &);
	~Gen_uwm_00001f05();
};

extern void param_unwind_take_d828(Gen_uw_0000d828 a, Gen_uw_0000d828 b, void (*cb)());
extern void param_unwind_take_16de7(Gen_uw_00016de7 a, Gen_uw_00016de7 b, void (*cb)());
extern void param_unwind_take_1f05(Gen_uwm_00001f05 a, Gen_uwm_00001f05 b, void (*cb)());

class ParamUnwindHost
{
public:
	void p14(int a0, int a1, int a2, const Gen_uw_0000d828 &message, int show);
	void p1c(int a0, int a1, int a2, int a3, int a4, const Gen_uw_0000d828 &message, int show);
	void p44(
		int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13, int a14,
		const Gen_uwm_00001f05 &message, int show);
	Gen_uw_00016de7 *walk16(const Gen_uw_00016de7 &key);
	Gen_uwm_00001f05 *walk1f(const Gen_uwm_00001f05 &key);
	Gen_uw_00016de7 *root16;
	Gen_uwm_00001f05 *root1f;
};

// ?p14@ParamUnwindHost@@QAEXHHHABUGen_uw_0000d828@@H@Z absent-from-retail
void ParamUnwindHost::p14(int a0, int a1, int a2, const Gen_uw_0000d828 &message, int show)
{
	(void)a0;
	(void)a1;
	(void)a2;
	if (--show == 0)
		param_unwind_take_d828(Gen_uw_0000d828(), message, 0);
}

// ?p1c@ParamUnwindHost@@QAEXHHHHHABUGen_uw_0000d828@@H@Z absent-from-retail
void ParamUnwindHost::p1c(int a0, int a1, int a2, int a3, int a4, const Gen_uw_0000d828 &message, int show)
{
	(void)a0;
	(void)a1;
	(void)a2;
	(void)a3;
	(void)a4;
	if (--show == 0)
		param_unwind_take_d828(Gen_uw_0000d828(), message, 0);
}

// ?p44@ParamUnwindHost@@QAEXHHHHHHHHHHHHHHHABUGen_uwm_00001f05@@H@Z absent-from-retail
void ParamUnwindHost::p44(
	int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
	int a8, int a9, int a10, int a11, int a12, int a13, int a14,
	const Gen_uwm_00001f05 &message, int show)
{
	(void)a0; (void)a1; (void)a2; (void)a3; (void)a4;
	(void)a5; (void)a6; (void)a7; (void)a8; (void)a9;
	(void)a10; (void)a11; (void)a12; (void)a13; (void)a14;
	if (--show == 0)
		param_unwind_take_1f05(Gen_uwm_00001f05(), message, 0);
}

// ?walk16@ParamUnwindHost@@QAEPAUGen_uw_00016de7@@ABU2@@Z absent-from-retail
Gen_uw_00016de7 *ParamUnwindHost::walk16(const Gen_uw_00016de7 &key)
{
	Gen_uw_00016de7 *n = root16;
	while (n)
	{
		param_unwind_take_16de7(*n, key, 0);
		n = *(Gen_uw_00016de7 **)&n->m;
	}
	return n;
}

// ?walk1f@ParamUnwindHost@@QAEPAUGen_uwm_00001f05@@ABU2@@Z absent-from-retail
Gen_uwm_00001f05 *ParamUnwindHost::walk1f(const Gen_uwm_00001f05 &key)
{
	Gen_uwm_00001f05 *n = root1f;
	while (n)
	{
		param_unwind_take_1f05(*n, key, 0);
		n = *(Gen_uwm_00001f05 **)&n->m;
	}
	return n;
}

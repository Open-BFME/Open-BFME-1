// Open-BFME5 conversions.

extern "C" __declspec(dllimport) void __stdcall bfmeEnter1179(void *p);
extern "C" __declspec(dllimport) void __stdcall bfmeLeave1179(void *p);
extern "C" __declspec(dllimport) void __stdcall bfmeSignal1179(void *h);
extern "C" int __cdecl bfmeTid1179(void);

extern "C" volatile int g_bfmeOwner1179;
extern "C" volatile int g_bfmeCount1179;
extern "C" char g_bfmeCs1179[];
extern "C" void *volatile g_bfmeEv1179;

char bfmeUnlock1179(void)
{
	char r;

	if (bfmeTid1179() == g_bfmeOwner1179)
		(void)g_bfmeCount1179;

	bfmeEnter1179(g_bfmeCs1179);
	g_bfmeCount1179 = g_bfmeCount1179 - 1;
	r = (char)(g_bfmeCount1179 == 0);

	if (r)
		g_bfmeOwner1179 = 0;

	bfmeLeave1179(g_bfmeCs1179);
	bfmeSignal1179(g_bfmeEv1179);

	return r;
}

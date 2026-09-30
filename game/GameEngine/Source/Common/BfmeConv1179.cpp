// Open-BFME5 conversions.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *p);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *p);
extern "C" __declspec(dllimport) void __stdcall ReleaseMutex(void *h);
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

	EnterCriticalSection(g_bfmeCs1179);
	g_bfmeCount1179 = g_bfmeCount1179 - 1;
	r = (char)(g_bfmeCount1179 == 0);

	if (r)
		g_bfmeOwner1179 = 0;

	LeaveCriticalSection(g_bfmeCs1179);
	ReleaseMutex(g_bfmeEv1179);

	return r;
}

// Retail 0x00905B70: int3 before entry; ret at 0x00905C2A, then int3.
// No caller proves the semantic name. The debug strings witness the operation.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
extern int g_rva00F405E0;
extern unsigned long g_rva00F405D4;
extern int g_rva00ED6DC4;
extern int g_rva00F405E4;
extern int g_rva00F405DC;
extern const char *g_rva00F405D8;

char Rva00905B70(const char *file, int line)
{
    char buffer[260];
    char result = bfmeUnlock1179();
    if (result && g_rva00F405E0 == bfmeTid1179()) {
        g_rva00F405E4 = timeGetTime() - g_rva00F405D4;
        if (g_rva00F405E4 > g_rva00ED6DC4) {
            sprintf(buffer, "%s(%d): DX Aquired.  Thread(%08x) \n",
                g_rva00F405D8, g_rva00F405DC, g_rva00F405E0);
            OutputDebugStringA(buffer);
            sprintf(buffer, "%s(%d): DX Released. Thread(%08X) Time (%d). \n",
                file, line, bfmeTid1179(), g_rva00F405E4);
            OutputDebugStringA(buffer);
        }
    }
    return result;
}

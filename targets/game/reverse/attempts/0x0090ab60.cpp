// ?Init@DX8Wrapper@@SA_NPAX_N@Z
// partial score=0.92 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
#include <string.h>

typedef unsigned long DWORD;
typedef void *HANDLE;
typedef void *HMODULE;
typedef void *(__stdcall *D3DCreate)(unsigned);

extern "C" DWORD __stdcall GetCurrentThreadId();
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateMutexA(void *, int, const char *);
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *);
extern "C" __declspec(dllimport) void * __stdcall GetProcAddress(HMODULE, const char *);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(HANDLE);

void __cdecl W3DRadarResetLock();
char __cdecl bfmeUnlock1179();
void __cdecl d_009064f0();

class DX8Wrapper {
public:
    static bool Init(void *hwnd, bool lite);
    static void Invalidate_Cached_Render_States();
    static void Enumerate_Devices();
};

struct BfmeDebug {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
    virtual void slot70(); virtual void slot74();
    virtual void slot78(int, void (*)(), int);
};
extern BfmeDebug *TheBfmeAwakenDebug;
extern void *Rva0133F478InitTextures[8];
extern void *Rva01340508Window;
extern volatile int g_bfmeOwnerVHM;
extern volatile int g_bfmeDepthVHM;

#define G32(a) (*(unsigned *)(a))
#define G8(a) (*(unsigned char *)(a))
#define GV32(a) (*(volatile unsigned *)(a))

static __forceinline char Rva0090AB60UnlockInline()
{
    if (GetCurrentThreadId() == g_bfmeOwnerVHM)
        (void)g_bfmeDepthVHM;
    EnterCriticalSection((void *)0x0133F4E8);
    g_bfmeDepthVHM = g_bfmeDepthVHM - 1;
    char release = (char)(g_bfmeDepthVHM == 0);
    if (release)
        g_bfmeOwnerVHM = 0;
    LeaveCriticalSection((void *)0x0133F4E8);
    ReleaseMutex((HANDLE)G32(0x0133F540));
    return release;
}

bool DX8Wrapper::Init(void *hwnd, bool lite)
{
    TheBfmeAwakenDebug->slot78(100, d_009064f0, 0);

    memset(Rva0133F478InitTextures, 0, sizeof(Rva0133F478InitTextures));

    memset((void *)0x01340100, 0, 0x400);
    memset((void *)0x0133F9E0, 0, 0x400);
    memset((void *)0x01340600, 0, 0x600);
    memset((void *)0x01341150, 0, 0x80);
    memset((void *)0x01340EC0, 0, 0x270);
    Rva01340508Window = hwnd;
    G32(0x01340570) = GetCurrentThreadId();
    InitializeCriticalSection((void *)0x0133F4E8);
    G32(0x0133F540) = (unsigned)CreateMutexA(0, 0, 0);
    W3DRadarResetLock();

    memset((void *)0x0133F4A8, 0, 0x40);
    memset((void *)0x0133F548, 0, 0x40);
    G32(0x012D6DB0) = -1;
    G32(0x012D6DB4) = 640;
    G32(0x012D6DB8) = 480;
    G32(0x012D6DBC) = 32;
    G8(0x0134050D) = 0;
    G8(0x012D6DAC) = 0;
    G32(0x013400FC) = 0;
    memset((void *)0x0133F500, 0, 0x40);
    G32(0x01340530) = 0;
    G32(0x01340534) = 0;
    G32(0x0134054C) = 0;
    G32(0x01340550) = 0;
    G32(0x01340554) = 0;
    G32(0x01340558) = 0;
    G32(0x0134055C) = 0;
    G32(0x01340560) = 0;
    G32(0x01340564) = 0;
    G32(0x01340568) = 0;
    G32(0x0134056C) = 0;
    G32(0x01340594) = 0;
    G32(0x01340598) = 0;
    G32(0x0134059C) = 0;
    G32(0x013405A0) = 0;
    G32(0x013405A4) = 0;
    G32(0x013405A8) = 0;
    G32(0x013405AC) = 0;
    G32(0x013405B0) = 0;
    G32(0x013405B4) = 0;
    G32(0x013405B8) = 0;
    G32(0x013405BC) = 0;
    Invalidate_Cached_Render_States();

    if (!lite) {
        HMODULE library = LoadLibraryA("D3D9.DLL");
        G32(0x013405D0) = (unsigned)library;
        if (!library) {
            bfmeUnlock1179();
            return false;
        }
        D3DCreate create = (D3DCreate)GetProcAddress(library, "Direct3DCreate9");
        G32(0x013405CC) = (unsigned)create;
        if (!create) {
            return false;
        }
        void *interface9 = create(0x1f);
        G32(0x01340530) = (unsigned)interface9;
        if (!interface9) {
            bfmeUnlock1179();
            return false;
        }
        G8(0x0134050C) = 1;
        Enumerate_Devices();
    }

    Rva0090AB60UnlockInline();
    return true;
}

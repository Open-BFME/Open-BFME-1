// 045-drawprobe — INSTRUMENT. Which point in the frame can a mod draw 2D from,
// and does drawFillRect's colour argument mean what we think?
//
// Round 1 drew a coloured band from three moments and none appeared, so the
// moment is not the variable. Round 2 separates the two things round 1
// conflated:
//
//   * whether each hook FIRES at all -> a counter per hook in the log
//   * whether the colour is the reason nothing shows -> every rect is now
//     0xFFFFFFFF, which is opaque white under ARGB, RGBA, ABGR or BGRA alike
//
// INSTRUMENT: --dist refuses it, and it must never ship.

typedef float Real;
typedef unsigned long Color;
extern "C" const int _fltused = 0;

typedef void(__fastcall *FillRect)(void *self, void *edx, Real x, Real y, Real w, Real h, Color c);
struct FILE;
typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_sprintf (*(SPrintf *)0x0135948C)

#define TheDisplay (*(void **)0x012F1270)
enum { DISP_FILL_RECT = 0xC0, DISP_GET_WIDTH = 0x2C, DISP_GET_HEIGHT = 0x30 };
typedef int(__fastcall *GetDim)(void *self, void *edx);

static FILE *s_log;
static int s_opened;
static unsigned s_hits[3];

static void band(int which, Real y) {
    ++s_hits[which];
    void *disp = TheDisplay;
    if (disp != 0) {
        void **vt = *(void ***)disp;
        ((FillRect)vt[DISP_FILL_RECT / 4])(disp, 0, 60.0f, y, 300.0f, 40.0f, 0xFFFFFFFFul);
    }
    if ((s_hits[which] % 120) != 0) {
        return;
    }
    if (!s_opened) {
        s_opened = 1;
        char path[512];
        c_sprintf(path, "%s\\My Battle for Middle-earth Files\\Draw.jsonl", c_getenv("APPDATA"));
        s_log = c_fopen(path, "a");
    }
    if (s_log == 0) {
        return;
    }
    void **vt = (disp != 0) ? *(void ***)disp : 0;
    c_fprintf(s_log, "{\"a\":%u,\"b\":%u,\"c\":%u,\"disp\":%u,\"w\":%d,\"h\":%d}\n",
              s_hits[0], s_hits[1], s_hits[2], (unsigned)disp,
              vt ? ((GetDim)vt[DISP_GET_WIDTH / 4])(disp, 0) : -1,
              vt ? ((GetDim)vt[DISP_GET_HEIGHT / 4])(disp, 0) : -1);
    c_fflush(s_log);
}

extern "C" __declspec(dllexport) void __cdecl drawprobe_a(void *ecx) { (void)ecx; band(0, 60.0f); }
extern "C" __declspec(dllexport) void __cdecl drawprobe_b(void *ecx) { (void)ecx; band(1, 110.0f); }
extern "C" __declspec(dllexport) void __cdecl drawprobe_c(void *ecx) { (void)ecx; band(2, 160.0f); }

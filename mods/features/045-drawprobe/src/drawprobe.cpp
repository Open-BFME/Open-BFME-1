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
static unsigned s_hits[4];

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
    c_fprintf(s_log, "{\"a\":%u,\"b\":%u,\"c\":%u,\"d\":%u,\"disp\":%u,\"w\":%d,\"h\":%d}\n",
              s_hits[0], s_hits[1], s_hits[2], s_hits[3], (unsigned)disp,
              vt ? ((GetDim)vt[DISP_GET_WIDTH / 4])(disp, 0) : -1,
              vt ? ((GetDim)vt[DISP_GET_HEIGHT / 4])(disp, 0) : -1);
    c_fflush(s_log);
}

// The rects never reach the screen from any moment, on any display, in the shell
// or in a replay. So the question is no longer WHEN but WHAT: InGameUI::message
// proves DisplayString drawing does reach the screen, so try that instead.
typedef void *(__fastcall *NewString)(void *self, void *edx);
typedef void(__fastcall *SetText)(void *self, void *edx, void *unicode_string);
typedef void(__fastcall *SetFont)(void *self, void *edx, void *font);
typedef void(__fastcall *SetColor)(void *self, void *edx, Color color);
typedef void(__fastcall *DrawText)(void *self, void *edx, int x, int y);
typedef void *(__fastcall *GetFont)(void *self, void *edx, void *name, Real size, unsigned char bold);
typedef void(__fastcall *UnicodeCtor)(void *self, void *edx, const unsigned short *text);

#define c_unicode ((UnicodeCtor)0x00C88DE0)
#define c_getfont ((GetFont)0x0040ABC3)
#define TheStringManager (*(void **)0x012F12CC)
#define TheGlobalLanguage (*(void **)0x012F1484)
#define TheFontLibrary (*(void **)0x012F1B38)
enum { DSM_NEW = 0x24, DS_SET_TEXT = 0x04, DS_SET_FONT = 0x18,
       DS_SET_COLOR = 0x28, DS_DRAW = 0x44 };
enum { GLD_FONT_NAME = 0xDC, GLD_FONT_SIZE = 0xE0, GLD_FONT_BOLD = 0xE4 };

static void *s_ds;
static int s_tried;

static void say(int x, int y) {
    if (!s_tried) {
        s_tried = 1;
        unsigned char *gld = (unsigned char *)TheGlobalLanguage;
        void *lib = TheFontLibrary, *mgr = TheStringManager;
        if (gld == 0 || lib == 0 || mgr == 0) { return; }
        void *font = c_getfont(lib, 0, gld + GLD_FONT_NAME,
                               (Real)*(int *)(gld + GLD_FONT_SIZE),
                               *(gld + GLD_FONT_BOLD));
        void **mvt = *(void ***)mgr;
        s_ds = ((NewString)mvt[DSM_NEW / 4])(mgr, 0);
        if (s_ds != 0 && font != 0) {
            void **vt = *(void ***)s_ds;
            ((SetFont)vt[DS_SET_FONT / 4])(s_ds, 0, font);
        }
    }
    if (s_ds == 0) { return; }
    void **vt = *(void ***)s_ds;
    void *line = 0;
    c_unicode(&line, 0, (const unsigned short *)L"OPEN-BFME draw probe");
    ((SetText)vt[DS_SET_TEXT / 4])(s_ds, 0, line);
    ((SetColor)vt[DS_SET_COLOR / 4])(s_ds, 0, 0xFFFFFFFFul);
    ((DrawText)vt[DS_DRAW / 4])(s_ds, 0, x, y);
}

extern "C" __declspec(dllexport) void __cdecl drawprobe_a(void *ecx) { (void)ecx; band(0, 60.0f); say(60, 220); }
extern "C" __declspec(dllexport) void __cdecl drawprobe_b(void *ecx) { (void)ecx; band(1, 110.0f); }
extern "C" __declspec(dllexport) void __cdecl drawprobe_c(void *ecx) { (void)ecx; band(2, 160.0f); }

// D is the one hypothesis the earlier rounds never tried: postDraw's TAIL,
// at RVA 0x004476E2, two instructions before its ret. Every draw postDraw makes
// has already happened here. If the 2D batch is reset at the START of the pass,
// an entry hook feeds a batch that is then cleared and a tail hook does not.
extern "C" __declspec(dllexport) void __cdecl drawprobe_d(void *ecx) {
    (void)ecx;
    band(3, 210.0f);
    say(60, 262);
}

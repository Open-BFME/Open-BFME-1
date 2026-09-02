// 044-modpanel — the mod panel. One on-screen surface every later feature can
// put a row on, drawn with the engine's own primitives so it belongs to BFME
// rather than sitting on top of it.
//
// UNSHIPPED AND NOT WORKING YET. It opens and closes on its key, its rows are
// live, and every binding below is measured and verified at runtime -- and
// nothing it draws reaches the screen. README.md has the four hook points that
// were tried, the proof that the call itself is correct (getWidth/getHeight
// through this same vtable return 1680x1050), and what to try next. Do not
// spend another round on hook placement.
//
// Press SLASH in a game or a replay. The panel opens in the top-left, lists
// what the mods have added, and closes again on the same key.
//
// WHAT THIS IS FOR. 039 added a pause, 043 added three camera axes, and the
// only place any of it was written down was a README. Rather than each feature
// inventing its own way to say so, this owns one panel and a table of rows;
// adding a row is one line in ROWS below. A row is a label, a value, or both,
// and the value comes from a function so it can be live.
//
// EVERY ADDRESS HERE WAS MEASURED, NOT INFERRED. The lesson of the feature
// before this one: three ledger rows in this area are pinned onto the wrong
// bodies, and a vtable slot taken from a header's declaration order crashed
// twice. So each one below carries the site it was read off.
//
//   InGameUI::postDraw        RVA 0x004469F0   the hook; runs after the world
//   TheDisplay                VA  0x012F1270
//     vtable base             VA  0x0111EDD0   +0x2C getWidth agrees with
//                                              040-horplus, independently
//     +0xC0 drawFillRect(x, y, w, h, color)    call site RVA 0x004475AC
//     +0xBC drawOpenRect(x, y, w, h, lineWidth, color)
//   TheDisplayStringManager   VA  0x012F12CC   init site RVA 0x0042F656
//     +0x24 newDisplayString()                 call sites RVA 0x0040CFC0 ff
//     +0x28 freeDisplayString(ds)
//   DisplayString vtable      VA  0x0111FEA8   from the ctor at RVA 0x006F4E0C
//     +0x04 setText(UnicodeString)             call site RVA 0x0040D109
//     +0x18 setFont(GameFont *)                call site RVA 0x0040D0F2
//     +0x28 setTextColor(Color)
//     +0x44 draw(Int x, Int y)                 ret 8, so the colour is set
//                                              separately -- not ZH's 4-arg draw
//   TheFontLibrary            VA  0x012F1B38   call site RVA 0x0040D0E4
//     FontLibrary::getFont(AsciiString *, Real, Bool)  ILT RVA 0x0000ABC3
//   TheGlobalLanguageData     VA  0x012F1484
//     +0xDC AsciiString font name, +0xE0 Int size, +0xE4 Bool bold
//                                              read together at RVA 0x0040CFD4
//   UnicodeString(const WideChar *)  VA 0x00C88DE0
//
// No loader and no CRT: cave.py drops this into an appended section and jumps
// in from mid-function. Nothing here may need a static initializer, an
// exception, 64-bit arithmetic, or a float without the marker below.
// Fixed-base 0x400000 image, DllCharacteristics 0x0000, so absolute addressing
// is safe.

typedef int Int;
typedef float Real;
typedef unsigned long Color;

extern "C" const int _fltused = 0;

typedef short(__stdcall *GetAsyncKey)(int);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
// MSVC 7.1 rejects __thiscall in this project. These are the documented
// __fastcall spellings used by 040-horplus: this in ECX, unused EDX, then the
// stack arguments in order.
typedef void(__fastcall *UnicodeCtor)(void *self, void *edx, const unsigned short *text);
typedef void(__fastcall *UnicodeDtor)(void *self, void *edx);
typedef void *(__fastcall *NewString)(void *self, void *edx);
typedef void(__fastcall *FreeString)(void *self, void *edx, void *ds);
typedef void(__fastcall *SetText)(void *self, void *edx, void *unicode_string);
typedef void(__fastcall *SetFont)(void *self, void *edx, void *font);
typedef void(__fastcall *SetColor)(void *self, void *edx, Color color);
typedef void(__fastcall *DrawText)(void *self, void *edx, Int x, Int y);
typedef void *(__fastcall *GetFont)(void *self, void *edx, void *name, Real size, unsigned char bold);
typedef void(__fastcall *FillRect)(void *self, void *edx, Real x, Real y, Real w, Real h, Color color);
typedef void(__fastcall *OpenRect)(void *self, void *edx, Real x, Real y, Real w, Real h,
                                   Real line, Color color);
typedef Int(__fastcall *GetDim)(void *self, void *edx);

#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
#define c_sprintf (*(SPrintf *)0x0135948C)
#define c_unicode ((UnicodeCtor)0x00C88DE0)
#define c_unicode_free ((UnicodeDtor)0x00C881D0)
#define c_getfont ((GetFont)0x0040ABC3)

#define TheGameLogic (*(void **)0x012F0898)
#define TheDisplay (*(void **)0x012F1270)
#define TheStringManager (*(void **)0x012F12CC)
#define TheGlobalLanguage (*(void **)0x012F1484)
#define TheFontLibrary (*(void **)0x012F1B38)
#define TheTacticalView (*(void **)0x012F1600)

enum { GL_MODE = 0x10C, GL_FRAME = 0x3C };
enum { GAME_REPLAY = 3 };
enum { VIEW_ANGLE = 0x28, VIEW_PITCH = 0x2C, VIEW_HEIGHT = 0x40, VIEW_ZOOM_LIMITED = 0x44 };
enum { GLD_FONT_NAME = 0xDC, GLD_FONT_SIZE = 0xE0, GLD_FONT_BOLD = 0xE4 };

enum { DSM_NEW = 0x24, DSM_FREE = 0x28 };
enum { DS_SET_TEXT = 0x04, DS_SET_FONT = 0x18, DS_SET_COLOR = 0x28, DS_DRAW = 0x44 };
enum { DISP_GET_WIDTH = 0x2C, DISP_OPEN_RECT = 0xBC, DISP_FILL_RECT = 0xC0 };

// Slash: free bare in retail (ctrl+slash is TOGGLE_FAST_FORWARD_MODE, hence the
// guard on it), and the key every other game puts help on.
enum { VK_CTRL = 0x11, VK_SLASH = 0xBF };

// Colours as 0xAARRGGBB, the format drawFillRect's call sites push. Sampled to
// sit beside BFME's own parchment-and-gold interface rather than over it.
// ul-suffixed, not an enum: these do not fit in an int, and MSVC 7.1 builds
// this translation unit with warnings as errors.
#define PANEL_BACK 0xD2140F0Aul   /* near-black, mostly opaque -- text has to read */
#define PANEL_EDGE 0xFF8A6A2Eul   /* the dull gold of the in-game frames */
#define TEXT_HEAD  0xFFE8C97Aul   /* heading gold */
#define TEXT_LABEL 0xFFCFC3A8ul   /* parchment */
#define TEXT_VALUE 0xFFFFFFFFul

enum {
    PANEL_X = 24,
    PANEL_Y = 24,
    PANEL_W = 268,
    ROW_H = 15,
    PAD = 10,
    VALUE_X = 168        // where the right-hand column starts, panel-relative
};

// ---------------------------------------------------------------- rows -----
//
// A row is a heading, a key binding, or a live reading. `value` fills the
// right-hand column; a row with no value is a heading, and a row with a
// literal `text` and no value is a plain line.
//
// TO ADD A ROW: write a value function and put one entry in ROWS. That is the
// whole extension mechanism, deliberately -- each feature is linked as its own
// blob with no linker between them, so a registry that features called into
// would need a rendezvous address in the cave and could not be checked at
// build time. A table in one file can be.

enum RowKind { ROW_HEAD, ROW_TEXT, ROW_VALUE };

typedef void(*ValueFn)(char *out);

struct Row {
    RowKind kind;
    const unsigned short *label;
    const unsigned short *text;   // ROW_TEXT only
    ValueFn value;                // ROW_VALUE only
    int replay_only;
};

static unsigned char *view() { return (unsigned char *)TheTacticalView; }
static unsigned char *logic() { return (unsigned char *)TheGameLogic; }

static void v_height(char *out) {
    unsigned char *v = view();
    if (v == 0) { c_sprintf(out, "-"); return; }
    c_sprintf(out, "%.0f", *(Real *)(v + VIEW_HEIGHT));
}
static void v_angle(char *out) {
    unsigned char *v = view();
    if (v == 0) { c_sprintf(out, "-"); return; }
    // 57.29578 = degrees per radian; the fields are radians, as View::setPitch's
    // -0.6283185 floor (-36 degrees) shows.
    c_sprintf(out, "%.0f deg", *(Real *)(v + VIEW_ANGLE) * 57.29578f);
}
static void v_pitch(char *out) {
    unsigned char *v = view();
    if (v == 0) { c_sprintf(out, "-"); return; }
    c_sprintf(out, "%.0f deg", *(Real *)(v + VIEW_PITCH) * 57.29578f);
}
static void v_zoomcap(char *out) {
    unsigned char *v = view();
    if (v == 0) { c_sprintf(out, "-"); return; }
    c_sprintf(out, v[VIEW_ZOOM_LIMITED] ? "on" : "released");
}
static void v_frame(char *out) {
    unsigned char *g = logic();
    if (g == 0) { c_sprintf(out, "-"); return; }
    c_sprintf(out, "%d", *(int *)(g + GL_FRAME));
}

#define W(s) ((const unsigned short *)L##s)

static const Row ROWS[] = {
    { ROW_HEAD,  W("REPLAY CONTROLS"), 0, 0, 1 },
    { ROW_TEXT,  W("Pause / resume"),  W("Ctrl + ."),   0, 1 },
    { ROW_TEXT,  W("Rotate camera"),   W("[   ]"),      0, 1 },
    { ROW_TEXT,  W("Zoom in / out"),   W("PgUp / PgDn"), 0, 1 },
    { ROW_TEXT,  W("Tilt camera"),     W(",   ."),      0, 1 },
    { ROW_TEXT,  W("Reset camera"),    W("Numpad 5"),   0, 1 },
    { ROW_HEAD,  W("CAMERA"),          0, 0, 0 },
    { ROW_VALUE, W("Height"),          0, v_height,  0 },
    { ROW_VALUE, W("Rotation"),        0, v_angle,   0 },
    { ROW_VALUE, W("Tilt"),            0, v_pitch,   0 },
    { ROW_VALUE, W("Zoom cap"),        0, v_zoomcap, 1 },
    { ROW_HEAD,  W("ENGINE"),          0, 0, 0 },
    { ROW_VALUE, W("Logic frame"),     0, v_frame,   0 },
    { ROW_HEAD,  W("OPEN-BFME"),       0, 0, 0 },
    { ROW_TEXT,  W("Close this panel"), W("/"),       0, 0 }
};
enum { ROW_COUNT = sizeof(ROWS) / sizeof(ROWS[0]) };

// ---------------------------------------------------------------- text -----

static void *s_string;   // one DisplayString, reused for every line of every frame
static void *s_font;
static int s_font_tried;

static void *font() {
    if (s_font_tried) {
        return s_font;
    }
    s_font_tried = 1;
    unsigned char *gld = (unsigned char *)TheGlobalLanguage;
    void *lib = TheFontLibrary;
    if (gld == 0 || lib == 0) {
        return 0;
    }
    // The same three fields, from the same struct, that the engine reads at
    // RVA 0x0040CFD4 when it builds a display string of its own.
    s_font = c_getfont(lib, 0, gld + GLD_FONT_NAME,
                       (Real)*(int *)(gld + GLD_FONT_SIZE),
                       *(gld + GLD_FONT_BOLD));
    return s_font;
}

static void *string() {
    if (s_string == 0) {
        void *mgr = TheStringManager;
        void *f = font();
        if (mgr == 0 || f == 0) {
            return 0;
        }
        void **vt = *(void ***)mgr;
        s_string = ((NewString)vt[DSM_NEW / 4])(mgr, 0);
        if (s_string != 0) {
            void **svt = *(void ***)s_string;
            ((SetFont)svt[DS_SET_FONT / 4])(s_string, 0, f);
        }
    }
    return s_string;
}

static void text(int x, int y, const unsigned short *wide, Color color) {
    void *ds = string();
    if (ds == 0) {
        return;
    }
    void **vt = *(void ***)ds;
    // The by-value UnicodeString contract: built here, destroyed by setText.
    void *line = 0;
    c_unicode(&line, 0, wide);
    ((SetText)vt[DS_SET_TEXT / 4])(ds, 0, line);
    ((SetColor)vt[DS_SET_COLOR / 4])(ds, 0, color);
    ((DrawText)vt[DS_DRAW / 4])(ds, 0, x, y);
}

// sprintf is narrow and the engine's text is wide. Widening a run of ASCII is a
// byte-to-short copy, which is cheaper than finding a wide printf and correct
// for everything a value function can produce.
static void text_ascii(int x, int y, const char *s, Color color) {
    unsigned short wide[64];
    int i = 0;
    while (s[i] != 0 && i < 63) {
        wide[i] = (unsigned char)s[i];
        ++i;
    }
    wide[i] = 0;
    text(x, y, wide, color);
}

// --------------------------------------------------------------- panel -----

static int s_open;
static int s_key_down;

static int rows_shown(int replay) {
    int n = 0;
    for (int i = 0; i < ROW_COUNT; ++i) {
        if (!ROWS[i].replay_only || replay) {
            ++n;
        }
    }
    return n;
}

static void draw_panel(int replay) {
    void *disp = TheDisplay;
    if (disp == 0) {
        return;
    }
    void **vt = *(void ***)disp;
    const int height = PAD * 2 + rows_shown(replay) * ROW_H;

    ((FillRect)vt[DISP_FILL_RECT / 4])(disp, 0, (Real)PANEL_X, (Real)PANEL_Y,
                                       (Real)PANEL_W, (Real)height, PANEL_BACK);
    ((OpenRect)vt[DISP_OPEN_RECT / 4])(disp, 0, (Real)PANEL_X, (Real)PANEL_Y,
                                       (Real)PANEL_W, (Real)height, 1.0f, PANEL_EDGE);

    int y = PANEL_Y + PAD;
    for (int i = 0; i < ROW_COUNT; ++i) {
        const Row *r = &ROWS[i];
        if (r->replay_only && !replay) {
            continue;
        }
        if (r->kind == ROW_HEAD) {
            text(PANEL_X + PAD, y, r->label, TEXT_HEAD);
        } else {
            text(PANEL_X + PAD, y, r->label, TEXT_LABEL);
            if (r->kind == ROW_TEXT) {
                text(PANEL_X + VALUE_X, y, r->text, TEXT_VALUE);
            } else {
                char buf[64];
                buf[0] = 0;
                r->value(buf);
                text_ascii(PANEL_X + VALUE_X, y, buf, TEXT_VALUE);
            }
        }
        y += ROW_H;
    }
}

#ifdef PROBE
struct FILE;
typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
static FILE *s_log;
static int s_log_opened;
static unsigned s_ticks;
static void probe() {
    if (!s_log_opened) {
        s_log_opened = 1;
        char path[512];
        c_sprintf(path, "%s\\My Battle for Middle-earth Files\\Panel.jsonl", c_getenv("APPDATA"));
        s_log = c_fopen(path, "a");
    }
    if (s_log == 0) { return; }
    c_fprintf(s_log, "{\"t\":%u,\"open\":%d,\"disp\":%u,\"mgr\":%u,\"gld\":%u,"
                     "\"fontlib\":%u,\"font\":%u,\"fonttried\":%d,\"ds\":%u}\n",
              s_ticks, s_open, (unsigned)TheDisplay, (unsigned)TheStringManager,
              (unsigned)TheGlobalLanguage, (unsigned)TheFontLibrary,
              (unsigned)s_font, s_font_tried, (unsigned)s_string);
    c_fflush(s_log);
}
#endif

extern "C" __declspec(dllexport) void __cdecl modpanel_draw(void *ecx) {
    (void)ecx;
    unsigned char *gl = (unsigned char *)TheGameLogic;
    if (gl == 0) {
        return;
    }
    const int mode = *(int *)(gl + GL_MODE);
    const int replay = (mode == GAME_REPLAY);

    // Polled once per client frame, so a tap shorter than a frame is missed. A
    // human press is 2-4 frames.
    if (!(c_getasynckey(VK_CTRL) & 0x8000) && (c_getasynckey(VK_SLASH) & 0x8000)) {
        if (!s_key_down) {
            s_key_down = 1;
            s_open = !s_open;
        }
    } else {
        s_key_down = 0;
    }

    if (s_open) {
        draw_panel(replay);
    }
#ifdef PROBE
    if ((++s_ticks % 30) == 0) { probe(); }
#endif
}

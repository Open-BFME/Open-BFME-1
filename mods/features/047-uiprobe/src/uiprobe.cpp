// 047-uiprobe — INSTRUMENT. Open the Options screen and flip a mod-bus bit from
// the keyboard, because the test rig has no working mouse.
//
// 046-optionsui puts three Open-BFME settings on the real Options screen, and
// demonstrating it needs someone to click a checkbox. On this rig nobody can:
// wine's DirectInput wants a pointer grab, the grab breaks pointer motion on
// every headless compositor available here, and without the grab the game
// tracks the cursor (hover lights up) but never sees a button. The KEYBOARD
// works everywhere, so this drives the same code paths from keys instead.
//
//   F5   both halves of AptMainMenu::Options' own handler at RVA 0x0051D9B0:
//        the transition start at 0x0051D590 with the main-menu screen from
//        0x012F49B4, then the show at 0x0055E290 with its literal (0, 1)
//   F9   play a replay outright -- RecorderClass::playbackFile, which is what
//        ReplayMenuSystem's Load branch calls. No menus, no mouse.
//   F6   flip the bus's rotate bit, so the checkbox visibly follows it and the
//        screen is proved to be showing OUR state and not the game's
//
// WHAT IT PROVED, and what it did not. F5 opens the screen: the frame, the
// buttons, the AUDIO CONTROLS column and its widgets all come up, through the
// same two calls the OPTIONS button makes. The LEFT column stays blank -- an
// empty frame with the main menu showing through it. Its widgets exist (hovering
// where Scroll Speed sits pops that widget's tooltip), so this is the movie not
// drawing the panel, not the panel being absent, and 046 is not the cause: the
// screen looks identical with 046 left out of the build.
//
// So the relabelled checkboxes cannot be photographed this way. showOptions(1,1)
// and (1,0) do not open the screen at all, so the byte pair at 0x012F4AD0/D1 is
// not the switch. What the button flow does that this does not is still open.
//
// INSTRUMENT: --dist refuses it, and it must never ship.

typedef short(__stdcall *GetAsyncKey)(int);
typedef void(__cdecl *ShowOptions)(int a, int b);
// MSVC 7.1 rejects __thiscall here; this is the documented __fastcall spelling.
typedef void(__fastcall *StartTransition)(void *self, void *edx);
typedef void(__fastcall *AsciiCtor)(void *self, void *edx, const char *text);
typedef void(__fastcall *PlaybackFile)(void *self, void *edx, void *ascii_string);

#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
#define c_showoptions ((ShowOptions)0x0095E290)
// The FIRST of the button's two calls: it flags the main menu and hands the
// transition handler the fade. Skipping it leaves the Options screen half
// initialised -- the audio column populates and the left one stays blank.
#define c_menutransition ((StartTransition)0x0091D590)
#define TheMainMenuScreen (*(void **)0x012F49B4)

// The whole reason this instrument exists. ReplayMenuSystem (the .wnd handler
// the FunctionLexicon binds at 0x012A94EC) ends its Load branch by building an
// AsciiString of the file and calling this on TheRecorder -- so a key can put
// the game in a replay with no menus and no mouse, which is the only way to
// test anything that draws in-game on this rig.
#define c_ascii ((AsciiCtor)0x00C88BC0)
#define c_playback ((PlaybackFile)0x0049B150)
#define TheRecorder (*(void **)0x012ED62C)

// AsciiString is taken by value and destroyed by the callee, the same contract
// as InGameUI::message's format.
static void play_replay(const char *path) {
    void *rec = TheRecorder;
    if (rec == 0) {
        return;
    }
    void *name = 0;
    c_ascii(&name, 0, path);
    c_playback(rec, 0, name);
}

#define MOD_BUS ((volatile unsigned char *)0x01416000)
#define BUS_MAGIC 0x4D46424Ful
enum { BUS_ROTATE = 4, BUS_TILT = 5, BUS_ZOOM = 6 };

enum { VK_F5 = 0x74, VK_F6 = 0x75, VK_F7 = 0x76, VK_F8 = 0x77, VK_F9 = 0x78,
       VK_F10 = 0x79 };

static int s_f5, s_f6, s_f7, s_f8, s_f9, s_f10;

// F10 answers the one question a screenshot cannot. 048 places BFME's own
// hidden advanced-graphics pages on the Options screen and they DRAW, in the
// game's art -- but every box comes up empty, which is either "the widget never
// registered" or "the setting really is off". Those look identical in a
// screenshot and are completely different bugs.
//
// AptOptions::InitGadgets (RVA 0x005625C0) is not a lookup: it is the callback
// the APT runtime invokes per gadget as the gadget is created, and it
// string-compares the name and caches the pointer on the screen. So a non-null
// slot IS registration, measured rather than inferred. HealthBars is the
// control -- it is an authored widget that visibly loads, so a run where it is
// null means the dump itself is wrong.
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

#define TheOptionsScreen (*(void **)0x012F4AD4)

// From InitGadgets' own compare-and-store chain.
enum {
    OPT_STATE = 0x258,      // the chain only runs when this reads 4
    OPT_HEALTHBARS = 0x290, // authored and visibly loading: the control
    OPT_ANISO = 0x2BC, OPT_TERRAIN = 0x2C0, OPT_3DSHADOW = 0x2C4,
    OPT_2DSHADOW = 0x2C8, OPT_WATER = 0x2CC, OPT_PROPS = 0x2D0,
    OPT_ANIMS = 0x2D4, OPT_HEAT = 0x2D8, OPT_LOD = 0x2DC,
    OPT_TEXDETAIL = 0x2FC
};

static unsigned slot(unsigned char *screen, int at) {
    return *(unsigned *)(screen + at);
}

static void dump_slots() {
    unsigned char *screen = (unsigned char *)TheOptionsScreen;
    char path[512];
    c_sprintf(path, "%s\\My Battle for Middle-earth Files\\UiProbe.jsonl",
              c_getenv("APPDATA"));
    FILE *f = c_fopen(path, "a");
    if (f == 0) {
        return;
    }
    if (screen == 0) {
        c_fprintf(f, "{\"screen\":0}\n");
    } else {
        c_fprintf(f,
                  "{\"screen\":%u,\"state\":%u,\"healthbars\":%u,"
                  "\"aniso\":%u,\"terrain\":%u,\"shadow3d\":%u,\"shadow2d\":%u,"
                  "\"water\":%u,\"props\":%u,\"anims\":%u,\"heat\":%u,"
                  "\"lod\":%u,\"texdetail\":%u}\n",
                  (unsigned)screen, slot(screen, OPT_STATE),
                  slot(screen, OPT_HEALTHBARS), slot(screen, OPT_ANISO),
                  slot(screen, OPT_TERRAIN), slot(screen, OPT_3DSHADOW),
                  slot(screen, OPT_2DSHADOW), slot(screen, OPT_WATER),
                  slot(screen, OPT_PROPS), slot(screen, OPT_ANIMS),
                  slot(screen, OPT_HEAT), slot(screen, OPT_LOD),
                  slot(screen, OPT_TEXDETAIL));
    }
    c_fflush(f);
}

// showOptions stores its two arguments in the byte pair at 0x012F4AD0/D1 before
// naming Options.apt, so they select something about the screen. The real
// button passes (0, 1) and the left column still comes up blank on this path,
// so the other three combinations are worth one run.
static void open_options(int a, int b) {
    void *menu = TheMainMenuScreen;
    if (menu != 0) {
        c_menutransition(menu, 0);
    }
    c_showoptions(a, b);
}

static int down(int vk) {
    return (c_getasynckey(vk) & 0x8000) != 0;
}

extern "C" __declspec(dllexport) void __cdecl uiprobe_frame(void *ecx) {
    (void)ecx;

    if (down(VK_F5)) {
        if (!s_f5) {
            s_f5 = 1;
            open_options(0, 1);
        }
    } else {
        s_f5 = 0;
    }

    if (down(VK_F9)) {
        if (!s_f9) {
            s_f9 = 1;
            // A bare filename: playbackFile hands it to the opener at RVA
            // 0x00099490, and that is one of the four callers of getReplayDir,
            // so the directory is prepended for us.
            play_replay("downloaded.rep");
        }
    } else {
        s_f9 = 0;
    }

    if (down(VK_F7)) {
        if (!s_f7) { s_f7 = 1; open_options(1, 1); }
    } else {
        s_f7 = 0;
    }

    if (down(VK_F8)) {
        if (!s_f8) { s_f8 = 1; open_options(1, 0); }
    } else {
        s_f8 = 0;
    }

    if (down(VK_F10)) {
        if (!s_f10) { s_f10 = 1; dump_slots(); }
    } else {
        s_f10 = 0;
    }

    if (down(VK_F6)) {
        if (!s_f6) {
            s_f6 = 1;
            if (*(volatile unsigned long *)MOD_BUS != BUS_MAGIC) {
                MOD_BUS[BUS_ROTATE] = 1;
                MOD_BUS[BUS_TILT] = 1;
                MOD_BUS[BUS_ZOOM] = 1;
                *(volatile unsigned long *)MOD_BUS = BUS_MAGIC;
            }
            MOD_BUS[BUS_ROTATE] = (unsigned char)(MOD_BUS[BUS_ROTATE] ? 0 : 1);
        }
    } else {
        s_f6 = 0;
    }
}

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

#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
#define c_showoptions ((ShowOptions)0x0095E290)
// The FIRST of the button's two calls: it flags the main menu and hands the
// transition handler the fade. Skipping it leaves the Options screen half
// initialised -- the audio column populates and the left one stays blank.
#define c_menutransition ((StartTransition)0x0091D590)
#define TheMainMenuScreen (*(void **)0x012F49B4)

#define MOD_BUS ((volatile unsigned char *)0x01416000)
#define BUS_MAGIC 0x4D46424Ful
enum { BUS_ROTATE = 4, BUS_TILT = 5, BUS_ZOOM = 6 };

enum { VK_F5 = 0x74, VK_F6 = 0x75, VK_F7 = 0x76, VK_F8 = 0x77 };

static int s_f5, s_f6, s_f7, s_f8;

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

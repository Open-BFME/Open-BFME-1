// 046-optionsui — three Open-BFME settings, in BFME's own Options screen.
//
// Not a panel drawn over the game: the real APT Options screen, with the real
// widgets. The chrome, the font, the hover glow and the click sounds are the
// game's because the widgets ARE the game's -- Options.apt builds itself out of
// GameWindowGadgets/CheckBox and MenuExport/Button, so there is nothing for a
// mod to imitate.
//
// The label side is data: mods/features/046-optionsui/apt_labels.py renames
// three checkboxes inside Options.apt. This file is the behaviour.
//
//   Camera: rotate      was Show All Health Bars    screen+0x290
//   Camera: tilt        was Show Unit Decals        screen+0x29C
//   Camera: free zoom   was Alternate Mouse Setup   screen+0x294
//
// TAKING A WIDGET OVER MEANS TAKING ITS SIDE EFFECT TOO. A relabelled checkbox
// that still writes the game's own option would be exactly the silent surprise
// this project refuses: tick "Camera: tilt" and unit decals quietly turn off in
// Options.ini. So `Save` is hooked at its ENTRY -- before it reads a single
// widget -- and the three checkboxes are put back to the values the game had in
// them. The game then persists what it always would have, and the only place
// our three settings live is the mod bus.
//
// EVERY ADDRESS WAS MEASURED. The Options screen caches its widgets by name in
// AptOptions::InitGadgets (RVA 0x005625C0), which is where the three offsets
// above come from; the screen singleton and the two accessors come from
// AptOptions::Save (RVA 0x00560280), which reads a checkbox exactly this way.
//
//   BfmeAptScreenOptions            VA 0x012F4AD4   set in the ctor at 0x009634C3
//     vtable                        VA 0x0110912C
//     +0x14 update()                RVA 0x0055DC00  ticks while the screen is up
//   AptOptions::Save                RVA 0x00560280  bound in the ctor at 0x00963532
//   GadgetCheckBoxIsChecked(w)      RVA 0x004B3230  __cdecl -> bit 2 of status
//   GadgetCheckBoxSetChecked(w, b)  RVA 0x004B31D0  __cdecl, and it repaints
//
// No loader and no CRT: cave.py drops this into an appended section. Nothing
// here may need a static initializer, an exception, 64-bit arithmetic or a
// float. Fixed-base 0x400000 image, so absolute addressing is safe.

typedef unsigned char(__cdecl *IsChecked)(void *gadget);
typedef void(__cdecl *SetChecked)(void *gadget, int checked);

#define c_ischecked ((IsChecked)0x008B3230)
#define c_setchecked ((SetChecked)0x008B31D0)

#define TheOptionsScreen (*(void **)0x012F4AD4)

// The mod bus: the first 0x40 bytes of the cave, reserved by modbuild.py and
// never allocated to a payload. Features are linked one at a time with no
// linker between them, so an address is the only thing they can share. Layout
// is owned by docs/mods.md and only ever grows at the end.
#define MOD_BUS ((volatile unsigned char *)0x01416000)
#define BUS_MAGIC 0x4D46424Ful /* 'OBFM' */
enum { BUS_ROTATE = 4, BUS_TILT = 5, BUS_ZOOM = 6 };

// Where the screen caches each widget, from InitGadgets.
enum { W_ROTATE = 0x290, W_ZOOM = 0x294, W_TILT = 0x29C };

enum { COUNT = 3 };
static const int WIDGET[COUNT] = { W_ROTATE, W_TILT, W_ZOOM };
static const int BUSFIELD[COUNT] = { BUS_ROTATE, BUS_TILT, BUS_ZOOM };

static void *s_pushed;              // the screen our values are already in
static unsigned char s_saved[COUNT];  // what the game had in those widgets

static void *widget(unsigned char *screen, int at) {
    return *(void **)(screen + at);
}

static void publish_defaults() {
    if (*(volatile unsigned long *)MOD_BUS == BUS_MAGIC) {
        return;
    }
    // Nobody has claimed the bus yet, so this is the first run. All three
    // camera axes on, which is what a build without this screen behaves like --
    // a reader that finds no magic treats everything as enabled.
    MOD_BUS[BUS_ROTATE] = 1;
    MOD_BUS[BUS_TILT] = 1;
    MOD_BUS[BUS_ZOOM] = 1;
    *(volatile unsigned long *)MOD_BUS = BUS_MAGIC;
}

extern "C" __declspec(dllexport) void __cdecl optionsui_update(void *ecx) {
    unsigned char *screen = (unsigned char *)ecx;
    if (screen == 0) {
        return;
    }
    publish_defaults();

    if (s_pushed != ecx) {
        // First frame on this screen: remember what the game put in each widget
        // so Save can be given it back, then show our own state instead.
        s_pushed = ecx;
        for (int i = 0; i < COUNT; ++i) {
            void *w = widget(screen, WIDGET[i]);
            if (w != 0) {
                s_saved[i] = c_ischecked(w);
                c_setchecked(w, MOD_BUS[BUSFIELD[i]] != 0);
            }
        }
        return;
    }

    // Live, every frame: a tick takes effect at once rather than on Accept.
    // Accept and Cancel belong to the game's own rows, and pretending our three
    // obey them would mean holding a second copy of the truth.
    for (int i = 0; i < COUNT; ++i) {
        void *w = widget(screen, WIDGET[i]);
        if (w != 0) {
            MOD_BUS[BUSFIELD[i]] = c_ischecked(w);
        }
    }
}

extern "C" __declspec(dllexport) void __cdecl optionsui_save(void *ecx) {
    unsigned char *screen = (unsigned char *)ecx;
    if (screen == 0 || s_pushed != ecx) {
        return;
    }
    // Runs before Save reads anything. Hand the widgets back the values the
    // game had in them, so what reaches Options.ini is the game's own settings
    // and not ours wearing their names.
    for (int i = 0; i < COUNT; ++i) {
        void *w = widget(screen, WIDGET[i]);
        if (w != 0) {
            c_setchecked(w, s_saved[i]);
        }
    }
    s_pushed = 0;   // so the next open latches again
}

// 048-advancedgfx — open BFME's own Custom Graphics tab, which 2.22 builds and
// never shows.
//
// `Options.apt` carries a finished Advanced tab: eleven widgets, their labels,
// their tooltips and an animated open and close, at frames 102..121 behind the
// label `_open_advanced`. The engine side is finished too -- every one of the
// eleven has a slot on the screen object, a line in `AptOptions::Save`, and a
// line in the load path. Even the navigation exists. Nothing calls it.
//
//   AptOptions::showAdvanced   RVA 0x0055DBA0   __thiscall(screen)
//
// That one function does both halves: it calls `assignOpen("advanced")` on the
// movie through WindowManager::callFunction, and it sets the screen state to 4.
// BOTH MATTER. `AptOptions::InitGadgets` (RVA 0x005625C0) is not a lookup -- it
// is the callback the APT runtime invokes per gadget as the gadget is created,
// and its compare-and-store chain runs only when the state reads 4. Play the
// movie without the state and the tab draws with nothing bound to it.
//
// Measured, not assumed. With the screen open on the normal tab the eleven
// slots read 0 and the state reads 2; after this call the state reads 4 and all
// eleven hold pointers. With `HeatEffects = yes` in Options.ini and every other
// advanced setting off, Heat Effects came up as the one ticked box -- so
// registration, the load path and the render are all proved end to end.
//
// GOING BACK. `AptOptions::update` opens a tab only out of state 1, so dropping
// the state back to 1 hands the screen to the game's own code and it reopens the
// normal tab on its next frame. Nothing here duplicates that logic.
//
// No loader and no CRT: cave.py drops this into an appended section. Nothing
// here may need a static initializer, an exception, 64-bit arithmetic or a
// float. Fixed-base 0x400000 image, so absolute addressing is safe.

typedef short(__stdcall *GetAsyncKey)(int);
// MSVC 7.1 rejects __thiscall here; this is the documented __fastcall spelling.
typedef void(__fastcall *ShowAdvanced)(void *self, void *edx);

#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
#define c_showadvanced ((ShowAdvanced)0x0095DBA0)

// F11, while the Options screen is up. The screen's own three buttons are
// authored into the movie and cannot be added to without reserialising it, so
// the tab needs a key until there is a button for it.
enum { VK_F11 = 0x7A };

// AptOptions state, from the screen's own writes: 1 asks update() to open a tab,
// 2 is the normal tab, 3 the online one, 4 the advanced one.
enum { OPT_STATE = 0x258, ST_OPENING = 1, ST_NORMAL = 2, ST_ADVANCED = 4 };

static int s_held;

// The nav bar's fourth button, which apt_panel.py places. It is a fourth
// instance of the SAME character the other three are (146, in sprite 147), and
// APT dispatches a click by the placement's instance name -- so naming it
// RefreshNat, a command the screen's constructor already registers, is what
// brings the click here.
//
// The online tab's own Refresh NAT button carries that same command, so this
// RETURNS non-zero to swallow the call when it is ours and zero to let the real
// handler run when it is not. Without that, a click on our button would also
// kick a genuine NAT refresh -- not theoretical, it writes
// FirewallNeedToRefresh into Options.ini. modbuild asks for a swallowing shim
// by giving this hook a fourth element.
extern "C" __declspec(dllexport) int __cdecl advancedgfx_refreshnat(void *ecx) {
    unsigned char *screen = (unsigned char *)ecx;
    if (screen == 0) {
        return 0;
    }
    unsigned *state = (unsigned *)(screen + OPT_STATE);
    if (*state == ST_NORMAL) {
        c_showadvanced(screen, 0);
        return 1;
    }
    if (*state == ST_ADVANCED) {
        // Hand it back to update(), which opens the normal tab out of state 1.
        *state = ST_OPENING;
        return 1;
    }
    return 0;   // the online tab: this click belongs to the game's own button
}

static int down(int vk) {
    return (c_getasynckey(vk) & 0x8000) != 0;
}

extern "C" __declspec(dllexport) void __cdecl advancedgfx_update(void *ecx) {
    unsigned char *screen = (unsigned char *)ecx;
    if (screen == 0) {
        return;
    }
    if (!down(VK_F11)) {
        s_held = 0;
        return;
    }
    if (s_held) {
        return;
    }
    s_held = 1;

    unsigned *state = (unsigned *)(screen + OPT_STATE);
    if (*state == ST_NORMAL) {
        c_showadvanced(screen, 0);
    } else if (*state == ST_ADVANCED) {
        // Hand it back to update(), which opens the normal tab out of state 1.
        *state = ST_OPENING;
    }
}

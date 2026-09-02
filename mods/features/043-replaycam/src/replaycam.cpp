// 043-replaycam — give a replay the camera controls the engine already has.
//
// BFME1 ships a complete keyboard camera: InGameUI::update reads four flags
// every client frame and drives the tactical view from them, and GameData.ini
// even carries the tuning constant for it (KeyboardCameraRotateSpeed = 0.1).
// Nothing in retail ever sets those flags. CommandMap.ini binds no key to any
// of the eight MSG_META_*_CAMERA_* events, the eight one-line setters at RVA
// 0x0043A6F0..0x0043A760 have no callers anywhere in the image, and the only
// writes to the flags are the three that CLEAR them (constructor, reset,
// setInputEnabled). The feature is finished, tuned, and unreachable.
//
// So this does not implement a camera. It writes the four bytes the engine is
// already reading, and lets the engine's own code do the work:
//
//   InGameUI+0x12B4 rotate left    -> view->setAngle(getAngle() - speed)
//   InGameUI+0x12B5 rotate right   -> view->setAngle(getAngle() + speed)
//   InGameUI+0x12B6 zoom in        -> view->zoomIn()   (height *= 0.96, -1.0)
//   InGameUI+0x12B7 zoom out       -> view->zoomOut()  (height *= 1.05, +1.0)
//
// THE HOOK is InGameUI::update itself, at its entry, so the flags are set and
// consumed inside one call. Nothing else can clear them in between -- which
// matters, because setInputEnabled clears all four and a replay is exactly the
// place the engine likes to disable input. Held keys, not toggles: the engine
// reads these as level, once per frame, and clears nothing itself.
//
// Addresses claimed by other features, so nobody re-derives this:
//   0x0006B910                                      039-replayctl
//   0x0072FEB0                                      042-tracksfix
//   0x0006BAE0, 0x0006BC2B                          030-netlatprobe
//   0x0006E910, 0x0006E986, 0x0006E9D9, 0x00909039  036/037/038 (FPS work)
// cave.py makes a second claim a hard build error, not a merge conflict.
//
// Replay-only, and it holds no state that can outlive one: the flags are
// written from scratch every frame, and the one field it does latch (the zoom
// cap) is restored to the value it was found with on the way out.
//
// No loader and no CRT: cave.py drops this into an appended section and jumps
// in from mid-function. Nothing here may need a static initializer, an
// exception, 64-bit arithmetic, or a float without the marker below --
// modbuild.py fails the build on the resulting unresolved external. Fixed-base
// 0x400000 image, DllCharacteristics 0x0000, so absolute addressing is safe.

typedef float Real;

// MSVC 7.1 emits this marker for the pitch arithmetic. modbuild.py accepts this
// one self-defined marker; every other unresolved external stays fatal.
extern "C" const int _fltused = 0;

typedef short(__stdcall *GetAsyncKey)(int);
// MSVC 7.1 rejects __thiscall here. This is the documented __fastcall
// spelling used by 040-horplus: this in ECX, unused EDX, then stack args.
typedef void(__fastcall *SetPitch)(void *self, void *edx, Real pitch);
typedef void(__fastcall *UnicodeCtor)(void *self, void *edx, const unsigned short *text);
// InGameUI::message is a VARIADIC member, so MSVC gives it __cdecl with `this`
// as the first stack argument -- which is exactly how the engine calls it at
// ConnectionManager::disconnectPlayer RVA 0x006663C3.
typedef void(__cdecl *UiMessage)(void *self, void *unicode_string);
typedef Real(__fastcall *GetBound)(void *self, void *edx);
typedef void(__fastcall *SetHeight)(void *self, void *edx, Real height);

#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
// W3DView::setPitch, reverse/functions.csv RVA 0x00742D50. Preferred over
// writing m_pitchAngle: it clamps to the engine's own -36 degree floor, drops
// the five in-progress camera-movement flags, and rebuilds the camera
// transform. Poking the field does none of that and fights the next update.
#define c_setpitch ((SetPitch)0x00B42D50)
// UnicodeString::UnicodeString(const WideChar *) -- the GameEngine one, in the
// same string TU as AsciiString's literal ctor at 0x00C88BC0, NOT the WWLib
// class of the same mangled name that reverse/functions.csv pins at RVA
// 0x00065410. message takes its format BY VALUE and destroys it on the way out
// (`call 0x00C881D0` on the parameter slot), so the string has to be a real
// refcounted one; handing it a static body would hand the destructor a static
// body to free.
#define c_unicode ((UnicodeCtor)0x00C88DE0)

#define TheGameLogic (*(void **)0x012F0898)
#define TheTacticalView (*(void **)0x012F1600)
#define TheGlobalData (*(void **)0x012ED5C8)

enum { GL_MODE = 0x10C };
enum { GAME_REPLAY = 3 };

// InGameUI's per-frame camera request flags, read by InGameUI::update at RVA
// 0x004413C5 (rotate) and 0x00441427 (zoom).
// InGameUI vtable +0x40: message(UnicodeString format, ...), which goes
// straight to _vsnwprintf(buf, 0x1fff, format, args). Its format IS a format --
// a stray % in the card text would be read as a conversion.
//
// The vtable base is 0x010F5B38, read off the store the constructor makes at
// RVA 0x0044B834, not inferred from where `update` sits. Three overloads live
// next to each other and only their frames tell them apart; the first cut
// picked the wrong one and crashed on a garbage format:
//
//   +0x38  frame 0x4014, format at [esp+0x4020] = arg3  messageColor(color, fmt, ...)
//   +0x3C  frame 0x4018, format at [esp+0x4020] = arg2  message(AsciiString, ...)
//          -- and it alone reads TheGameText (0x012F147C) to resolve the label
//   +0x40  frame 0x4014, format at [esp+0x401C] = arg2  message(UnicodeString, ...)
enum { UI_VT_MESSAGE = 0x40 };

enum {
    UI_ROTATE_LEFT = 0x12B4,
    UI_ROTATE_RIGHT = 0x12B5,
    UI_ZOOM_IN = 0x12B6,
    UI_ZOOM_OUT = 0x12B7
};

// View, confirmed against the pinned accessors: setHeightAboveGround writes
// +0x44, setZoomLimited writes +0x48, setFieldOfView writes +0x6C, getAngle
// reads +0x28 and getPitch reads +0x2C.
enum { VIEW_PITCH = 0x2C, VIEW_HEIGHT = 0x40, VIEW_ZOOM_LIMITED = 0x44 };
// The height clamp W3DView::setHeightAboveGround applies is not a pair of
// fields: it is an object embedded at View+0x24B8 whose first two vtable slots
// return the floor and the ceiling. Asking it means the limits stay whatever
// the map and the engine decided, instead of this file inventing a number.
enum { VIEW_LIMITER = 0x24B8 };
// View vtable slot for setHeightAboveGround, read off the same table that
// InGameUI::update calls +0x130/+0x134 (zoomIn/zoomOut) through.
enum { VT_SET_HEIGHT = 0x12C };
// How much further out than a player a replay may go, and by the same token how
// much further the far plane has to reach. The engine's own ceiling is the unit
// -- measured at 600 on Fords of Isen -- so this is "twice as far", not a
// distance, and it follows whatever the map set.
//
// Removing the clamp instead of widening it is not an option: zoomOut is
// geometric (h = h * 1.05 + 1.0, once per frame), and six seconds of an
// unclamped key took the camera from 600 to 48,653,620.
//
// Two rather than three because three is past what the renderer looks good at.
// At 3x the map itself runs out -- terrain covered 45% of the frame, the rest
// off-map void -- and the terrain skirt shows through as a flat wedge. At 2x
// the frame is still whole.
enum { REPLAY_ZOOM_OUT_X = 2 };

// GlobalData::m_keyboardCameraRotateSpeed, the constant InGameUI::update
// already fsubs/fadds for rotate. Reused for pitch so the two axes share one
// tuning knob instead of this file inventing a second.
enum { GD_ROTATE_SPEED = 0xCC8 };
// GlobalData's camera clip-depth multiplier -- the thing the
// SET_CAMERA_CLIP_DEPTH_MULTIPLIER script action writes, and the only input to
// the far plane: W3DView::setCameraTransform computes
// Set_Clip_Planes(10.0, TheGlobalData[+0xA28] * 1800.0). It has to move WITH
// the height ceiling or lifting the ceiling buys nothing: measured on Fords of
// Isen at the retail multiplier, terrain is whole to 715, two thirds gone by
// 831, and the screen is black by 1121 -- all of it clipping, not culling.
enum { GD_CLIP_DEPTH = 0xA28 };

// [ ] rotate, PageUp/PageDown zoom, , . pitch, / the card. All of them are
// unbound in retail:
// CommandMap.ini claims none of them, and the bare comma and period are only
// ever bound by commandmapdebug.ini, which a retail build does not load.
enum {
    VK_CTRL = 0x11,
    VK_SLASH = 0xBF,
    VK_PRIOR = 0x21,
    VK_NEXT = 0x22,
    VK_COMMA = 0xBC,
    VK_PERIOD = 0xBE,
    VK_LBRACKET = 0xDB,
    VK_RBRACKET = 0xDD
};

// The mod bus: the first 0x40 bytes of the cave, reserved by modbuild.py, and
// the only way a separately-linked feature can talk to this one. 046-optionsui
// writes these three from the Options screen.
//
// The MAGIC is the gate, not the byte. A build without 046 leaves the bus
// zeroed, and zero must not read as "every camera axis off" -- so an unclaimed
// bus means everything is enabled, which is exactly how this feature behaved
// before the bus existed.
#define MOD_BUS ((volatile unsigned char *)0x01416000)
#define BUS_MAGIC 0x4D46424Ful /* 'OBFM' */
enum { BUS_ROTATE = 4, BUS_TILT = 5, BUS_ZOOM = 6 };

static int bus_on(int field) {
    if (*(volatile unsigned long *)MOD_BUS != BUS_MAGIC) {
        return 1;
    }
    return MOD_BUS[field] != 0;
}

static int s_in_replay;
static unsigned char s_saved_zoom_cap;
static Real s_saved_clip_depth;
static int s_card_delay;
static int s_card_key_down;

// The card. Shown once a replay has settled and again on F10, through the
// engine's own message feed -- the surface BFME already uses to tell a player
// something, so it gets the game's font, colour and fade for free and cannot
// disturb the renderer.
//
// Short lines on purpose. The feed is RIGHT-aligned to the viewport edge and
// does not wrap, so a padded two-column layout stretches each line across the
// whole screen and over the battle. Six lines on purpose too: the feed shows
// about that many before the oldest scrolls off, and a seventh cost the header.
static const unsigned short *const CARD[] = {
    (const unsigned short *)L"Replay: Ctrl+. pause",
    (const unsigned short *)L"[ ] rotate camera",
    (const unsigned short *)L"PgUp/PgDn zoom",
    (const unsigned short *)L", . tilt camera",
    (const unsigned short *)L"Numpad5 reset camera",
    (const unsigned short *)L"/ shows controls"
};
enum { CARD_LINES = sizeof(CARD) / sizeof(CARD[0]) };
// Client frames to wait before the card appears. The message feed is not up on
// the replay's first frame, and a line posted into it then is dropped.
enum { CARD_DELAY_FRAMES = 90 };

static void show_card(void *ui) {
    void **vt = *(void ***)ui;
    UiMessage message = (UiMessage)vt[UI_VT_MESSAGE / 4];
    for (int i = 0; i < CARD_LINES; ++i) {
        // One dword, constructed by the engine and destroyed by the callee:
        // the ordinary contract for a by-value string argument.
        void *line = 0;
        c_unicode(&line, 0, CARD[i]);
        message(ui, line);
    }
}

static int down(int vk) {
    return (c_getasynckey(vk) & 0x8000) != 0;
}

#ifdef PROBE
// -DPROBE only. Reals go out as raw IEEE bits: printing them would promote
// float to double in the varargs and casting them to int would pull in the
// CRT's __ftol, and there is no CRT here. decode offline.
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
static FILE *s_file;
static int s_opened;
static char s_path[512];
static unsigned s_ticks;
static unsigned bits(unsigned char *base, int off) { return *(unsigned *)(base + off); }
static void trace(unsigned char *ui, unsigned char *view) {
    if (s_opened == 0) {
        s_opened = 1;
        c_sprintf(s_path, "%s\\My Battle for Middle-earth Files\\Cam.jsonl", c_getenv("APPDATA"));
        s_file = c_fopen(s_path, "a");
    }
    if (s_file == 0) { return; }
    c_fprintf(s_file,
              "{\"t\":%u,\"in\":%d,\"out\":%d,\"L\":%d,\"R\":%d,"
              "\"angle\":%u,\"pitch\":%u,\"h\":%u,\"lim\":%d,\"b48\":%d,"
              "\"uiIn\":%d,\"uiOut\":%d,\"g2354\":%u,\"g1dc\":%d,\"g204\":%d,"
              "\"g228\":%d,\"g27c\":%d,\"g27d\":%d,\"clientBC\":%d}\n",
              s_ticks, down(VK_PRIOR), down(VK_NEXT), down(VK_LBRACKET), down(VK_RBRACKET),
              bits(view, 0x28), bits(view, 0x2C), bits(view, 0x40),
              (int)view[0x44], (int)view[0x48],
              (int)ui[UI_ZOOM_IN], (int)ui[UI_ZOOM_OUT], bits(view, 0x2354),
              (int)view[0x1DC], (int)view[0x204], (int)view[0x228],
              (int)view[0x27C], (int)view[0x27D],
              (int)(*(unsigned char **)0x012F1464)[0xBC]);
    c_fflush(s_file);
}
#endif

extern "C" __declspec(dllexport) void __cdecl replaycam_update(void *ecx) {
    unsigned char *ui = (unsigned char *)ecx;
    unsigned char *gl = (unsigned char *)TheGameLogic;
    unsigned char *view = (unsigned char *)TheTacticalView;
    unsigned char *gd = (unsigned char *)TheGlobalData;
    const int replay = (gl != 0) && (*(int *)(gl + GL_MODE) == GAME_REPLAY);

    if (replay != s_in_replay) {
        s_in_replay = replay;
        // Latch both on the way in and put back exactly what was there on the
        // way out, rather than assuming retail's values for them. The clip
        // depth especially: a map's script can set it, and restoring a guess
        // would quietly override that map for the rest of the session.
        if (view != 0) {
            if (replay) {
                s_saved_zoom_cap = view[VIEW_ZOOM_LIMITED];
            } else {
                view[VIEW_ZOOM_LIMITED] = s_saved_zoom_cap;
            }
        }
        if (gd != 0) {
            Real *clip = (Real *)(gd + GD_CLIP_DEPTH);
            if (replay) {
                s_saved_clip_depth = *clip;
                *clip = s_saved_clip_depth * REPLAY_ZOOM_OUT_X;
            } else {
                *clip = s_saved_clip_depth;
            }
        }
    }

    if (!replay || ui == 0 || view == 0) {
        s_card_delay = 0;
        return;
    }

    // A replay has no build radius and no unit to keep on screen, so the height
    // clamp that keeps a player at a playable scale only gets in the way.
    // W3DView::setHeightAboveGround consults this byte and skips its whole
    // clamp block when it is zero. Off the switch, the engine's own cap stands
    // and the clamp below never fires, so the camera behaves like retail.
    const int freezoom = bus_on(BUS_ZOOM);
    if (freezoom) {
        view[VIEW_ZOOM_LIMITED] = 0;
    }

    // Which puts the clamp here instead, against the same numbers the engine
    // would have used. The engine clamps inside its own store, so this sees a
    // value at most one 5% step past the ceiling and pulls it back through the
    // engine's setter -- never by poking the field, which would skip the camera
    // transform that goes with it.
    if (freezoom) {
        unsigned char *limiter = view + VIEW_LIMITER;
        void **limvt = *(void ***)limiter;
        const Real floor = ((GetBound)limvt[0])(limiter, 0);
        const Real ceiling = ((GetBound)limvt[1])(limiter, 0) * REPLAY_ZOOM_OUT_X;
        const Real height = *(Real *)(view + VIEW_HEIGHT);
        if (height > ceiling || height < floor) {
            void **viewvt = *(void ***)view;
            ((SetHeight)viewvt[VT_SET_HEIGHT / 4])(view, 0,
                                                   height > ceiling ? ceiling : floor);
        }
    }

    const int ctrl = down(VK_CTRL);

    if (s_card_delay <= CARD_DELAY_FRAMES && ++s_card_delay == CARD_DELAY_FRAMES) {
        show_card(ui);
    }
    // Slash because it is the help key everything else uses, and because it is
    // free bare in retail -- ctrl+slash is TOGGLE_FAST_FORWARD_MODE, hence the
    // guard. Like every key here this is polled once per client frame, so a tap
    // shorter than a frame is missed; a human press is 2-4 frames, an
    // `xdotool key` tap is not, and mistaking the second for a broken key cost
    // a build.
    if (!ctrl && down(VK_SLASH)) {
        if (!s_card_key_down) {
            s_card_key_down = 1;
            show_card(ui);
        }
    } else {
        s_card_key_down = 0;
    }

    ui[UI_ROTATE_LEFT] = (unsigned char)down(VK_LBRACKET);
    ui[UI_ROTATE_RIGHT] = (unsigned char)down(VK_RBRACKET);
    ui[UI_ZOOM_IN] = (unsigned char)down(VK_PRIOR);
    ui[UI_ZOOM_OUT] = (unsigned char)down(VK_NEXT);

    // ctrl+period is 039-replayctl's pause. Requiring ctrl to be up keeps
    // pausing from tilting the camera on the way through.
#ifdef PROBE
    if ((++s_ticks % 10) == 0) { trace(ui, view); }
#endif

    if (!ctrl && gd != 0 && bus_on(BUS_TILT)) {
        const Real step = *(Real *)(gd + GD_ROTATE_SPEED);
        const Real pitch = *(Real *)(view + VIEW_PITCH);
        if (down(VK_COMMA)) {
            c_setpitch(view, 0, pitch - step);
        } else if (down(VK_PERIOD)) {
            c_setpitch(view, 0, pitch + step);
        }
    }
}

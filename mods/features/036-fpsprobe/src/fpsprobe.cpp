// 036-fpsprobe -- did the SCREEN change, or only the loop?
//
// The question this exists to answer is the one the fps60 spike can most
// easily fake. A render loop can be made to iterate at 60 Hz while every
// second frame presents the identical image: the extra draw fired but
// interpolated nothing, or re-used a cached skeletal pose. Loop cadence, frame
// counters and even Present call counts all pass that build. Only the pixels
// it put on the screen do not.
//
// So this hashes the backbuffer, at the one instruction where the frame is
// finished and not yet shown: DX8Wrapper::End_Scene, after EndScene() and
// after the `flip` test, immediately before Present. RVA 0x00909039 is exactly
// `mov eax,[TheD3DDevice]`, five bytes, one whole instruction, no relative
// operand -- the cleanest detour site in the render path.
//
// It hashes a GRID rather than three chosen rectangles. Which part of the
// screen holds a moving unit depends on the scripted scene, the camera and the
// resolution, and a probe that has to be rebuilt when the scene moves is a
// probe that will be run against a stale region. 48 tiles are emitted per
// sampled frame and the READER decides which ones are unit, animation and UI
// -- offline, from the data, revisable without touching the binary. The tiles
// that never change in retail ARE the UI; that is a finding, not an assumption.
//
// BURST SAMPLED, ON A WALL CLOCK. A readback stalls the pipeline, so sampling
// every frame would heat what it measures -- and heat it ASYMMETRICALLY, since
// one arm presents twice as often. Eight consecutive presents every two
// seconds is the same absolute cost per second in both arms, while consecutive
// frames within a burst are what the duplicate-pair metric needs.
//
// No CRT and no loader here: see modbuild.py's undefined-externals check.
// Addresses are absolute; fixed-base 0x400000 image, DllCharacteristics 0.

// ---- the game's own CRT, through its import table -------------------------
struct FILE;
typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
typedef int(__stdcall *QueryCounter)(unsigned *);

#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_sprintf (*(SPrintf *)0x0135948C)
#define c_qpc (*(QueryCounter *)0x01358EB4)
#define c_qpf (*(QueryCounter *)0x01358EB8)

// The engine's own millisecond clock -- the same one GameEngine::execute's
// frame limiter compares against, so a burst schedule built on it shares a
// time base with the thing being measured. __stdcall, no arguments, ms in eax.
typedef unsigned(__stdcall *TimeGetTime)(void);
#define c_time ((TimeGetTime)0x00505750)

// ---- the engine's globals -------------------------------------------------
// DX8Wrapper's device pointer, proven by the two vtable slots the retail code
// calls through it: +0xA8 in End_Scene and +0x44 here, which are EndScene and
// Present in IDirect3DDevice9 and in no other interface this image uses.
#define TheD3DDevice (*(void **)0x01340534)

// ---- the engine's own headroom, straight off GameEngine::execute ----------
// The frame limiter writes both of these every iteration, on both of its
// paths: FRAME_WORK is how long the iteration's work took, FRAME_IDLE how much
// of the frame budget was left over. Together they are how close this machine
// is to not keeping up -- which is the question a weaker computer poses, and
// one no frame RATE can answer, because a machine that has run out of headroom
// still reports whatever rate it is managing.
//
// FRAME_IDLE alone is ambiguous: the no-limit path at RVA 0x0006BEC2 stores a
// literal 0 into it, so zero means EITHER "the work filled the budget" OR "the
// limiter did not run this iteration". FRAME_LIMITED is the flag that decides
// which, so it rides every line beside them.
#define FRAME_WORK (*(unsigned *)0x012ED514)
#define FRAME_IDLE (*(unsigned *)0x012ED510)
#define FRAME_LIMITED (*(unsigned char *)0x012ED520)

// ---- the animation clock -------------------------------------------------
// WW3D::SyncTime, the clock every W3D animation plays against. Set by
// WW3D::Sync (RVA 0x008FD310: `[0x133F424] = [0x133F420]; [0x133F420] = arg`),
// and the value handed to it is an accumulator advanced by a HARDCODED 33 ms
// per client frame -- 1000/30 -- with no reference to real time anywhere on
// the path (RVA 0x006F40E8, `add eax,[0x12BB1CC]`, and 0x12BB1CC holds 33).
//
// So animation speed is proportional to the CLIENT FRAME RATE, and any change
// that raises the frame rate speeds every animation up with it. Nothing else
// this probe records would show that: a torch flickering twice as fast still
// changes on the same fraction of presented frames, so the cell hashes, the
// duplicate rate and the new-images rate are all blind to it.
//
// Emitted raw so the reader can take its slope against the wall clock. That
// slope is animation milliseconds per real millisecond: 1.0 would be real
// time, and retail should already be well above it, because patch 1.03 raised
// FramesPerSecondLimit to 38 and left this constant at 30 fps.
#define TheAnimationClock (*(unsigned *)0x0133F420)
#define TheGameLogic (*(void **)0x012F0898)
#define TheGameClient (*(void **)0x012F1464)
#define TheNetwork (*(void **)0x012F7714)

enum {
    GL_FRAME = 0x3C,
    // Non-zero once this machine has seen a desync. The correctness gate: a
    // build that renders beautifully and disagrees with its peer about the
    // world is not a candidate, and the obvious observables are the wrong
    // shape -- the router's overrun counter zeroes itself every clean quantum.
    GL_DESYNC = 0x6C,
    // The sub-step GameLogic::update was last called with. GameEngine::update
    // cycles it 2,3,4,5,6,1 and calls the logic on every one, which is what
    // makes the simulation run at six steps per network frame rather than one.
    // Stored by GameLogic::update itself (`mov [ebp+0x168],edi` at RVA
    // 0x0038DB5A, ebp being its `this`), so it is the engine's own record of
    // the cycle rather than a count kept here -- and it is how a build that
    // claims to have doubled the cycle is made to prove it.
    GL_PHASE = 0x168,
    NET_STATUS = 0x0C,
    // ClientFrameSubsystem::getFrame, vtable slot 26. Called rather than read
    // off a guessed offset: GameEngine::execute reaches the render clock
    // through exactly this slot (`call [edx+0x68]` at RVA 0x0006BE96) to decide
    // whether to run the frame limiter, so it is the engine's own answer and
    // not a field that merely looks like it. MSVC 7.1 has no __thiscall on a
    // free function; __fastcall is the same call with an ignored edx.
    CLIENT_GETFRAME = 0x68
};

typedef int(__fastcall *GetFrame)(void *self, void *edx);

// ---- the simulation's own state CRC ---------------------------------------
// GameLogic::getCRC, reached through its thunk at VA 0x0040B532 exactly as the
// engine reaches it: BFMEDesyncCheck's constructor (RVA 0x000652C0) loads
// TheGameLogic into ecx, pushes a single zero, calls this, and keeps the
// result. That is the number two peers compare to decide they have desynced,
// so it is the sharpest available summary of simulation state.
//
// It exists here to answer one question that no frame-rate metric can: whether
// changing the sub-step count changes what the SIMULATION does, or only how
// often the client draws between simulation steps. Same map, same absence of
// input, two builds -- if the CRC sequences agree frame for frame, the
// sub-step count does not reach the simulation.
//
// Called once per logic frame, which is less often than the engine calls it
// when its own desync reporting is enabled (once per client frame), so the
// cost is bounded by something retail already does.
typedef unsigned(__fastcall *GetCRC)(void *self, void *edx, int mode);
#define c_getcrc ((GetCRC)0x0040B532)

enum {
    GL_GAMEMODE = 0x10C   // the ctor skips modes 4 and 8; mirrored below
};

// ---- IDirect3DDevice9 / IDirect3DSurface9, as vtable offsets --------------
// Only the six entry points this needs. Every one is __stdcall and returns an
// HRESULT in eax; `this` is the first stack argument, not ecx, because COM on
// win32 is stdcall-with-this-pushed.
typedef long(__stdcall *DevGetBackBuffer)(void *, unsigned, unsigned, unsigned, void **);
typedef long(__stdcall *DevGetRenderTargetData)(void *, void *, void *);
typedef long(__stdcall *DevCreateOffscreen)(void *, unsigned, unsigned, unsigned,
                                            unsigned, void **, void *);
typedef long(__stdcall *SurfGetDesc)(void *, void *);
typedef long(__stdcall *SurfLockRect)(void *, void *, const void *, unsigned);
typedef long(__stdcall *SurfUnlockRect)(void *);
typedef unsigned long(__stdcall *ComRelease)(void *);

enum {
    DEV_GETBACKBUFFER = 0x48,
    DEV_GETRENDERTARGETDATA = 0x80,
    DEV_CREATEOFFSCREEN = 0x90,
    SURF_RELEASE = 0x08,
    SURF_GETDESC = 0x30,
    SURF_LOCKRECT = 0x34,
    SURF_UNLOCKRECT = 0x38,
    D3DPOOL_SYSTEMMEM = 2,
    D3DLOCK_READONLY = 0x10
};

static int i32(const void *base, int offset) {
    return *(const int *)((const unsigned char *)base + offset);
}
static unsigned char u8(const void *base, int offset) {
    return *((const unsigned char *)base + offset);
}

static void *vslot(void *object, int offset) {
    return *(void **)(*(unsigned char **)object + offset);
}

// D3DSURFACE_DESC: Format, Type, Usage, Pool, MultiSampleType, Quality, W, H.
struct SurfaceDesc {
    unsigned format, type, usage, pool, multisample, quality, width, height;
};
struct LockedRect {
    int pitch;
    unsigned char *bits;
};

// ---- the tile grid --------------------------------------------------------
// The screen is PARTITIONED, not sampled. An earlier shape hashed 32x32 tiles
// centred in much larger cells and covered 16% of the screen, which makes
// "this tile never changed" depend on whether the thing that moved happened to
// walk through a sampled rectangle. A unit is twenty pixels across; most of a
// 640x480 screen was a gap it could cross unseen. Full coverage costs one pass
// over the frame that was just read back anyway -- a few hundred microseconds
// against a readback measured in milliseconds -- and removes the question.
//
// The geometry rides the open line, so the reader places cells from the file
// rather than from a constant it has to be kept in step with.
enum { COLS = 16, ROWS = 12, TILES = COLS * ROWS };

enum { BURST_FRAMES = 8, BURST_PERIOD_MS = 2000 };

// ---- where the records land ----------------------------------------------
static const char PATH_ENV[] = "BFME_FPS_PATH";
static const char PATH_FMT[] = "%s\\My Battle for Middle-earth Files\\FpsProbe.jsonl";

static FILE *s_file;
static int s_opened;
static char s_path[512];
static unsigned s_qpc[2];

// The readback surface, created once for one backbuffer geometry. A geometry
// change invalidates every tile coordinate in the file, so it stops the
// instrument rather than silently re-aiming it at different pixels.
static void *s_surface;
static unsigned s_w, s_h, s_bpp;
static int s_stopped;          // a hard error; sampling never resumes
static unsigned s_burst_at;    // ms the current burst started
static int s_burst_left;
static unsigned s_seq;         // sampled frames
// EVERY present, sampled or not. The reader compares two hashes only when this
// says the engine presented them back to back, and nothing in the image can
// supply that: the counter at 0x01340594 that End_Scene increments looked like
// a frame count and is not one -- across a 90-second capture it took five
// distinct values and was unchanged across 330 of 336 consecutive presents.
// Counting the hook's own firings is the only count that means what it says.
static unsigned s_presents;

// The CRC is recomputed only when the logic frame moves, and cached in between
// so every sampled present can carry it without paying for it.
static int s_crc_frame = -1;
static unsigned s_crc;
static unsigned s_hash[TILES];

static FILE *file() {
    if (s_opened == 0) {
        s_opened = 1;
        const char *path = c_getenv(PATH_ENV);
        if (path == 0) {
            c_sprintf(s_path, PATH_FMT, c_getenv("APPDATA"));
            path = s_path;
        }
        s_file = c_fopen(path, "a");
    }
    return s_file;
}

// Loud, once, and then stop. There is no console to report to from inside a
// code cave, so the record IS the report: the reader refuses a capture whose
// file carries a stop line rather than reporting whatever partial data it has.
static void stop(FILE *out, const char *why, long code) {
    s_stopped = 1;
    c_fprintf(out, "{\"ev\":\"stop\",\"why\":\"%s\",\"hr\":%d}\n", why, (int)code);
    c_fflush(out);
}

// FNV-1a over one cell. `bytes` is a multiple of four by construction: the
// cell width is rounded down to an even number and every format kept here is
// two or four bytes a pixel.
#ifndef FPSPROBE_TIMING_ONLY
static unsigned hash_cell(const unsigned char *bits, int pitch, unsigned x,
                          unsigned y, unsigned w, unsigned h, unsigned bpp) {
    unsigned acc = 2166136261u;
    unsigned bytes = w * bpp;
    for (unsigned row = 0; row < h; ++row) {
        const unsigned char *p = bits + (y + row) * (unsigned)pitch + x * bpp;
        for (unsigned i = 0; i < bytes; i += 4) {
            acc = (acc ^ *(const unsigned *)(p + i)) * 16777619u;
        }
    }
    return acc;
}
#endif

// Bytes per pixel for the formats a backbuffer is actually created in. An
// unknown one stops the instrument: guessing a stride reads the wrong pixels
// and still produces a plausible-looking hash, which is the worst outcome
// available here.
static unsigned bytes_per_pixel(unsigned format) {
    // D3DFMT_A8R8G8B8, X8R8G8B8, A2B10G10R10, A8B8G8R8, X8B8G8R8, A2R10G10B10.
    // The rig measures 21.
    if (format == 21 || format == 22 || format == 31 || format == 32 ||
        format == 33 || format == 35) {
        return 4;
    }
    // D3DFMT_R5G6B5, X1R5G5B5, A1R5G5B5.
    if (format == 23 || format == 24 || format == 25) {
        return 2;
    }
    // D3DFMT_R8G8B8 is 20 and three bytes a pixel, which would make a cell's
    // row length odd; it is refused rather than handled, because no backbuffer
    // this game creates uses it and an untested stride is worse than a stop.
    return 0;
}

// ---- the detour entry -----------------------------------------------------
// DX8Wrapper::End_Scene, at the `mov eax,[TheD3DDevice]` that feeds Present.
// Reached only when the caller asked for a flip, so every call here is a frame
// that really reaches the screen -- render-to-texture passes end their scene
// through the other branch and never arrive.
extern "C" __declspec(dllexport) void __cdecl fpsprobe_present(void) {
    if (s_stopped) {
        return;
    }
    void *device = TheD3DDevice;
    if (device == 0) {
        return;
    }
    ++s_presents;
    unsigned now = c_time();
    if (s_burst_left <= 0) {
        // Unsigned difference, so the 49-day wrap of the ms clock costs one
        // late burst rather than stopping the instrument for a month.
        if (s_burst_at != 0 && now - s_burst_at < BURST_PERIOD_MS) {
            return;
        }
        s_burst_at = now;
        s_burst_left = BURST_FRAMES;
    }
    --s_burst_left;

    FILE *out = file();
    if (out == 0) {
        return;
    }

    void *back = 0;
    long hr = ((DevGetBackBuffer)vslot(device, DEV_GETBACKBUFFER))(device, 0, 0, 0, &back);
    if (hr < 0 || back == 0) {
        stop(out, "GetBackBuffer", hr);
        return;
    }

    SurfaceDesc desc;
    hr = ((SurfGetDesc)vslot(back, SURF_GETDESC))(back, &desc);
    if (hr < 0) {
        stop(out, "GetDesc", hr);
        ((ComRelease)vslot(back, SURF_RELEASE))(back);
        return;
    }

    if (s_surface == 0) {
        // Multisampling makes both a readback and a subrect copy of the
        // backbuffer illegal, so it is a hard stop and not a degraded mode:
        // the capture must be re-run with it off, and a file that quietly
        // contained no tile lines would look like a capture that found no
        // motion.
        if (desc.multisample != 0) {
            stop(out, "backbuffer is multisampled; disable AA and re-run", 0);
            ((ComRelease)vslot(back, SURF_RELEASE))(back);
            return;
        }
        unsigned bpp = bytes_per_pixel(desc.format);
        if (bpp == 0) {
            stop(out, "unhandled backbuffer format", (long)desc.format);
            ((ComRelease)vslot(back, SURF_RELEASE))(back);
            return;
        }
        if (desc.width < COLS * 2 || desc.height < ROWS) {
            stop(out, "backbuffer smaller than the tile grid", 0);
            ((ComRelease)vslot(back, SURF_RELEASE))(back);
            return;
        }
        hr = ((DevCreateOffscreen)vslot(device, DEV_CREATEOFFSCREEN))(
                device, desc.width, desc.height, desc.format, D3DPOOL_SYSTEMMEM,
                &s_surface, 0);
        if (hr < 0 || s_surface == 0) {
            s_surface = 0;
            stop(out, "CreateOffscreenPlainSurface", hr);
            ((ComRelease)vslot(back, SURF_RELEASE))(back);
            return;
        }
        s_w = desc.width;
        s_h = desc.height;
        s_bpp = bpp;
        unsigned freq[2];
        freq[0] = 0;
        freq[1] = 0;
        c_qpf(freq);
        c_fprintf(out,
                  "{\"ev\":\"open\",\"qfreqlo\":%u,\"qfreqhi\":%u,\"w\":%u,\"h\":%u,"
                  "\"fmt\":%u,\"bpp\":%u,\"cols\":%u,\"rows\":%u,"
                  "\"cellw\":%u,\"cellh\":%u,"
                  "\"burst\":%u,\"periodms\":%u,\"tiles_read\":%d}\n",
                  freq[0], freq[1], s_w, s_h, desc.format, s_bpp,
                  (unsigned)COLS, (unsigned)ROWS,
                  (s_w / COLS) & ~1u, s_h / ROWS,
                  (unsigned)BURST_FRAMES, (unsigned)BURST_PERIOD_MS,
#ifdef FPSPROBE_TIMING_ONLY
                  0
#else
                  1
#endif
                  );
    } else if (desc.width != s_w || desc.height != s_h) {
        // Every tile coordinate already written to this file was for the old
        // geometry. Continuing would put two incompatible coordinate systems
        // in one capture under the same field names.
        stop(out, "backbuffer geometry changed mid-capture", 0);
        ((ComRelease)vslot(back, SURF_RELEASE))(back);
        return;
    }

#ifdef FPSPROBE_TIMING_ONLY
    // The readback is the expensive part: a whole-frame GPU-to-CPU copy, 5.76 MB
    // at 1600x900, four times a second, and it stalls the pipeline. Measured, it
    // is what produced ~85 ms hitches and a ~7% simulation deficit at that
    // resolution -- the instrument being the largest thing it measured. At
    // 660x520 the copy is a quarter the size and the same build reads clean,
    // which is exactly why this went unnoticed on the rig.
    ((ComRelease)vslot(back, SURF_RELEASE))(back);
#else
    hr = ((DevGetRenderTargetData)vslot(device, DEV_GETRENDERTARGETDATA))(
            device, back, s_surface);
    ((ComRelease)vslot(back, SURF_RELEASE))(back);
    if (hr < 0) {
        stop(out, "GetRenderTargetData", hr);
        return;
    }

    LockedRect locked;
    locked.pitch = 0;
    locked.bits = 0;
    hr = ((SurfLockRect)vslot(s_surface, SURF_LOCKRECT))(s_surface, &locked, 0,
                                                         D3DLOCK_READONLY);
    if (hr < 0 || locked.bits == 0) {
        stop(out, "LockRect", hr);
        return;
    }

    unsigned cell_w = (s_w / COLS) & ~1u;
    unsigned cell_h = s_h / ROWS;
    for (unsigned r = 0; r < ROWS; ++r) {
        for (unsigned c = 0; c < COLS; ++c) {
            s_hash[r * COLS + c] = hash_cell(locked.bits, locked.pitch,
                                             c * cell_w, r * cell_h,
                                             cell_w, cell_h, s_bpp);
        }
    }
    ((SurfUnlockRect)vslot(s_surface, SURF_UNLOCKRECT))(s_surface);
#endif

    s_qpc[0] = 0;
    s_qpc[1] = 0;
    c_qpc(s_qpc);
    void *logic = TheGameLogic;
    if (logic != 0) {
        int frame = i32(logic, GL_FRAME);
        int mode = i32(logic, GL_GAMEMODE);
        if (frame != s_crc_frame && mode != 4 && mode != 8) {
            s_crc_frame = frame;
            s_crc = c_getcrc(logic, 0, 0);
        }
    }
    void *client = TheGameClient;
    void *net = TheNetwork;
    c_fprintf(out,
              "{\"ev\":\"frame\",\"qlo\":%u,\"qhi\":%u,\"ms\":%u,\"seq\":%u,"
              "\"present\":%u,\"f\":%d,\"cf\":%d,\"phase\":%d,\"desync\":%u,"
              "\"work\":%u,\"idle\":%u,\"limited\":%u,\"anim\":%u,"
              "\"crc\":%u,\"live\":%d,\"tiles\":[",
              s_qpc[0], s_qpc[1], now, s_seq, s_presents,
              logic != 0 ? i32(logic, GL_FRAME) : -1,
              client != 0 ? ((GetFrame)vslot(client, CLIENT_GETFRAME))(client, 0) : -1,
              logic != 0 ? i32(logic, GL_PHASE) : -1,
              logic != 0 ? u8(logic, GL_DESYNC) : 0,
              FRAME_WORK, FRAME_IDLE, (unsigned)FRAME_LIMITED, TheAnimationClock,
              s_crc,
              (net != 0 && i32(net, NET_STATUS) == 1) ? 1 : 0);
    for (unsigned i = 0; i < TILES; ++i) {
        c_fprintf(out, i + 1 < TILES ? "%u," : "%u", s_hash[i]);
    }
    c_fprintf(out, "]}\n");
    ++s_seq;
    // Flushed at the end of a burst only: eight lines then a two-second gap,
    // so the cost is one flush per burst rather than one per readback, and a
    // crash costs at most the burst in progress.
    if (s_burst_left <= 0) {
        c_fflush(out);
    }
}

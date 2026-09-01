// 041-tracksprobe — INSTRUMENT. Why does the terrain-track vertex buffer go
// null while the system is still live?
//
// Three retail minidumps (DUMP-20241020-1152/1155/1157, a multiplayer prefix)
// are the same crash byte for byte, down to esp:
//
//   EXCEPTION_ACCESS_VIOLATION reading 0x00000004, eip = 0x00D1DD7F
//   VertexBufferClass::WriteLockClass::WriteLockClass  <- edi (the buffer) == 0
//     TerrainTracksRenderObjClassSystem::flush         0x0072FEB0
//       RTS3DScene::Customized_Render / Render / draw
//         GameEngine::_bfme_updateClientSubsystems     0x0006B910
//
// flush reads the buffer at [this+0] and hands it straight to WriteLockClass,
// which bumps a refcount at buffer+4. It guards only on the TRACK LIST at
// [this+0x10] being non-empty and on a shader-state query
// (Is_Backface_Culling_Inverted, 0x00910ED0) — neither says anything about the
// buffer's lifetime. So the crash needs exactly three things at once, and this
// probe watches all three:
//
//   system   [0x012F9D98]  non-null  (its caller null-checks this, so it was)
//   tracks   [system+0x10] non-null  (flush's own guard, so it was)
//   buffer   [system+0x00] NULL      (unchecked, and it was)
//
// The static search for what nulls the buffer came up one short. shutdown
// (0x0072EDF0) nulls it, but shutdown has ONE caller — the destructor — which
// frees the object and nulls the global immediately after, so a live system
// with a null buffer is not reachable that way. Either the buffer is never
// created on some path, or something releases it that the call graph does not
// name. That is a question for a running game, which is what this is.
//
// A line is written only when the (system, buffer, tracks) shape CHANGES, plus
// a heartbeat, so a whole match is a handful of lines and a device-loss or
// teardown transition is impossible to miss in them.
//
// ctrl+F9 nulls the buffer deliberately. That is not a fix or a test of one:
// it is how the signature above gets confirmed to be reachable from THIS build,
// so a natural reproduction can be compared against a forced one. It writes the
// engine's own field and then lets the engine crash itself, so the dump it
// produces is comparable with the three retail ones line for line.
//
// INSTRUMENT: --dist refuses it, and it must never ship. No CRT and no loader
// here — see modbuild.py's undefined-externals check.

struct FILE;
typedef FILE *(__cdecl *FOpen)(const char *, const char *);
typedef int(__cdecl *FPrintf)(FILE *, const char *, ...);
typedef int(__cdecl *FFlush)(FILE *);
typedef char *(__cdecl *GetEnv)(const char *);
typedef int(__cdecl *SPrintf)(char *, const char *, ...);
typedef int(__stdcall *QueryCounter)(unsigned *);
typedef short(__stdcall *GetAsyncKey)(int);
typedef void *(__cdecl *OpNew)(unsigned);

#define c_fopen (*(FOpen *)0x013593BC)
#define c_fprintf (*(FPrintf *)0x013593C0)
#define c_fflush (*(FFlush *)0x013593A8)
#define c_getenv (*(GetEnv *)0x013593FC)
#define c_sprintf (*(SPrintf *)0x0135948C)
#define c_qpc (*(QueryCounter *)0x01358EB4)
#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)
// The game's own operator new, as called by the terrain-track system's creation
// site at 0x00730630 (`push 0xc; call 0xc81f30`). Using the engine's allocator
// rather than any of ours keeps the fake node in the same heap the real ones
// live in, so the walk over it behaves the way a walk over a real one does.
#define c_new ((OpNew)0x00C81F30)

#define TheTerrainTracks (*(void **)0x012F9D98)
#define TheGameLogic (*(void **)0x012F0898)

enum { TT_BUFFER = 0x00, TT_TRACKS = 0x10, GL_FRAME = 0x3C, GL_MODE = 0x10C };
enum { VK_CTRL = 0x11, VK_F9 = 0x78 };

// A TerrainTracksRenderObjClass, sized from the two field offsets the engine
// itself uses on one: the flag at +0x12EC/+0x12ED and `next` at +0x12FC.
enum { TRACK_NODE_SIZE = 0x1300 };

static const char PATH_FMT[] = "%s\\My Battle for Middle-earth Files\\Tracks.jsonl";

static FILE *s_file;
static int s_opened;
static char s_path[512];

static FILE *file() {
    if (s_opened == 0) {
        s_opened = 1;
        c_sprintf(s_path, PATH_FMT, c_getenv("APPDATA"));
        s_file = c_fopen(s_path, "a");
        if (s_file != 0) {
            c_fprintf(s_file, "{\"ev\":\"open\"}\n");
            c_fflush(s_file);
        }
    }
    return s_file;
}

static void *field(void *base, int off) {
    return *(void **)((unsigned char *)base + off);
}

// The shape that matters, as one comparable value: which of the three is set.
static int shape(void *sys, void *buffer, void *tracks) {
    return (sys != 0) | ((buffer != 0) << 1) | ((tracks != 0) << 2);
}

static int s_last = -1;
static unsigned s_ticks;
static int s_key_down;

extern "C" __declspec(dllexport) void __cdecl tracks_frame(void *ecx) {
    (void)ecx;
    void *sys = TheTerrainTracks;
    void *buffer = (sys != 0) ? field(sys, TT_BUFFER) : 0;
    void *tracks = (sys != 0) ? field(sys, TT_TRACKS) : 0;

    const int now = shape(sys, buffer, tracks);
    // 3 == system and buffer live, no tracks queued; that is the ordinary idle
    // shape and logging it every 600 frames is enough to prove the probe ran.
    const int changed = (now != s_last);
    ++s_ticks;
    if (changed || (s_ticks % 600) == 0) {
        FILE *f = file();
        if (f != 0) {
            void *gl = TheGameLogic;
            unsigned qpc[2];
            qpc[0] = 0;
            qpc[1] = 0;
            c_qpc(qpc);
            c_fprintf(f,
                      "{\"ev\":\"%s\",\"t\":%u,\"sys\":%u,\"buf\":%u,\"trk\":%u,"
                      "\"shape\":%d,\"frame\":%d,\"mode\":%d}\n",
                      changed ? "change" : "beat", qpc[0],
                      (unsigned)sys, (unsigned)buffer, (unsigned)tracks, now,
                      gl ? *(int *)((unsigned char *)gl + GL_FRAME) : -1,
                      gl ? *(int *)((unsigned char *)gl + GL_MODE) : -1);
            c_fflush(f);
        }
        s_last = now;
    }

    const int held = (c_getasynckey(VK_CTRL) & 0x8000) != 0 &&
                     (c_getasynckey(VK_F9) & 0x8000) != 0;
    if (held) {
        if (!s_key_down) {
            s_key_down = 1;
            if (sys != 0) {
                FILE *f = file();
                if (f != 0) {
                    c_fprintf(f, "{\"ev\":\"force\",\"buf\":%u,\"trk\":%u}\n",
                              (unsigned)buffer, (unsigned)tracks);
                    c_fflush(f);
                }
                // Both halves of the field condition.
                //
                // flush gates on the track list being non-empty, so the list has
                // to hold something. A bare non-null does NOT work and the first
                // attempt at one proved it: the per-frame update at 0x0072EEB0
                // walks the list before flush ever runs and read `next` off the
                // fake node, dying at 0x0072EEDC on address 0x12FD -- a crash of
                // the probe's own making, in the wrong function.
                //
                // So the node is a real allocation from the engine's own heap,
                // zeroed: `next` at +0x12FC reads 0 so the walk terminates on
                // it, and every other field the update reads is 0 too. That
                // leaves flush reaching the buffer deref, which is the crash
                // this is here to reproduce.
                //
                // Only when the real list is empty: a real track is always the
                // better witness, and one must never be overwritten.
                if (tracks == 0) {
                    unsigned char *node = (unsigned char *)c_new(TRACK_NODE_SIZE);
                    if (node != 0) {
                        for (unsigned i = 0; i < TRACK_NODE_SIZE; ++i) {
                            node[i] = 0;
                        }
                        *(void **)((unsigned char *)sys + TT_TRACKS) = node;
                    }
                }
                *(void **)((unsigned char *)sys + TT_BUFFER) = 0;
            }
        }
    } else {
        s_key_down = 0;
    }
}

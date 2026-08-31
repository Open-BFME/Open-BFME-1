// 039-replayctl — pause and resume a replay with ctrl+period.
//
// The spike that produced this is archived at build/s1/replayctl-spike.cpp.bak;
// it also carried a checkpoint/restore probe for a 30-second step-back, which
// does not work. plans/replay-controls.md has the eight runs and the evidence.
// What ships here is the half that does.
//
// THE HOOK, and why it is this one. RVA 0x0006B910 is the body behind GameEngine
// vtable slot 32 — the CLIENT half of the engine frame. It runs on every engine
// iteration INCLUDING the ones where the logic tick is skipped. A hook on the
// logic side would stop being called the moment it paused the logic and could
// never see the key that unpauses it.
//
// Addresses claimed by other features, so nobody re-derives this:
//   0x0006BAE0, 0x0006BC2B                          030-netlatprobe
//   0x0006E910, 0x0006E986, 0x0006E9D9, 0x00909039  036/037/038 (FPS work)
// cave.py makes a second claim a hard build error, not a merge conflict.
//
// PAUSING. GameLogic+0x11C is the whole mechanism. updateNetworkAndLogic reads
// it (isGamePaused is literally `mov al,[ecx+0x11C]; ret`) and skips the logic
// tick; TheNetwork is NULL in a replay so nothing overrides that; and
// RecorderClass::updatePlayback keys off the logic frame at GameLogic+0x3C, so
// the recorded command stream stalls WITH the frame counter rather than running
// ahead of it. The client half keeps running, which is what leaves the camera
// live. Measured: the logic frame held at 937 for 3,176 client iterations, the
// camera panned throughout, and clearing the bit resumed cleanly.
//
// It is frame-exact, and by construction rather than by luck. Only the gated
// phase-1 step advances m_frame — phases 2..6 interpolate and leave it alone —
// so however many ungated sub-steps run between setting the bit and the gate,
// the logic frame cannot move. Verified with the bit set mid-cycle
// (GameEngine+0x30 == 4), which is the case that DOES leak sub-steps: the frame
// still did not advance.
//
// We do NOT call GameLogic::setGamePaused (0x00783490). It writes the same byte
// and then disables input and forces the arrow cursor — the exact opposite of
// what a replay wants. We write the byte.
//
// We write BIT 1, not the value 1. All 28 isGamePaused call sites do
// `test al,al` and none compares against 1, so any non-zero reads as paused,
// and a bit leaves the byte composable with another writer instead of
// clobbering it. Two things this does not survive, both known and both
// acceptable for a replay: setGamePaused does a whole-byte store, so an
// engine-initiated pause (quit menu, popup) clears our bit; and GameLogic+0x11D
// is a SEPARATE live flag, so this is a byte-width write, never a word.
//
// No loader and no CRT: cave.py drops this into an appended section and jumps in
// from mid-function. Nothing here may need a static initializer, an exception,
// 64-bit arithmetic, or a float — modbuild.py fails the build on the resulting
// unresolved external. Fixed-base 0x400000 image, DllCharacteristics 0x0000, so
// absolute addressing is safe.

typedef short(__stdcall *GetAsyncKey)(int);
#define c_getasynckey (*(GetAsyncKey *)0x01358FE8)

#define TheGameLogic (*(void **)0x012F0898)

enum {
    GL_MODE = 0x10C,   // m_gameMode; 3 == GAME_REPLAY
    GL_PAUSED = 0x11C  // m_gamePaused
};
enum { GAME_REPLAY = 3, PAUSE_BIT = 2 };

// ctrl+period. Free in retail: period is only bound in commandmapdebug.ini,
// which a retail build does not load.
enum { VK_CTRL = 0x11, VK_PERIOD = 0xBE };

static int s_key_down;  // edge latch, so holding the key toggles once
static int s_last_mode;

extern "C" __declspec(dllexport) void __cdecl replayctl_frame(void *ecx) {
    (void)ecx;
    unsigned char *gl = (unsigned char *)TheGameLogic;
    if (gl == 0) {
        return;
    }

    const int mode = *(int *)(gl + GL_MODE);
    if (mode != s_last_mode) {
        // Leaving a replay must not strand our pause bit in the next game.
        s_last_mode = mode;
        s_key_down = 0;
        if (mode != GAME_REPLAY) {
            gl[GL_PAUSED] = (unsigned char)(gl[GL_PAUSED] & ~PAUSE_BIT);
        }
    }

    if (mode != GAME_REPLAY) {
        return;
    }

    const int held = (c_getasynckey(VK_CTRL) & 0x8000) != 0 &&
                     (c_getasynckey(VK_PERIOD) & 0x8000) != 0;
    if (held) {
        if (!s_key_down) {
            s_key_down = 1;
            gl[GL_PAUSED] = (unsigned char)(gl[GL_PAUSED] ^ PAUSE_BIT);
        }
    } else {
        s_key_down = 0;
    }
}

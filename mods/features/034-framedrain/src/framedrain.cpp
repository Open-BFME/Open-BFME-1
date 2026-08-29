// 034-framedrain — REFUTED. Kept as the record of a fix that desyncs.
//
// Measured on the rig, 2026-08-29, one match against an otherwise identical
// build: the desync flag set on both seats from logic frame 102 (raised on 26 of
// the logged frames -- GameLogic+0x6C is a FLAG, not a tally, so this is 'at
// least one divergence', not 26 of them), and the match
// dead at frame 127. The comparison arm -- the same build without this feature
// -- and the twelve matches before it show zero.
//
// It did mechanically what it set out to do: the guest's backlog went 1 -> 0
// and its polls-per-frame 1.00 -> 7.39. It was still wrong.
//
// The safety argument below is the part that failed, and it is worth keeping
// because it is convincing and false. It said: every extra pass runs the
// engine's own getFrameAdvanceCount -> areFrameCommandsComplete unmodified, so
// an extra frame only happens when the engine itself says it may. That is true
// and insufficient. areFrameCommandsComplete compares a count that is a
// SNAPSHOT: it can still grow after the comparison, and nothing in the gate can
// see that. Retail is safe not because the gate is sufficient but because a
// guest is only ever asked once per quantum, by which time the frame it is
// asking about is settled. The one-poll-per-frame cadence is load-bearing for
// CORRECTNESS, not just pacing -- and a guest's one-frame lag is the protocol's
// margin, not slack to reclaim.
//
// The precise mechanism is NOT established, and TWO plausible candidates have
// now been tested against the captures and refuted. Recorded so nobody spends
// the same afternoon on them again:
//
//   1. "ceiling == N means the router is still on N and still binding to it, so
//      the guest runs an open frame." Refuted: only 2 of 210 game commands bound
//      to the frame the router was currently on, and both were frame 0.
//   2. "a drained guest sits at frame == ceiling + 1, so the router binds its
//      commands to a frame it has already executed." Refuted: 0 of 23 commands
//      in the drain1 capture were bound to an already-executed frame, worst-case
//      staleness 0 frames. (Small sample -- the match died at frame 127 -- but it
//      points the wrong way for the hypothesis, not weakly for it.)
//
// THE STRUCTURAL CHANGE, measured 2026-08-29 -- this is what the two guesses
// above were reaching for and missing. How long after the ROUTER runs frame N
// does the guest run it:
//
//     retail admission   p50 216.8 ms   p10 200.7   min 128.1   (n=866)
//     034-framedrain     p50  14.2 ms   p10   4.5   min   0.7   (n=127)
//
// The guest stops trailing the router by a full quantum and starts executing
// frames alongside it -- 0.7 ms apart at the closest. The router keeps binding
// arriving commands to its current frame N right up until it runs N, so there
// is a window in which a command can still be assigned to a frame the guest has
// already executed. Retail makes that window unreachable by leaving 200 ms of
// ordering margin; this feature reduces it to under a millisecond.
//
// At the desync, frame 101 carried two commands and the router filed the guest's
// own at t=43215 while the router itself ran 101 at t=43375 and the guest ran it
// at t=43385 -- ten milliseconds apart.
//
// WHY THE MARGIN EXISTS AT ALL, read from the exe 2026-08-29 and stronger than
// the account above. BFME HAS NO RUN-AHEAD. Zero Hour schedules a command
// m_runAhead frames into the future; BFME assigns the router's CURRENT frame:
//
//     sendLocalCommand 0x00A6478D   executionFrame = max(currentFrame, 2)
//     relayCommand     0x00A63121   unbound guest command -> router's current frame
//
// So the router keeps binding arriving commands to frame N right up until the
// moment it runs N. The only thing that stops a command being bound to a frame
// some guest has already executed is that guests run a whole quantum later. The
// guest's one-frame lag is not latency the protocol failed to remove -- IT IS
// THE ORDERING MARGIN, and it is the only one there is. This feature removed it.
//
// That also disposes of the framing in the original rationale below, which
// treated the lag as "the larger half of what a guest still feels" and therefore
// as something to reclaim. It is load-bearing, and any future attempt here has
// to supply a replacement margin before taking this one away.
//
// WHAT IS MEASURED AND WHAT IS NOT. The margin collapse is measured, and the
// no-run-ahead structure above is read directly from the disassembly. That the
// collapse produced THIS desync is still inference: no command in the capture is
// caught being bound after the guest ran its frame, and with 23 commands before
// the match died there may simply not be one to catch. Treat it as the
// best-supported account rather than a proof.
//
// What remains certain regardless: polling the admission gate more often
// desyncs, reproducibly and quickly. Anyone reviving this needs to restore an
// ordering margin, not merely satisfy the readiness gate, and needs a desync
// gate over several matches before believing any green result.
//
// Do not promote this into FEATURES.
//
// ---- the original rationale, preserved ------------------------------------
//
// A guest's simulation runs one 200 ms logic frame behind the host's, every
// frame, forever -- a constant phase offset on the whole simulation, and the
// larger half of what a guest still feels after 031-earlysend.
//
// The frame driver at 0x0006BAE0 runs AT MOST ONE logic frame per call: it
// consults getFrameAdvanceCount, and its single caller uses that count as a
// boolean (`test eax,eax; jle`) before calling GameLogic::update exactly once.
// On the rig the router reaches that driver 13.3 times a second and carries a
// backlog of 0; a guest reaches it 4.97 times a second -- gap p50 198.1 ms, one
// call per logic frame -- and carries a backlog of 1. So the guest is handed
// permission for a frame, spends it, and does not ask again until the next
// quantum has already passed.
//
// The probe's numbers for the same match: the guest ran a frame within 0.1 ms
// of first being told it could, while for 79% of frames areFrameCommandsComplete
// already reported the NEXT frame complete a median 198.0 ms before the guest
// ran it. Hence this: ask again.
//
// One measurement consequence, recorded so it is not later read as a symptom.
// A guest that has fully drained sits at frame == ceiling + 1, so the next call
// is refused by construction, and that refusal path increments the client stall
// counter at Network+0x2C once per frame. `stalls` is therefore not a usable
// gate for this feature.

#define TheGameLogic (*(void **)0x012F0898)
#define TheNetwork (*(void **)0x012F7714)

enum {
    GL_FRAME = 0x3C,
    NET_CONMGR = 0x08,
    NET_STATUS = 0x0C,      // 1 while a match is up
    CM_LOCALSLOT = 0x12028,
    CM_ROUTERSLOT = 0x1202C,
    CM_CEILING = 0x1205C,
    MAX_EXTRA = 2
};

static int i32(const void *base, int offset) {
    return *(const int *)((const unsigned char *)base + offset);
}
static void *ptr(const void *base, int offset) {
    return *(void **)((const unsigned char *)base + offset);
}

// The driver takes its one argument on the stack and cleans it (`ret 4`), and
// overwrites ecx before reading anything, so it is __stdcall and not a method.
typedef void(__stdcall *Driver)(int mode);
#define c_driver ((Driver)0x0046BAE0)

// Re-entry guard. The extra pass goes through this same detour; without this it
// would recurse until the stack ran out.
static int s_inside;

extern "C" __declspec(dllexport) void __cdecl framedrain(void *ecx) {
    (void)ecx;
    if (s_inside != 0) {
        return;     // this IS the extra pass: run its one frame and unwind
    }
    void *net = TheNetwork;
    if (net == 0 || i32(net, NET_STATUS) != 1) {
        return;
    }
    void *cm = ptr(net, NET_CONMGR);
    void *logic = TheGameLogic;
    if (cm == 0 || logic == 0) {
        return;
    }
    // The router is paced by its own QueryPerformanceCounter quantum and already
    // carries no backlog; an extra pass there would be asking it to run faster.
    if (i32(cm, CM_LOCALSLOT) == i32(cm, CM_ROUTERSLOT)) {
        return;
    }

    s_inside = 1;
    for (int i = 0; i < MAX_EXTRA; ++i) {
        int before = i32(logic, GL_FRAME);
        if (i32(cm, CM_CEILING) < before) {
            break;
        }
        c_driver(1);
        if (i32(logic, GL_FRAME) == before) {
            break;      // the engine declined
        }
    }
    s_inside = 0;
}

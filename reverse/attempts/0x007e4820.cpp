// ?d_007e4820@@YAXXZ
// partial score=0.65 date=2026-09-12
// ?frame@Rva007E4820FrameClock@@QAEHH@Z [retail body 0x007E4820]
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// IDENTITY FIX (2026-09-12): retail calls through the real pinned global
// ?g_bfmeNowVNH@@3P6AHXZA (0x00F59544, `int (__cdecl*)()`) at every one of
// its three timing reads (`call dword ptr [0x1359544]`), not through a
// `timeGetTime` dllimport as the earlier stash declared -- that earlier
// declaration compiled to the wrong relocation target. Declare and call
// through the real global function pointer instead.
//
// probe.py: ours=236, retail=230 (was 238/230). Two source-shape fixes each
// shaved bytes: (1) `imul` vs `__allmul` for the multiply depends on which
// operand order the __int64 cast is applied to; the SECOND/THIRD paths'
// `(__int64)(now - m_startTime) * scale` already used the correct
// operand-cast idiom and DID compile to a native `imul` matching retail's
// own `sub eax,[+0x50]; imul dword ptr[+0x40]` (confirmed byte-identical for
// that instruction pair specifically); (2) testing `flags & 0x800000` BEFORE
// loading `m_scale` (an if/else assigning `scale` up front, matching
// retail's test-then-load instruction order) saved 2 bytes over
// load-then-conditionally-shift.
//
// REMAINING GAP (unresolved, 6 bytes / one `sub esp,8` + matching
// `add esp,8`): retail has NO stack frame anywhere in this function (only
// register pushes: esi/edi always, plus ebx/ebp on the frame-limiting path).
// Worked out the EXACT mechanism from the byte offsets: retail's
// `mov [esp+0x14],eax` (storing the computed `nextFrame` value for the later
// comparison) targets, after its four register pushes (esi,edi,ebx,ebp = 16
// bytes), precisely the stack address of the function's OWN INCOMING
// ARGUMENT (`flags`) -- retail overwrites its own dead parameter slot
// in place instead of allocating a new local. Our compiled body allocates a
// genuinely NEW 8-byte slot instead of reusing that dead slot, even though
// register allocation otherwise matches retail exactly (confirmed: ours
// also ends up with edi=nextFrame, ebx=scale, ebp=sign-extension high dword,
// esi=this, the same four callee-saved registers retail chooses). Tried and
// ruled out: reassigning the `flags` parameter directly (`flags = ...`) vs.
// a separate named local `nextFrame` -- both compile to the same 236 bytes,
// so the reuse heuristic is not about which C++ spelling is used for the
// value; the parameter's original stack slot is not what's driving the
// difference. Not attempted: an explicit second stack-argument-shaped
// parameter, or splitting the function into an outer thunk whose own
// argument slot the inner logic could target -- both changes the callable
// signature and were not tried given the mangled name is fixed.

extern int (__cdecl *g_bfmeNowVNH)();

class Rva007E4820FrameClock
{
public:
    int frame(int flags);

private:
    char m_pad0[0x40];
    int m_scale;
    int m_denominator;
    int m_frame;
    int m_pad4c;
    int m_startTime;
};

int Rva007E4820FrameClock::frame(int flags)
{
    if (!*(volatile unsigned char *)0x01309838 && !(flags & 0x44)) {
        return (int)(((__int64)((int)(*g_bfmeNowVNH)() - m_startTime) * m_scale
            / m_denominator) / 1000);
    }

    int scale;
    if (flags & 0x800000)
        scale = m_scale >> 1;
    else
        scale = m_scale;

    int nextFrame = m_frame + 1;
    if (nextFrame >= (int)(((__int64)((int)(*g_bfmeNowVNH)() - m_startTime) * scale
        / m_denominator) / 1000))
        return nextFrame;
    return (int)(((__int64)((int)(*g_bfmeNowVNH)() - m_startTime) * scale
        / m_denominator) / 1000);
}

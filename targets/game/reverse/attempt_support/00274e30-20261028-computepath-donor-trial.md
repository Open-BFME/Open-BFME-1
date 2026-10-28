# 0x00274E30 AIUpdateInterface::computePath — topup-2 investigation (2026-10-28)

Claim: `0x00274E30=bd3c45e1949a4034ad605bb3189b41cb`. Result: BLOCKED, no commit.
Stash `targets/game/reverse/attempts/0x00274e30.cpp` (score 0.5392, 2026-09-26)
re-verified via probe: 3416/3472B, 1488 non-reloc diffs, frame 0x5C vs 0x64,
first divergence at +0x10. Unchanged from history #44/#45.

## Donor evidence (NEW, recorded here)

- Donor revision: `inputs/reference/open-bfme-2` @ `beed8a16790a6812231ac7b05e3e6893e4cb5d1`
  (official Open-BFME-2 master HEAD at session time).
- Donor counterpart: `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_computePath.cpp`
  = `?computePath@AIUpdateInterface@@QAE_NPAVPathfindServicesInterface@@PAUCoord3D@@@Z`,
  donor row 59671, `matched` @ donor RVA 0x00265E0B, 3223B, RET 8.
- Donor is 249B SMALLER than BFME1 retail (3472B) and semantically divergent:
  donor `findPath` takes a 5th `&retry` arg and sets `m_retryPath` from it;
  BFME1 retail `call dword ptr [edx]` (slot 0) at +08b8 passes exactly 4 stack
  args (no retry). BFME1 `patchPath` (slot 3, `[ebx+0xc]`) at +0834 takes
  (obj, set, path, bool-from-`[esi+0x326]`); `findClosestPath` (slot 1) at
  +095c takes 7 args. The BFME1 stash already matches all three signatures;
  the donor must NOT be copied verbatim for the call sequence.
- Donor trial harness path: `python3 tools/bfme2_sweep.py compile <donor path>`
  fails deterministically with `header dependency set changed during trial`.
  Root cause: the second dependency-stability trace contains a phantom
  lowercase-spelled nested include
  (`z:\...\open-bfme-2\code\libraries\include\lib\Coord3D.h`) alongside the
  real `Code/...` path, so the two trace sets never agree (7-line trace in
  `build/bfme2_sweep/trials/ecad2114c7bd4507a965e2a947a135/compile.log`,
  `donor.obj` built fine). Harness/environment issue under wine, NOT evidence
  against the donor body. Do not retry without fixing `bfme2_trial.py` trace
  normalization (case/canonicalization of `-showIncludes` lines).

## BFME1 retail facts established this session (all from `dis_retail.py`)

- `+0x1C0` is `LocomotorSet::m_name` (`AsciiString`); retail inlines `.str()`
  as `m_data ? m_data+8 : Empty` (`mov e?x,[esi+0x1c0]; test; +8 / Empty).
  NOT a locomotor pointer. Stash `DETAIL()` via `locomotorSet.name.str()`
  already matches.
- `m_curLocomotor` is at `+0x1CC` (`mov edx,[esi+0x1cc]` at +00f8), agreeing
  with `game/.../Update/AIUpdate.cpp:178` (`retail this+0x1CC`). Stash layout
  correct here (AsciiString is 4 bytes, so set@0x1A8 + 0x1C ends 0x1C4,
  `locomotor` @0x1CC).
- Header block contains BOTH the `Object %s(%d)` fprintf (+0088) AND the
  `DETAIL` call (+00e0). The stash's header block is semantically complete.
- Portal-true path zeroes `[esi+0x160]=frame`, `[esi+0x16c]=0`,
  `[esi+0x326]=0` — i.e. timestamp/blockedFrames/stuck; `blocked` (+0x325)
  untouched. Stash matches.
- Prologue shape: `push ebx; mov ebx,[g_4FC]` (logger into EBX, kept for the
  first TRACE call), `mov esi,ecx`, flags-tested `je` from the `g_239` test,
  `mov edi,[ebp+0xc]` AFTER the first call (+0040), `mov eax,[esi+8]` (+003d)
  scheduled between the two flag tests. Logger is reloaded per site later
  (`mov e?x,[0x12ed4fc]`); `theNewPath` lives in EBX mid-function
  (`mov ebx,eax` + spill `[esp+0x14]`).

## Hypotheses tested and ruled out (probe, all 3416B/1488 diffs, no movement)

1. Portal result struct `{..., PathfindLayerEnum layer; int portal}` (portal
   @+0x20) vs `{..., int portal}` (portal @+0x1C): ZERO codegen effect
   (address-taken struct). No evidence either way; retail `cmp [esp+0x6c]`
   after a 4-push sequence with callee-popped args is consistent with +0x1C,
   but unproven.
2. Nested-`if (g_239) { if (log) {...} }` vs combined `&&`: ZERO codegen
   effect. The `mov edi` scheduling and EBX-vs-EDX logger allocation are
   driven by something else — prime suspect remains the unexplained frame
   delta (0x5C vs 0x64, 8 bytes), whose source local was not identified.
   `Region3D extent` is 0x18 in both (retail `[esp+0x34..0x44]` use).

## Recommended next steps

- Attack the 8-byte frame delta first: inventory every stack object in retail
  (`lea`/`[esp+..]`/`[ebp-..]` references) vs the stash's locals
  (`PathInfo`, `extent`, `originalDestination`, `pos`, `goalPos`, `retry`,
  `tryClosest`, `theNewPath`); the missing 8B likely a struct-size
  underestimate, not register noise.
- Then re-attack logger-in-EBX: with the frame fixed, try hoisting
  `void *log = g_012ED4FC;` into one local used by all TRACE/DETAIL sites.
- Keep donor call sequence OUT; keep donor control-flow/log-text ideas IN.
- Fix `bfme2_trial.py` trace comparison (normalize case) before any further
  donor-compile attempts for this TU.

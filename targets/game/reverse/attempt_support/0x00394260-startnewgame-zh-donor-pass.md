# 0x00394260 GameLogic::startNewGame(Bool) — ZH donor pass and wall state

Identity (proven, not a guess): `?startNewGame@GameLogic@@QAEX_N@Z`.
Certified-caller notes in functions.csv (loadAmbientLightMap 0x00386DE0,
populateRandomSideAndColor 0x00390A50) and symbols.csv notes
(_bfme_newMap@VictorySystem 0x001DF4A0, _bfme_setEngineVisibility@Mouse
0x005A4B50, liteupdate@Network, loadProgressComplete@Network,
prepareForMP_or_Skirmish@SidesList) all cite it. Boundary: 7643 B; RET4 at
00396038..0039603A + INT3 (identity_evidence/session8-startnewgame-truncated-dump.md).

## Bank (best candidate)

targets/game/reverse/attempts/0x00394260.cpp — full 7643 B control-flow
draft, 370 calls in retail order, address-derived ABI adapters (111 call
adapters are macros so receiver evaluation follows by-value args as
retail does). Re-probed 2026-10-27 on the current tree:

    py -3 tools/probe.py targets/game/reverse/attempts/0x00394260.cpp \
        "?startNewGame@GameLogic@@QAEX_N@Z" 0x00394260 [--shape]

    ours=7566  retail=7643 (claimed)  relocs=498
    4655 non-reloc byte diffs, first at +23
    shape 0.892; 172 structural diffs, first at +0391
    frame 0x344 vs retail 0x340 (first diff +0015)

Diag artifacts (untracked, reproducible by the command above):
build/probe_00394260_repro.txt, build/probe_00394260_shape.txt,
build/callees_00394260.txt (116-target inventory).

## ZH donor pass (2026-10-27)

Donor: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/
Source/GameLogic/System/GameLogic.cpp lines 1105-2370 =
`GameLogic::startNewGame(Bool loadingSaveGame)`. Read in full; the donor
call sequence maps onto the retail ILT inventory:
checkForDuplicateColors 0x386520, populateRandomSideAndColor 0x390A50,
populateRandomStartPosition 0x00390F90, placeNetworkBuildingsForPlayer
0x38A9F0, FindWaypointByName 0x388820, Player::iterateObjects thunk
0xCDCF0, getLoadScreen 0x386190, setFPMode x2 (0x8FC4C0),
PartitionManager::revealMapForPlayer 0x8F73D0, Pathfinder::NewMap
0x3D80F0, Network loadProgressComplete/liteupdate at donor lines 2169-2170
(the ledger note that pinned this twin).

BFME 1 additions absent from the donor (bank already models them):
Mouse setEngineVisibility 0x5A4B50 (body offset 0x198),
GameLogic::loadAmbientLightMap 0x386DE0, ControlBar side-asset preload
0x4A2CB0, preloadSpellTextures 0x59A3D0, VictorySystem::_bfme_newMap vcall
0x001DF4A0 (vtable 0x0109FD8C +0x24, right after PlayerList newMap),
GetSystemMenu/EnableMenuItem quit-menu re-enable (IAT, x2 each),
Radial ControlBar scheme strings (RadialClockOverlay1/2, RadialBorder,
RadialOver, RadialPush), menu-close guard (ctor 0x00382DA0 / dtor
0x00382DD0, frame -844).

Verdict on the donor: applicable as a semantic twin and identity
corroboration; NOT a byte-path repair. The residual is (a) frame slot
packing that the measured VC7.1 rules make unreachable from source, and
(b) body-wide regalloc residue. A donor-driven rewrite starts from the
same wall; the bank already encodes retail's exact call stream and local
lifetimes (retail /FAsc + eh_info), which the donor source cannot improve.
Donor revision: the in-repo ZH reference tree at the current checkout.

## The wall (why the bank is where it is)

Frame: retail packs guard(4B) -844, key(AsciiString, IsThreadedLoad) and
progress(59B) sharing -840, prefs(OptionPreferences, 20B) -836, game
-816, pos/skirmish + second-loop counter(41) -812, cameraName -800,
created/stream -796. Bank /FAsc: guard -848, key -844, game -840
(function scope), created -804, progress -788 (own slot), cameraName -784.
Measured VC7.1 slot-packing rules are in docs/shape_levers.md
(factor-two size rule; last-created candidate never shares; address-taken
function-scope locals never share). A greedy simulation of those rules
over code-range lifetimes did NOT reproduce retail's grouping (recorded
in that doc under the startNewGame entry) — treat the rules as
constraints, not a full model.

Regalloc residue (the bulk of the 172 structural diffs): zero-register
lives in ebx/ebp longer than retail and spill-choice flips, e.g.
  +03ea  retail `xor ebp,ebp`            ours `mov edi,[esp+0x18]`
  +0407  retail `mov eax,[ecx+0x58]` `add ecx,0x58`
  +040a  ours `lea ecx,[eax+0x58]` `mov eax,[ecx]`   (vtable-field walk)
  +04b4  retail `mov byte [esi+0xa0],0`  ours `..., bl` (zero via reg)
  +052b  retail `mov byte [eax],0`       ours `..., bl`
  +0391  retail stores 0x412a3267 direct; ours via ebp round-trip

## Prerequisite revisit (changed since the 2026-10-15 verdicts)

The recorded prerequisite was "land the dumps first" (14 dump callees +
typed pins). As of 2026-10-27 ten of the fourteen are clean-matched
(0x00144DC0, 0x001AD080, 0x002ECF40, 0x00367470, 0x00386190, 0x0038A9F0,
0x00390A50, 0x003D80F0, 0x004A2CB0, 0x0059A3D0). The bank calls every
callee through its retail call-site shape (ABI inferred from the call
itself), and for all ten the now-proven ledger signatures agree with the
inferred thiscall/cdecl + stack-slot counts, so landing them changed no
call-site bytes in the bank. Four remain dumps, each blocked on its own:
0x0019FF20 (693B), 0x0038F7B0 (2335B, map-object + 3 AI template names),
0x003916F0 (596B), 0x00392D00 (2353B, GameLogic side-population member
called via ILT 0x000298E3 at body 0x0039494B; 0x7C vs 0x68 frame — the
same 4-byte packing wall, ten verdicts of its own).

## Ruled out (do not repeat)

alignment facades, union alignment, /FAsc scope trials, localSlot
variants, the 32-trial exception-shape search, adapter-macro rewrite
(done; 4755->4655), OptionPreferences 20B layout, created/stream slot
sharing, nested blocks, game holder/reference, throw() facade pattern
(2026-09-28 scan found no second instance), and the compiler-flag
family (the 0.892 shape match under the standard flags is itself
evidence the flags are right; a flag delta would diverge shapes globally,
not locally). Compiler settings from the bank's cl line: /DNDEBUG
/DWIN32 /D_WINDOWS /MD /EHsc + stlport (see the stash header).

## Resume

Re-probe the bank only when one of the four dump callees lands (then
re-check that callee's ABI against the bank adapter) or when a new
shape-lever entry targets the zero-register/spill family. A donor-driven
rewrite is not a shorter path; the identity is proven and the block is
compiler-internal (frame packing + regalloc), recorded as
blocker=stack-slot/frame-layout.

## Re-draw 2026-10-27 (5th draw)

Re-drawn from the deferred pool after untried work ran dry. Tree unchanged
since verdict 14 (master == 7b17edd73a); the four dump callees are still
gen-dump rows; no new shape_levers entry. Donor evidence revisited: official
BFME 2 tip advanced 73898a96 -> a32b57717 (635 commits); the span does not
touch donor GameLogic.cpp or the shape/recipe docs and its commit messages
carry no applicable hits (startNewGame/394260/regalloc/zero-register/FAsc/
packing). No re-scan (unchanged inputs); verdict 15 recorded. Block stands.

## Re-draw 2026-10-27 (7th draw)

Re-drawn from the deferred pool after untried work ran dry (54
already-investigated hidden, 6 deferred). Verified both Resume conditions
unmet against 6f31f09be3: (a) the four dump callees
0x0019FF20/0x0038F7B0/0x003916F0/0x00392D00 are still gen-dump rows in
functions.csv (37174/37547/37549/37551) - none landed; (b) no new
shape_levers entry - the only upstream commit since the 5th draw (6f31f09be3,
another worker's 0x002850A0 shape-0.967 bank, model=claude-opus-5-5, residue =
early push ebp +0x32 vs +0xCF plus m_object reload register) is a different
function with a different residue family, recorded as a handoff note not a
shape-lever entry. That commit touches nothing under docs/, game/ or inputs/
(2 attempt_history JSONs + the handoff + the re_attempts.log line), so the
bank inputs (bank file + TU + ledger + shims + shape_levers) are
byte-unchanged and the in-repo ZH donor tree is unchanged. Per "do not repeat
unchanged scans", no re-probe (shape 0.892 / 4655 non-reloc / 172 structural,
frame 0x344 vs 0x340 stands). Verdict 16 (7th draw) recorded. Block stands.

## Re-draw 2026-10-30 (8th draw)

Re-drawn from the deferred pool against 5f0d3fd46d (360 commits / 818 files
since verdict 16's tree). Both Resume conditions verified unmet: (a) the four
dump callees 0x0019FF20/0x0038F7B0/0x003916F0/0x00392D00 are still gen-dump
rows (functions.csv 37149/37502/37504/37506); (b) all 11 new shape_levers
entries since 8bbb61ae41 were read in full (container-indirection temp
rotation; visible-callee escape x3; x87 CSE operand order; switch-constant
cross-jump; constant-register tail-merge; shared trailing call saves +
register-arg order; offset-struct locals; EBP-prologue release-and-return +
index local; local split + inline table getter; array-pop declaration order;
opposite-polarity heads; tail-merge receivers x2 + body-private static; TU
by-reference locals; forceinline store-group + sqrt pop order) - none targets
the zero-register (ebx/ebp) lifetime, spill-choice or frame slot-packing
family that walls this body. The only diff in this body's TU (GameLogic.cpp,
0f9a68d7fb) is the g012F706C -> TheLivingWorldManager macro, outside
startNewGame. Bank inputs otherwise byte-unchanged, so no re-probe per "do not
repeat unchanged scans" (shape 0.892 / 4655 non-reloc / 172 structural, frame
0x344 vs 0x340 stands). Verdict 17 (8th draw) recorded. Block stands.

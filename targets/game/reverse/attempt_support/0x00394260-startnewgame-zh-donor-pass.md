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

## Re-draw 2026-11-13 (9th draw): the Zero Hour reference lane, run for the first time

Verdicts 1-17 left the Zero Hour reference lane NEVER run in this checkout:
`build/spike_zh` and `build/zh_sweep` did not exist, so no ZH compile or byte-compare
had ever been attempted for this body. This draw ran the lane end to end, so the
donor is now byte-compared rather than read. Claim `Claim-Lease: 0x00394260=64a076783de34ec487bc1832b2681de6`
(own lease). No production source, pin or ledger row changed by this draw.

### What the lane produced (`tools/zh_sweep.py compile` / `match` / `land-multi`)

* `compile`: 918 built, 1 cached, 68 failed of 987 `GeneralsMD/Code` TUs over the
  sweep's ten subtrees. All 68 failures are the WWAudio/MILES shim family (`AIL_*`,
  `HSTREAM`, `HPROVIDER`, `LPCTSTR` unresolved against
  `inputs/reference/shims/sweep/windows.h`). The unit that owns our target's body,
  `GameEngine/Source/GameLogic/System/GameLogic.cpp`, compiled; its
  `GameLogic_System_GameLogic.stl.obj` is in the cache.
* `match`: 26,402 function COMDATs from 919 objects — 3871 exact-multi (256,050 B),
  2076 exact-unique-CLAIMED (286,516 B), 4708 near, 4670 no-needle, 11077 no-placement.
  There is **no `exact-unique-unclaimed` bucket at all**: every exactly-unique ZH
  placement lands on ground the ledger already claims, so `zh_sweep.py land` has
  nothing new to append. Evidence: `build/zh_sweep/match.json`.
* The target's own donor COMDAT: `?startNewGame@GameLogic@@QAEX_N@Z` from the ZH
  unit is **8968 B against retail's proven 7643 B** and bucketed `no-placement` —
  it had a searchable reloc-free needle (>= 10 bytes) and that needle occurs nowhere
  in BFME 1's `.text`. Not a byte twin, not a near miss, not a placement anywhere.
  This is the measurement the earlier donor pass was missing, and it confirms that
  pass's verdict: a semantic twin, not a tier-1/2 byte-path repair.
* The four dump callees 0x0019FF20 / 0x0038F7B0 / 0x003916F0 / 0x00392D00: no ZH
  COMDAT places at any of them, exact or near. `land-multi` over all 901 gen-dump
  rows at HEAD (705,598 B, 489 distinct sizes) against the 1196 multi-placed bodies
  reports **0 dump addresses an exact-multi twin can be landed on**, 0 proven pins,
  0 string rejections — "every candidate was filtered out". Resume condition (a)
  is NOT fired: the four rows are still `matched,gen-dump` (functions.csv
  37063/37393/37395/37397 at this tree).
* `packets`: deliberately NOT run. `do_packets` rebuilds the TRACKED
  `targets/game/reverse/zh_sweep/packets/` directory and unlinks every packet this
  run does not reproduce, which would delete another contributor's annotated lead.
  The same filter reproduced read-only over `match.json` (near with align >= 0.85,
  live ledger claims re-derived from `functions.csv` spans): 1495 near records over
  849 distinct addresses, **all 849 already claimed -> 0 packets**, and 0x00394260
  is not among the near addresses. The lane is exhausted against the live ledger
  repo-wide, not just for this body.

### BFME 1's own home TU already carries the vendored source (new this draw)

`game/GameEngine/Source/GameLogic/System/GameLogic.cpp` (the wb1 home) carries the
EA source of `GameLogic::startNewGame( Bool loadingSaveGame )` at lines 2604-3870,
marked `// ?startNewGame@GameLogic@@QAEX_N@Z present-unmatched`. Probing that real
TU with its own `// cl:` line
(`tools/probe.py game/GameEngine/Source/GameLogic/System/GameLogic.cpp
"?startNewGame@GameLogic@@QAEX_N@Z" 0x00394260 --size 7643 --shape`): emitted 8263 B,
5427 non-reloc diffs, **shape 0.360, 209 structural**, frame `sub esp, 0x304` vs
retail `0x340`. Divergence is immediate at +001b: retail does `push ebx / push ebp /
push esi / push edi / xor edi,edi` while ours reads a flag first (`mov al,[esp+0x314]`)
then `mov ebp,ecx / mov ebx,1`. So the vendored body is 620 B too large and
structurally unlike retail; the hand-authored bank (shape 0.892 / 172 structural,
frame 0x344) remains far and away the best candidate. Do not "land" the vendored
source in place of the bank: it is a present-unmatched filler and swapping it would
be the tier-4 fallback the rules forbid.

### BFME 2 donor attempt (setup blocked, not evidence about the body)

`tools/bfme2_sweep.py compile Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`
fails. Unmapped it resolves the donor's own
`inputs/reference/open-bfme-2/reference/shims/{bfmealloc,bfme2_ascii,bfmelist}` and
dies on `_STL::list<_Tp,_Alloc>::resize` / `_STL::allocator<char>::deallocate`
unable to match (trial `build/bfme2_sweep/trials/7c00bd55265b4bc7bb0c28381d956eaa`).
Mapped to BFME 1's `inputs/reference/shims/stlport_bfme` and
`asciistring_outofline` (`build/local-model-probe/zh_bfme2_map.json`) it fails earlier:
`quoted include unresolved: ascii_string.h`. Per the repository rules a path/setup
failure is recorded as a blocker, not as evidence the donor body is wrong.
Structurally the BFME 2 route is ruled out regardless of further mapping work: BFME 2's
own `?startNewGame@GameLogic@@QAEX_N@Z` row is 546 B at 0x00248558 in a different
executable, decomposed into `startNewGame_Init` 0x00241230/431 B,
`startNewGame_PlaceMPBuildings` 0x002421F5/494 B,
`startNewGame_OpenLoadScreen` 0x00244CB0/166 B plus a 736 B tail row — functions BFME 1
retail does not contain. Tier-1/2 donor reuse cannot reproduce a 7643 B monolith; the
donor's value is the call-stream semantics the bank already encodes.

### Resume for the next agent

Resume conditions are now: (a) one of the four dump callees lands — the ZH lane cannot
land them (0 supersessions), so only a BFME 1 structural recovery of one of them will
do; (b) a new `docs/shape_levers.md` entry targeting the zero-register (ebx/ebp)
lifetime, spill choice or frame slot packing. The four entries added 2026-11-12
(`a661a9c828` HRESULT switch return-group order, `2ccc080692` `__LINE__` diagnostic
arguments, `c79eeaa702` a global STL-linkage COMDAT footprint, `832811202e` canonical
adoption with `eh_state_pins.py` label repinning) do not target that family. Do not
re-run the ZH sweep while its inputs are unchanged: the object cache `build/spike_zh`,
`build/zh_sweep/match.json` and this section record what it concluded, and its
conclusion is that the lane is exhausted. Verdict 18 (9th draw) recorded. Block stands.

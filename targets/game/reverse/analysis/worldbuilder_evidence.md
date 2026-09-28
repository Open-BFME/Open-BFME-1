# EA evidence from WorldBuilder internal builds

BFME1's and BFME2's WorldBuilders are internal builds of the game engine, and their code
names itself: `Class::method` strings and EA source paths (`Z:\LOTR\Code\...\File.cpp`)
referenced from inside the function they describe. The release game has neither. Pairing
the game's functions with WorldBuilder's recovers EA's original file for about two-thirds
of the game's own code bytes and EA's own name for about 1,300 functions.
`tools/ea_evidence.py` writes `targets/game/reverse/ea_evidence.csv`. Briefs, the placement
lane and `tools/ea_name_guard.py` read it. Measured 2026-09-29.

## Pairing

| Pairing | Held-out precision | Pairs |
|---|---|---|
| game - BFME1 WorldBuilder | 98.4% | 23,851 |
| BFME1 - BFME2 WorldBuilder | 94.4% | 18,942 |
| game - BFME2 WorldBuilder | 89.5% | 11,352 |

Held-out: half of the export and unique-string seeds are hidden, and the run is scored on
how it pairs them. `ea_evidence.py` refuses to write below 95%, 90% and 85%.

1. **Seeds.** Shared exports; string literals referenced by exactly one function on each
   side (97.8% precise); BSim unique top-1 matches (`tools/ghidra/bsim_query.java`: at least
   0.5 similar, 0.05 ahead of the runner-up, claimed once), 99.6% right on string truth.
2. **Anchored alignment**, the lever that made the difference: 6,295 pairs became 23,851.
   The two builds link their object files in a different order, so only 37% of known pairs
   keep a global order. Inside an object, though, functions stay in source order: 80% of
   consecutive pairs step forward together. Between two pairs at most 32 KB apart on both
   sides, the unpaired functions are aligned in order by instruction-mnemonic similarity (at
   least 0.6), skipping functions only one build has.
3. **Call-graph propagation.** Gap fill between paired calls, and callee fingerprints.
   Alignment and propagation alternate until neither grows.

Rejected, do not retry:

- BSim top-1 without a margin: mostly wrong. Small and sibling functions tie at 1.0, and
  internal-build asserts change the p-code enough that the true partner is often not in
  the top 5.
- Positional vtable alignment with Zero Hour: 36% precise, because BFME shifted slots.
- WorldBuilder exports: the same ~1,820 symbols the game exports.
- RTTI: the exe has 76 type descriptors, all STL/CRT exception types.

## What the pairs transfer

**Files** (27K functions). Routes, in order of trust:

- `wb1`: the partner references its own path.
- `zh`: Zero Hour defines the ledger's Class::method out of line in exactly one `.cpp`.
- `wb2`: BFME2's path.
- `*-run`: filled between two same-file neighbours, in WorldBuilder's or retail's order.

Checked against an established Zero Hour class home, `zh` agrees 99.5% and `wb1` 91%. The
`wb1` disagreements are BFME1's real reorganisation, not errors: Pathfinder moved to
`GameLogic/Pathfinder/pathfinder.cpp`, and INI, FileSystem, Xfer and Geometry moved under
`Libraries/Source/`. BFME1 already had `dxwrapper.cpp`. Retail-run agrees only 84%,
because it gives an inline or template body the TU that emitted it, not its home. The
placement lane therefore moves files on `wb1` and `zh` only.

**Names** (1,328). BFME2's labels name ~5,100 functions, BFME1's only 86. A game function
gets a label through `direct` (game to WB2), `chain` (game to WB1 to WB2) or `wb1`, and routes
that disagree give no name. Against plain ledger names, labels agree 76% of the time, and
84% where both routes agree on strong legs. The disagreements in samples:

- Invented ledger names: the majority, for example `bfmeCellTypeTwo` for
  `Pathfinder::IsCliffCell` and `BfmeP1050::bfmeFwd1050` for
  `PartitionManagerImpl::GetClosestObject`.
- Zero Hour names that BFME renamed: `xfer` became `DoXfer` (BFME1's own exports say so),
  and `DX8Wrapper` versus `DXWrapper`.
- Label errors, which make a label evidence rather than proof:
  - A body that inlined a labelled callee carries the callee's label:
    `~AIStateMachine` is labelled `AIStateMachine::clear`.
  - Some `Class::member` strings tag allocations, not methods: `MeshMatDescClass::UV`.
  - Near-identical functions get paired wrongly now and then: a D3DX parser function was
    labelled `AptPlayer::GetExtern`.

## Ceilings by category

The denominator is the game's own functions: 73,580 rows, 7.74 MB. It excludes 62K import
thunks, 28.5K compiler funclets and 4.3K vendored functions.

| Category | Backed by evidence | Source |
|---|---|---|
| function names | 31.5% of bytes before, ~40% with WorldBuilder labels | exports, exact ZH symbols, labels |
| original file | ~2/3 of bytes (half of it placeable, `wb1`/`zh`) | WorldBuilder paths, ZH, retail runs |
| class of a placeholder | 7-10% of placeholder functions | vtable slots (2,896), labelled members |
| globals | 13% confirmed by ZH; 32% are placeholders, 25% invented | no WorldBuilder names |
| members | ~61% (`tools/name_oracle.py`) | ZH offsets, INI tables |
| locals, parameters | ~0%, except bodies with an exact ZH twin | nothing in any binary |

The remaining ~60% of function bytes is BFME-specific code with no name in any binary we
have.

## Where it is used

- Briefs (`tools/fleet/context_pack.py`) print `EA name` and `EA source file`.
- `tools/placement_queue.py`: EA's own path, when every row a file owns agrees, is the
  strongest destination rule.
- `tools/ea_name_guard.py` (pre-commit and pre-push): giving a placeholder address a real
  name against a strongly paired EA name fails, unless the name is EA's, one Zero Hour
  declares, the export, or keeps the address token, or the notes say
  `ea-name-disputed=<evidence>`. Replayed over 2026-09-15..29, it would have stopped 85
  names, almost all invented (`_bfme_showOptions` for `AptOptions::OpenScreen`).

## Regenerating

1. Export each WorldBuilder with `tools/ghidra/worldbuilder_analysis.java`
   (`tools/worldbuilder_analysis.py --analyze`). BFME2's exe is not in this repo. Headless
   analysis takes about 10 minutes for BFME1's and 60 for BFME2's.
2. Optionally, BSim:
   - `bsim createdatabase file:/dir/wb1 medium_nosize`, then
     `bsim generatesigs ghidra:/dir/project --bsim file:/dir/wb1`, for each WorldBuilder;
   - `analyzeHeadless <game project> -postScript bsim_query.java 5 0.5 file:/dir/wb1
     game_wb1.tsv file:/dir/wb2 game_wb2.tsv`, and the same on BFME1's WorldBuilder
     project against WB2 for `wb1_wb2.tsv`.
   - This takes about an hour in all and adds about a quarter more pairs.
3. `python3 tools/ea_evidence.py --wb1 DIR --wb2 DIR --wb2-exe PATH --bsim DIR`, about 10
   minutes.

## Open, for when agent naming is revisited

- 983 placeholders whose WorldBuilder partner carries assert or debug text. For 517 of
  them, the game body has no string of its own.
- RotWK's WorldBuilder is an internal build with ~6K more labels and is not paired yet.
- Existing invented names that contradict strong labels are a correction queue:
  `ea_name_guard.py --range <old> HEAD` lists the recent ones.
- Folding strays into their EA file: the destination is now known for most of them, but
  95% collide with their target on types (see the placement lane).

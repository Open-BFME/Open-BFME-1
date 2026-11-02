# dir32 gate debt at VA 0x012F4A00 — num_get facet ID (STLport name), guard-blocked

Debt line (body_guard_baseline.csv:494, shrink-only):

    dir32,0x012F4A00,?id@?$num_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@2V0locale@2@A,"retail 0x012F4A00 is already recorded as ?g_bfmeSlot04VA@@3HA (+2 more); reference that name, not a new one"

## What the debt is

The datum at VA 0x012F4A00 (RVA 0x00EF4A00) is the four-byte narrow
`_STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >`
`locale::id` facet identifier (value 12, `.data`). Identity is established:
`targets/game/reverse/identity_evidence/00ef4a00-scalar-global.md` (RVA 0x00831F90
writes 12; readers 0x0053CA40/0x005380A0 pass its address to
`locale::_M_use_facet`; `inputs/vendor/stlport/stl/_num_get.h:238` initializes
`num_get<char,...>::id._M_index = 12`).

The STLport name is referenced by the `_M_get_num<char,char_traits<char>,long>`
body (RVA 0x0053CA40, `game/Libraries/Source/STLport/Rva0053CA40NumericInput.cpp`,
DIR32 at +0x6f) — verified by `build.dir32_references`. That body is a cleanly
`matched` 262-byte row built from the vendored template
(`_istream.c:233` `_M_get_num` uses `use_facet<num_get<char,...>>`, which emits
`_M_use_facet(num_get<char>::id)`). It is NOT a reconstruction target; the issue
is purely the symbol name, which the ledger does not record.

## Why the naive "mirror num_put" path is blocked

The num_put sibling (VA 0x012F64E4) was resolved by recording its STLport name in
`dir32_addresses.csv` (line 11949) + a `data_rows.csv` row (line 592) + converting
the writer/reader to the STLport name (commit e83e449d95). But that recording
predates the guard:

- num_put STLport dir32 row added 2026-09-27 (commit 99e2be2a35).
- the "already recorded" guard added 2026-10-05 (commit f4b01f3dc5, "Gate: check
  what DIR32 masking and the extent hid (BFME1 red team)").

The guard is `unrecorded_dir32_problem` (tools/build.py:3636):
`others = at.get(base, set()) - {sym}` (where `at` is built ONLY from
dir32_addresses.csv); if `others` is non-empty it returns "already recorded as
<name>; reference that name, not a new one" — BEFORE the `data.get(sym)==base`
path. `dir32_record.py record` applies this guard to every proposed addition, so
it refuses the STLport name while the base is recorded under other names.

Verified live (build/guard_test.py): `unrecorded_dir32_problem(?id@?$num_get@...,
0x012F4A00)` returns the "already recorded as ?g_bfmeSlot04VA@@3HA (+2 more)"
problem. So `dir32_record.py record` will not add the row as long as the base
still holds other names.

## The base's name landscape (0x012F4A00)

Recorded in dir32_addresses.csv:
- `?g_bfmeSlot04VA@@3HA` (line 10695) — ZOMBIE: `git grep g_bfmeSlot04VA -- game/`
  finds no source. No data row.
- `?g_rva005380a0_id@@3DA` (line 11401) — ZOMBIE: no source uses the `D`
  (char/array) spelling. No data row.
- `?g_rva005380a0_id@@3IA` (line 16627) — LIVE: `unsigned int g_rva005380a0_id`
  defined in `game/GameEngine/Source/Common/BfmeOneHundredTwentyTwo.cpp`
  (writer `bfmeAssignSlotsVA` line 40: `g_rva005380a0_id = 12;`) and read by
  `game/GameEngine/Source/Common/Rva005380A0Facet.cpp` (reader `rva005380a0`
  lines 18/23). One data row (data_rows.csv:278) for this name at the VA.

The STLport name is referenced by the `_M_get_num` object (0x0053CA40) and, after
the fix, by the writer/reader. The writer already uses the STLport name for the
num_put slot (line 42 `_STL::num_put<char>::id._M_index = 14;`) — the exact model.

## The verified resolution (num_put pattern, guard-ordered)

Each step below is evidence-backed; the ordering is forced by the guard (the game
names must be retired BEFORE the STLport name is recorded, and the data row must
exist before both the retires and the record).

1. Convert the writer `BfmeOneHundredTwentyTwo.cpp` line 40
   `g_rva005380a0_id = 12;` to `_STL::num_get<char>::id._M_index = 12;` and add the
   `extern template _STL::locale::id _STL::num_get<char, _STL::istreambuf_iterator<
   char, _STL::char_traits<char> > >::id;` declaration (mirror lines 7-8/42 for
   num_put). Both are stores of 12 to the same 4-byte id object -> byte-matches
   (the num_put line 42 proves the shape).
2. Convert the reader `Rva005380A0Facet.cpp` to the num_put reader shape
   (`Rva005C0FD0Facet.cpp`): `#include <istream>`, drop the minimal `_STL::locale`
   declaration, add `template _STL::locale::id _STL::num_get<char,
   _STL::istreambuf_iterator<char, _STL::char_traits<char> > >::id;`, and use
   `_M_use_facet(_STL::num_get<char>::id)`. Verified low-risk: the real
   `_STL::locale::_M_use_facet` is `facet* _M_use_facet(const id&) const`
   (`_locale.h:175`) — IDENTICAL to the minimal declaration the reader uses, so the
   call shape and the 0x12f4a00 address are unchanged -> byte-matches.
   (After 1+2 the live game name `?g_rva005380a0_id@@3IA` is unreferenced.)
3. Add the STLport-name data row (source = the reader TU, matching the num_put
   pattern): `py -3 tools\add_data_match.py "?id@?$num_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@2V0locale@2@A" 0x012F4A00 game/GameEngine/Source/Common/Rva005380A0Facet.cpp --va --size 4 --model <model> --evidence targets/game/reverse/identity_evidence/00ef4a00-scalar-global.md`.
   (Now the STLport name is "ledger-owned" at the VA.)
4. Retire the three game names, each `--for` the STLport name
   (`py -3 tools\dir32_record.py retire <OLD> --for <STLport> [--msg FILE]`):
   `?g_rva005380a0_id@@3IA` (live; unreferenced after 1+2, so its bare identifier no
   longer occurs under game/), `?g_bfmeSlot04VA@@3HA` (zombie), and
   `?g_rva005380a0_id@@3DA` (zombie). The retire guard (dir32_record_guard) requires
   NEW ledger-owned at OLD's VA (the data row from 3) and OLD absent from game/ +
   shims/. After this, dir32_addresses.csv holds NO name at the VA.
5. Run the full gate (`.\build.cmd` with no selector, or a committing change) to
   generate the proposal `build/dir32_addresses.csv` (absent now). The gate is
   green: with the game names retired, `unrecorded_dir32_problem(STLport, VA)` has
   empty `others` and hits `data.get(sym)==base` (the row from 3) -> passes.
6. `py -3 tools\dir32_record.py record` to adopt the STLport name into
   dir32_addresses.csv (the guard now passes: `others` empty, data row backs it).
7. Retire the debt: `py -3 tools\repair_queue.py pass-test 'dir32,0x012F4A00,?id@?$num_get@DV?$istreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@2V0locale@2@A,"retail 0x012F4A00 is already recorded as ?g_bfmeSlot04VA@@3HA (+2 more); reference that name, not a new one"'`.
   The reader TU's STLport reference is now recorded (6) so the line deletes and
   stays deleted.
8. Verify (the committing change's full gate + scoped builds of the writer/reader/
   `_M_get_num`), commit on its own, push (pull --rebase / push / pull).

## Cost / why it was banked

Steps 5+8 are two full-gate runs (~40-60 min each). The full sequence is
2 source edits (verified byte-match) + 3 retires + 1 data row + 2 full gates +
record + pass test. It is completable and fully planned, but the double full-gate
cost made it the wrong item to finish this loop turn; the next served item (the
0x00394260 6th re-draw) is quick. Resume here: execute steps 1-8 in order.

## Resolution (2026-11-02)

Steps 1-4 executed exactly as planned and scoped-verified (both TUs green,
byte-matched; data row zero-filled 4 B at 0x012F4A00; the three retires
landed, leaving NO name at the VA). Step 5's full gate ran on the then-HEAD
(95fc3b901f) and went RED on 11 unrecorded DIR32 names unrelated to this
item (none baselined; the repo had been running scoped gates only since they
appeared). Our name was NOT among the failures: with the game names retired
and the data row in place, `unrecorded_dir32_problem(STLport, VA)` passes via
`data.get(sym)==base`, exactly as step 5 predicted — the full-gate run
confirms the guard analysis. No proposal was written (the gate is red), so
step 6 (`record`) could not run.

Deviated from the banked plan at the user's direction: the item landed
WITHOUT the dir32 record. The matched data row already gives the STLport
name its ledger identity at 0x012F4A00, so the DIR32 consistency check
passes without the record; the canonical-name record line is a deferred
follow-up for a full-gate green window (the proposal would then include the
name; one-line `dir32_record.py record` commit).

Steps 7-8 completed: pass-test PASS, rebase onto c4a7c4b2c9 (which also fixed
3 of the 11 unrelated names — upstream had recorded
?cantConnectBeforeOnline@@3EA, ?mustDownloadPatch@@3EA and
?s_asyncDNSLookupInProgress@@3EA at 0x012F716D/0x012F716C/0x012F717A),
scoped re-verification on the rebased tree, commit, push.

Eight of the unrelated names remain open at c4a7c4b2c9 (all unrecorded in
origin's dir32_addresses.csv, none baselined; full-gate red until repaired):
??_7Waypoint@@6B@ 0x0109C3DC (vtable owned by the matched Waypoint
ctor/dtor rows), ??_7ParticleInfo@@6B@ 0x0110FE78 (vtable owned by the
matched ParticleInfo rows), ??_7BfmeHolderCU@@6B@ 0x0111126C (14 names
already recorded at the VA; the BfmeHolderCU spelling unrecorded),
??m_curFadeFrame@ScreenCrossFadeFilter@@1HA@@3HA 0x0130720C (matched data
row under the near-spelling ?m_curFadeFrame@ScreenCrossFadeFilter@@1HA),
?nShadowDecalVertsInBatch@@3HA 0x01306E20, ?d_008c66a0/d_008c6ad0
0x00CC66A0/0x00CC6AD0, __fmode 0x0134FBAC.

## Ruled out

- Recording the STLport name alone (the guard refuses it while the base holds the
  game names; a data row alone does not clear it — the "already recorded" branch
  fires first).
- A byte-true reconstruction of the `_M_get_num` body to drop the STLport
  reference: the body is already matched via the applicable vendored template, so a
  reconstruction is not warranted (AGENTS.md escalation ladder, step 4).
- Forcing a rename or a gate/tool change to bypass the guard (weakening
  verification — forbidden).

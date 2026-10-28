# 0x00504600 ?WOLMapSelectMenuSystem@@YA — topup-2 investigation (2026-10-28)

Claim: `0x00504600=5f99c8961b694bcfb9420bfdc56e33c5`. Result: BLOCKED, no commit.
Stash `targets/game/reverse/attempts/0x00504600.cpp` (score 0.5117, 2026-10-21)
re-verified via probe: 1372/1372B exact size, 670 non-reloc diffs, 18 structural
diffs, shape 0.963. First divergence at +00fb. No improvement banked.

## Donor evidence (NEW, recorded here)

- Donor revision: `inputs/reference/open-bfme-2` @ `beed8a16790a6812231ac7b05e3e6893e4cb5d1`.
- NO BFME2 counterpart exists: `rg WOLMapSelectMenuSystem` over
  `inputs/reference/open-bfme-2/reverse/functions.csv` and `Code/` returns
  nothing (only unrelated mentions of WOLMapSelectMenu in GameSpyOverlay /
  WOLGameSetupMenu). Closest usable evidence is the already-landed BFME1
  sibling `game/.../Menus/WOLMapSelectInitialize00503FA0.cpp` (same ByRef
  populate wrapper, same TU-local vtable views). Donor lane inapplicable.

## Retail facts established this session (all from `dis_retail.py`)

- Radio branches call the 4-arg cdecl map-list filler with the getMap() hidden
  temp: `lea ecx,[esp+0x1c]; push ecx; mov ecx,[TheGameSpyGame]; call getMap`
  then `push eax(temp) ; push 1; push 1; push edx(mapList)`,
  `mov [state],3`, `call j_00029cee`, `add esp,0x10`, `lea ecx,[esp+0x1c]`,
  `mov [state],-1`, `call releaseBuffer@BFMERetailAsciiString`. The stash's
  ByRef-wrapper call sequence matches this exactly (temp pointer pushed,
  caller destroys via releaseBuffer). Keep the wrapper; a by-value form is
  refuted by the push pattern (history #8 concurs).
- The three unknown callees are all MATCHED rows, not ABI risks:
  `j_00028a01` -> `?setUsesSystemMapDir@CustomMatchPreferences@@QAEX_NZ`
  (0xADB60, non-virtual, direct call with pushed FALSE/TRUE);
  `j_00030495` -> `?write@UserPreferences@@UAE_NXZ` (0xA9F60, VIRTUAL but
  retail emits a DIRECT `call`);
  `j_00041f6a` -> `??1CustomMatchPreferences@@UAE@XZ` (0xAAFB0 dtor, direct).
- `j_0000b0f5` -> real `??0CustomMatchPreferences@@QAE@XZ` (0xAB7F0); the
  `?forward@CustomMatchPreferencesCtorThunk` symbol is only the ILT-slot pin
  name, so a probe `!!` on that call target is a naming artifact, not a body
  divergence (same mechanism the landed sibling relies on).

## Variants tried (probe, all vs 1372B/670-diff baseline)

1. `throw()` EH levers via `eh_levers.py` + `shape_search.py --max-trials 40`:
   one generated choice is invalid C++ (`AsciiString(...) throw()` on a ctor
   call at line 275, compile error); 9 trials, ALL score 0.5117 identical.
   `throw()` is inert on this body. (Note: `eh_levers.py` output needs its
   `[eh_levers: ...]` header line stripped before `shape_search.py` accepts it.)
2. `((UserPreferences&)pref).write()` -> `pref.UserPreferences::write()` and
   -> `pref.write()`: both 1405B/748 diffs (REGRESSION). The retail direct
   `call write` mechanism is still unexplained (virtual in every visible
   header), but it is downstream of the first divergence; do not chase it first.
3. `if (selected >= 0)` -> real-source `if (selected != -1)` (buttonOK branch;
   matches both in-tree source AND retail `cmp eax,-1` at +01e8): 1379B/724
   diffs (REGRESSION, branch-cascade). Kept OUT of the stash, but recorded:
   the real source form costs 7B elsewhere, so a compensating delta is still
   missing. Revisit AFTER the +00fb divergence is fixed.
4. Named-temp diagnostic (`AsciiString systemMapName = ...getMap();` + pass
   lvalue): 1412B/766 diffs, frame 0x34, and state stores stay register-form
   (`mov ebx,3; mov [slot],ebx`, `mov byte [slot],4`). REGRESSION, reverted.
   Proves the hidden-temp form is correct (retail state 3 + inline
   releaseBuffer) and that the imm-vs-reg state-store materialization is NOT
   temp-specific.

## The +00fb divergence (the whole task, 3x repeated)

Retail: `add esp,0x10; lea ecx,[esp+0x1c]; mov [esp+0x4c],-1; call releaseBuffer`.
Ours: `or esi,-1; add esp,0x10; lea ecx,[esp+0x1c]; mov [esp+0x4c],esi; call
releaseBuffer`. ESI is otherwise dead in ours (only pushed/popped), so MSVC
materializes the -1 state value in a dead register instead of the immediate
store. Repeats at +0168 (user branch) and +01a5 (pref-dtor state reset).
Frames are identical (`sub esp,0x38`), all surrounding code matches. Cause
unknown: not `throw()` (trial 1), not the write dispatch (trial 2), not temp
naming (trial 4). Suspects for the next agent: the exact getMap/static-type
expression (a differently-typed `TheGameSpyGame` changes hidden-temp EH
funclets), or the `populateMapListboxByRef` inline-cast call (declare the
callee with a real prototype instead of the cast-through-`extern void`
indirection and compare).

## Recommended next steps

- Fix +00fb first (it is the first of 18 structural diffs; everything
  downstream, incl. the write()-dispatch shape, sits behind it).
- Then re-try `selected != -1` (trial 3): it is source-true and matches retail
  `cmp eax,-1`, and its 7B cost must be absorbed by the +00fb fix.
- Keep donor lane closed for this symbol; keep the ByRef wrapper.

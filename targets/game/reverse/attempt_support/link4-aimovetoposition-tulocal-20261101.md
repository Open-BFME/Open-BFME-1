# Link queue #4: aiMoveToPosition wrong emitter, TU-local removal (s30b)

Queue: `?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z`,
wrong_selected, 1,123 B, census bb53b24f2b. Prior handoff
`link4-aimovetoposition-scriptactions-20261101.md` proved ScriptActions.obj is
the only wrong emitter (142 B ZH-shaped COMDAT from the aicommandoutofline
shim inline) and reached 125/127 on the caller via a shim edit.

## New: TU-local emitter removal, object-verified

Instead of editing the shared shim (10+ dependent TUs, full gate), neutralize
the inline in ScriptActions.cpp only, following the file's existing
findSpecialPowerTemplate/getAI macro pattern:

```cpp
#define aiMoveToPosition(a, b) aiMoveToPosition(a, b); void zhInlineAiMoveToPosition(a, b)
// ... includes ...
#undef aiMoveToPosition
```

Object proof (`build/match/...script^actions.obj`): the symbol is no longer
DEFINED, and remains an undefined external, so the TU's two calls
(doNamedMoveToWaypoint 0x00300610, unmatched doCreateReinforcements) bind to
retail's 0x000D86C0. `zhInlineAiMoveToPosition` is never emitted (uncalled).
No other matched row in the TU calls it (168/169 rows still verify).

## Caller: still 125/127, residue is one temp register

Best caller body is unchanged from the prior handoff (volatile x/y/ai/z
interleave). Residue at +0x6a/+0x6e: retail `lea ecx,[esp+0xc]; push ecx`,
ours `lea eax,[esp+0xc]; push eax`. Shape 1.000.

Exhausted this session (each kept the upstream 107 bytes identical, none
flipped the lea; full-TU probes via probe.py/rotation_sweep.py):

- `rotation_sweep.py` singles (14 toggles) and `--pairs` (102 toggles): no
  toggle moves a byte.
- Guard respells, single and combined: `if (theObj)` / `if (theObj != NULL)`,
  `if (!way)` / `if (way == NULL)`, `if (!aiUpdate)` / `if (aiUpdate == NULL)`.
- Call-site spellings: `(const Coord3D *)&destination[0]`, qualified
  `aiUpdate->AICommandInterface::aiMoveToPosition`, comma declaration
  `UnsignedInt x = src[0], y = src[1];`, `AIUpdateInterface * const aiUpdate`,
  moved `destination` declaration, `__declspec(noinline)` on the generated
  declaration. `__restrict` is unsupported by this compiler (C4235).
- Ruled out: a TU-local retail-equal inline body. ZH `DamageInfo` (in the
  shim's `AICommandParms`) carries virtuals, so any TU-local view over it
  inlines a fuller dtor chain than the owner's opaque-POD view; the emitted
  COMDAT could not equal retail's 219 B. Composition/placement-new variants
  fail on the explicit dtor call for the same reason.

## Donor

BFME 2 @6584c19741 (`../Open-BFME-2`, verified equal to upstream master):
`reference/shims/zh_outofline/GameLogic/AI.h:467` declares aiMoveToPosition
out of line (commit 0a4a424646, Oct 10). Confirms the approach family; no
transferable lever for the BFME 1 caller residue (different retail).

## Next

Untried: folded-temp spellings that move the rotation pointer without
changing bytes (e.g. a `p->m++`-style folded temp upstream), or a
TU-local volatile-qualified `BfmeObjectModules` accessor for the m_ai read
(verify all TU rows: the class is shared). Verdict: `blocked` on
0x00300610 (candidate 125/127 = 0.984; no stash since the row is matched
and the TU exceeds the bank size cap). To resume: apply the macro hunk
above to ScriptActions.cpp plus the caller body from the prior handoff
(volatile x/y/ai/z interleave, `destination[3]` stores, `!aiUpdate`
check), then attack the +0x6a/+0x6e lea register.

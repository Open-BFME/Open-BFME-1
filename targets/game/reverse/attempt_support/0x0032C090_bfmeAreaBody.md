# 0x0032C090 ScriptConditions::bfmeAreaBody (700 B) — bank 0.9886

Session a1 s503 (2026-10-31, model=claude-opus-5-5). Stash:
`targets/game/reverse/attempt_support/0x0032C090_bfmeAreaBody.cpp.txt` (compiles; 700/700 B, 8 non-reloc diffs).

## Evidence
- BFME 1 target: caller `bfmeAreaGate` 0x0032C400 (matched,
  `BfmeScriptCondAreaGate.cpp`) calls it through ILT 0x0000C586 with
  (a, b, c) and its symbol `?bfmeAreaBody@ScriptConditions@@IAE_NPAVParameter@@00@Z`
  is unresolved in the link queue (#472) — landing this body fixes that link.
  First arg is used as a Condition (customData +0x44, customFrame +0x48).
- Layout/class views: copied from the matched sibling
  `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032ABC0.cpp`
  (volatile `BfmeOverride` template pointer => one `[esi+4]` reload per kind test,
  direct member calls `isInside`, `getEachPlayerFromMask`, `unidentified_0034DB40`,
  PlayerTeamNode list walk, BfmeTeamIterator).
- BFME 2 donor (open-bfme-2 b5a7b8290a): `ScriptConditions::evaluateSkirmishPlayerHasUnitsInArea`
  in `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp`
  has the same member walk (four kind exclusions, isInside, status bit 0, kind 25).
  BFME 1 differs: the cache test is inside the player loop and `-1` continues.
  Kind masks in BFME 1: [0xd0]&0x01000000, [0xd8]&0x20, [0xd8]&0x00800000,
  [0xdc]&0x2000, [0xc8]&0x02000000 — written as explicit word/mask tests
  (`isKindOf(n)` and a template bit test both compile to `shr/test`).

## Progress
- old bank 0.31 (did not compile any more) -> 0.81 (STL list + PMF union views)
  -> 117 diffs (sibling views; `if (!pObj) continue;` removes an extra test)
  -> 8 diffs with `_ReadWriteBarrier()` before `Int count = 0;` (or before the
  end `setCustomFrame`, or a volatile re-read of TheScriptEngine there): without
  it VC7.1 hoists `mov edi,[TheScriptEngine]` above the customData `je` and keeps
  it to the end block on the empty-team-list path (retail reloads).

## Remaining 8 bytes (+0xA2..+0xCD)
retail: customData ECX, TheScriptEngine ESI, frameA EDX, customFrame EAX.
ours:   customData ESI, TheScriptEngine EDX, frameA ECX, customFrame EAX.

## Ruled out (all still 8 diffs, or worse)
nested if / customData local / `if (Int d = ...)` / switch on customData /
-1 and 1 order swapped (12) / `!=`-else form / goto label / Bool useCache local /
`!(a > f)` forms / frame local (441) / reversed `>=` operands (441) /
engine local (432) / inline cache helpers (free, ScriptEngine member, engine param) /
engine getters non-const, Int, by-reference (440) / direct field access on engine (440) /
volatile frame fields / volatile customFrame (433) / do-while and for(;;) loops /
player null as if-block / count and pPlayer declared at function top /
barrier at 5 other positions / Parameter* first arg + Condition cast.
Next ideas: something else in retail that blocks the TheScriptEngine PRE
naturally (would also change RA); compiler-flag sweep on the TU.

## s509 (claude-opus-5-5): still 8 diffs
- Flags on the bank TU: /Ob1 /Ob2 /G6 /GX /Ox inert (8); /G7 315, /Os 369, /Oy- 503.
- The barrier can be replaced by the dir32-recorded alias `?TheBfmeGlobal_012f076c@@3PAVBfmeGlobal_012f076c@@A`
  (same 0x012F076C) in either the cache test or the end `setCustomFrame` read: same 8 diffs, so the
  PRE hoist and the customData/engine register rotation are independent.

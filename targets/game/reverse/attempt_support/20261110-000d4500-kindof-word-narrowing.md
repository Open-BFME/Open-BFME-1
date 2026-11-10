# 0x000D4500 Rva000D4500CastleSearchCallback: load-narrowing residue

> `build/wf/000d4500/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x000d4500.cpp`.

Target `?Rva000D4500CastleSearchCallback@@YAHPAVObject@@PAX@Z`, 273 B.
The current ledger row is still `?d_000d4500@@YAXXZ` (gen_asm). Flags are unchanged from
the bank: `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source`, stlport.

## Status

- The bank `targets/game/reverse/attempts/0x000d4500.cpp` still reproduces as logged: 273/273 B,
  17 relocations, 3 non-relocation bytes (see `build/wf/000d4500/base.cpp`).
- Remaining mismatch at +0x37 and +0x3D:
  ```
  retail: 8b 80 c8 00 00 00  mov eax, dword ptr [eax+0xc8]  | ours: 8a 88 c8 00 00 00  mov cl, byte ptr [eax+0xc8]
  retail: 84 c0              test al, al                    | ours: 84 c9              test cl, cl
  ```
- **Mechanism found (new).** MSVC 7.1 narrows `mem32 & 0x80` to a byte load when the
  load has one use. Retail's dword load means the load had two uses when narrowing ran,
  so it was CSE'd into a register. A later pass then removed the redundant second test.
  This diagnostic source is **EXACT** at 273 B with 17 relocations:
  `build/wf/000d4500/diag_exact_redundant_test.cpp`
  ```cpp
  const ThingTemplate *tmpl = obj->getTemplate();
  unsigned int w = tmpl->m_kindof[0];
  if( !(w & 0x80) && !tmpl->isKindOf( KINDOF_STRUCTURE ) && !obj->isKindOf( KINDOF_BASE_FOUNDATION ) )
      return 1;
  ```
  It is not landable. The second STRUCTURE test is redundant and would count as a dummy
  statement. It proves only what the IL needs. To land, we need a natural EA-style source
  that reads the kind word twice with the first read in a named word local. Order matters:
  local first, then a direct/inline read.

## Measured narrowing rules (isolated probes in build/wf/000d4500/)

These are measured effects; the causes are hypotheses.
1. In the same retail TU (Player.cpp), `Player::ungarrisonAllUnits` (0xD9180) emits the byte
   form after the identical getFinalOverride join. So flags/TU are not the lever.
2. Retail-wide scan: the `mov r32,[..+0xC8]; test r8l,r8l; js` form occurs only at 0xD4537
   and 0x3E8F61. Both are EH functions with a function-static NameKey. 25 byte-form sites
   are mostly non-EH.
3. A matched TU keeps the dword form: `Rva226800RemoveContain.cpp` at 0x226865, with
   `UnsignedInt kindOf = thing->m_kindOfAtCC; if ((kindOf & 2) != 0)`.
   - Bisecting its body: the dword form survives only when the test's then-block contains a
     static-local EH region **and** the join after it has a call or a branch (`rcF2`, `rcH3`,
     `rcK*`, `rcQ*`).
   - Diag `vDWI4` reproduces this in the d4500 TU: a uint local, W-form
     `if ((kindOf&0x80) || isKindOf(BASE)) { static...; } call();`.
   - Inline `isKindOf` in that W-form still narrows (`vDW`).
   - This rule cannot explain retail. Retail's false path returns straight to the epilogue.
4. A Bool local of the test (`vJ1`, `vK1`, `vM1`) avoids the narrowed load but is stored to
   the stack (`shr eax,7; and al,1; mov [esp+..],al`), giving 281 B.
5. Two reads of the same word, the first in a named local, give EXACT (`vN2`, `vN8`, `vP4`).
   These variants still narrow:
   - two direct reads (`vN5`)
   - local used twice (`vN4`)
   - inline read first, then the local (`vP3`, 156 diffs)
   - a dead second read (`vP1`)

## Ruled out this session (all still 3 diffs unless noted)

- **Negative vs positive nesting:** U1 form, else-return form (`vE1`/`vE2`, with and without
  uint local), and a matrix over inline/uint-local/tmpl-local x search-at-top/after x
  negative/positive (`gen1.py`, 12 variants).
- **Static placement:** block-scoped static, castle predeclared (`vL1`-`vL4`).
- **Static in a helper:** inline helper holding the static. VC7.1 will not inline a function
  with a static local, even `__forceinline` (195 B).
- **Inline candidate predicate:** `vWH1`-`vWH3`.
- **Bool/uint locals:** `vK*`, `vM*`.
- **Flag threading:** `vT1`, 13 diffs.
- **Extra constant uses:** extra 0x80/1 constant uses in the body (`vR*`, `vM*` diag).
- **Non-polymorphic Overridable view:** `vD`.
- **Prior sessions (still valid):** volatile reads, bitset/word helpers, shifts, casts,
  bitfields, /G5-/G7, /Ox, /Os, /O1.

## Donor search

- BFME 2 (`inputs/reference/open-bfme-2` @ 2bac16a65): no corresponding callback. It has
  `CastleMemberBehaviorFind.cpp`, a static-key finder that is out of line in BFME 2, and
  `PlayerDoFindCommandCenter.cpp`, a different callback.
- Zero Hour `Player.cpp` has no castle search.

## Next step

Look for a natural spelling with two reads of `m_kindof[0]` before any call. For example, an
EA BitFlags/KindOf helper that copies the word into a local and then calls `test()`, or an
`isKindOfMulti`-style mask check. Probe each one against the rule in item 5.

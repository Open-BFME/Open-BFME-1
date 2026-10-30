# 0x001E65C0 WeaponTemplate::getAimPosition: frame-slot residue (2026-10-30)

Bank: `targets/game/reverse/attempts/0x001e65c0.cpp`, 444/444 B, 34 non-reloc
bytes, score 0.923 (previous bank 411 B / 211 diffs, 0.52). Model claude-opus-5-5.

## Evidence

- BFME 1 target: boundary RET 0x10 at +0x1B9, INT3 at +0x1BC. The matched caller
  `Weapon::bfmeGetLOSVictimPos` fixes the ABI and the reloc-derived name.
- BFME 2 donor (inputs/reference/open-bfme-2 at 20a0cb6173, path
  `Code/GameEngine/Source/GameLogic/Object/WeaponTemplateTargetPositions.cpp`,
  `adjustTargetPositionOnVictim` 0x002CAB3A, byte-exact in BFME 2) supplied the
  structure: the random value is an inline argument of
  getWorldspaceBestContactPoint, the height adjustment runs only on the
  non-flag path, and a volatile pos.z read keeps the outer arm separate. These
  are donor-derived shape choices that BFME 1 bytes confirm. The donor uses SSE;
  BFME 1 uses x87.
- Compiler: `/DNDEBUG /MD /EHsc`, WWLib `ascii_string.h`, plus a TU-local inline
  `StringBase<char>::isNotEmpty` specialization (the same pattern as
  AttachmentTransform007629F0.cpp).

## Residue

Every instruction matches except the frame displacements. Retail uses
`sub esp,0Ch`. It puts the AsciiString in the dead `victim` argument slot
(+16) and zDelta in the dead `weaponSlot` slot (+20). Our build gives zDelta
+16, gives the string a frame slot (-28), and uses `sub esp,10h`.
`/FAsc` shows the slot table: add `/FAsc /Fa<path>` to the cl line.

## Measured slot behaviour (all variants run on the bank)

- The string wins +16 (and zDelta moves to +20) only when the string has more
  final-code references. Two cases do this: an out-of-line `isNotEmpty` call
  (+1 lea), or an extra `return` with its own destructor site in the flag
  branch (e1/e4/e5). Both change the code: +13 B for the call, +48 B for the
  return, because the tail is duplicated instead of jumping to retail's
  0x17F join.
- The slot did not move with any of these: IL-only extra string uses
  (`isNotEmpty() && isNotEmpty()`, `(void)&s`, a cast to a const reference),
  a const string, a const-reference binding, direct-init, block-scoping the
  string, zDelta at function, block or split-declared scope (before or after
  the string), const/register zDelta, passing zDelta through a forceinline
  helper by value (it becomes `$T` and still takes +16), a ternary clamp, a
  Bool clamp local, an inverted condition chain, an inverted flag test (+47 B),
  or a local copy of victim.
- Retail's counts are the same as ours (string lea/mov/lea plus the unwind
  lea; zDelta has 4 references), so the tie-break is not the plain final
  reference count. Untested hypothesis: the weights are scaled by block
  frequency, which source structure changes and this code shape does not.

## Next step

Find a spelling that gives the string one more reference in a block that
cross-jumps into the 0x17F join, or that lowers zDelta's weight, without
changing the code. A `return` in the flag branch whose copy and destructor
tail-merge with the main tail would do it. The e1 variant failed only because
the duplicated tail used different registers (eax/ecx instead of ecx/edx).

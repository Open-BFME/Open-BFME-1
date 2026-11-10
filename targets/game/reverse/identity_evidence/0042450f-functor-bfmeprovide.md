# Functor target at 0x0042450F is bfmeProvide, not a LoadScreen method

`??0LoadScreen0051BF30` builds a shown-functor whose method slot retail reads
as VA `0x0042450F` (dir32 debt line for
`?Rva0051B560@LoadScreen0051BF30@@QAEXPAX0_N@Z`).

- RVA `0x0002450F` is the 5-byte ILT `?j_0002450f@@YAXXZ`
  (`game/gen_small/gthunks_040.cpp`, matched, `target=0x0051B560`).
- `0x0051B560` is the matched 114-byte
  `?bfmeProvide@Rva0051B560Host@@QAEXHPAD_N@Z`
  (`game/GameEngine/Source/GameClient/GUI/Rva0051B560SlotColorProvide.cpp`).
- The old spelling `LoadScreen0051BF30::Rva0051B560` was never defined and
  carries no ledger row: an undefined external the link resolved nowhere.
  The `LoadScreen0051BF30` class itself is untouched and still used
  throughout `AptLoadScreen.cpp`.

So the functor is rebound to the matched provider body (which the thunk
reaches transparently); `LoadScreen0051BF30` is not renamed and
`Rva0051B560Host` is not a replacement identity for it. The checker's
`LoadScreen0051BF30 -> Rva0051B560Host` pairing is a false pairing of a
rebinding, closed by this note.

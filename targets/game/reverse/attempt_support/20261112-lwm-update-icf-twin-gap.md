# BfmeLivingWorldManager::update (0x006174D0, 369B): ICF-twin strictness gap

## Current verdict (2026-11-12, current objects, fresh RetailTruth)
`?update@BfmeLivingWorldManager@@QAEXXZ` judges `wrong` on exactly ONE reloc:

- `@0x73`: our TU calls its own STLport spelling
  `?begin@...pair<const int,void*>...(PAX)...` (call-site bytes identical to
  retail, 0 non-reloc diffs across all 369 bytes; other 25 relocs resolve).
- Retail's call runs through ILT thunk `?j_00047dc5` (0x00047DC5, E9) to the
  shared int-keyed `hashtable::begin` body at 0x00611610.
- The judge homes our PAX spelling only at 0x000D09C0 (symbols.csv pin 76561;
  `pins()` keeps the FIRST pin per name). `_stub(0x47DC5) = 0x611610`, which is
  not in `{0xD09C0}`, so `_lands` fails.

## Why this is a judge artifact, not a code defect
- The bodies at 0x00611610 and 0x000D09C0 (plus 0xD0900/0xEF5E0/0x33CDA0) are
  BYTE-IDENTICAL 78B (verified by direct image reads). Retail ICF-folded (or
  duplicated) one body; every int-keyed `begin` in the image executes the same
  bytes.
- The PAX-spelling COMDAT family is healthy: 14 definers in current objects
  (LivingWorldManagerUpdate.obj, rva000d74b0 map TU, 12 gen_small fam TUs),
  every copy verdict=retail against the pinned body.
- `link.exe` resolves our call to one of those identical copies; the actual
  link is correct. Only RetailTruth's exact-address `_lands` flags it.

## Ruled-out fixes
- `?j_00047dc5` thunk-call hack: REJECTED. `hashtable::begin` returns its
  8-byte iterator via hidden pointer (`lea eax,[esp+c]; push eax; lea
  ecx,[...]; call`), so the call shape is push+ECX+call. `__thiscall`
  function-pointer casts are refused by the compiler (C4234); the file's
  `__fastcall` single-arg trick puts the hidden pointer in ECX instead of on
  the stack (verified garbled codegen, reverted; tree is pristine).
- Retyping the map to `hash_map<int,Relationship>` (Player.obj's defined,
  20-times-homed spelling): semantically wrong (the map holds object
  pointers, not Relationship enums). Refused.
- Second `route=` pin for PAX through 0x47DC5: REFUSED BY GATE DESIGN.
  `route_verdict`'s E9 arm requires the name in the target body's ledger
  identities; 0x611610 is named `tg_00611610` (+Relationship object-symbol),
  so a PAX route claim is inadmissible ("not a check anyone can write").
- Second functions.csv row naming PAX at 0x611610: would be the 437th
  two-name address (`one_identity.py` tracks 436). Policy decision, not a
  lone-agent call. The existing `tg_00611610` row already covers the address
  under the alias convention.

## Proposed resolution (needs tool/policy owner)
Teach `_lands` (or a narrow ICF-twin rule) that a call target whose body
bytes are identical to an expected home's body bytes is a hit, OR adjudicate
a dual-home for proven ICF twins. Evidence for either is all above; the
`tg_00611610` row + pin 76562 + 14 retail definers corroborate.

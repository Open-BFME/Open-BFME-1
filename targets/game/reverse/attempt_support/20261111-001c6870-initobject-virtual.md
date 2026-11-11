# 0x001C6870 Object::initObject: EXACT (933/933 B)

Workflow session 2026-11-11 (claude-opus-5-5). It starts from the bank
`targets/game/reverse/attempts/0x001c6870.cpp`, which was 6 non-reloc bytes
at +0x171 and reproduces as logged.

Best candidate: `build/wf/001c6870/final2.cpp`. It defines
`?initObject@Object@@UAEXXZ`. The flags are unchanged from the bank:
`/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib` (VC7.1, build
default /O2). `probe.py ... 0x001C6870 --size 933` reports
`result EXACT (modulo relocation slots)`.

## Root cause of the residue
The bank's coupling, a byte-narrowed bit-88 test against the `or edi,-1`
constant register, was a side effect. The real cause is the
`m_lastWeaponCondition` declaration.

- ZH declares `Byte m_lastWeaponCondition[WEAPONSLOT_COUNT]` and initObject
  runs `for (i < WEAPONSLOT_COUNT) m_lastWeaponCondition[i] = WSF_INVALID;`.
- BFME 1 sets WEAPONSLOT_COUNT to 4. The witness is
  `game/GameEngineDevice/.../W3DModelDrawWeaponBarrelValidation0076F9E0.cpp:77`.
  The Xfer at 0x001D48A0 also moves Object+0x2A4 as one 4-byte item.
- VC7.1 unrolls the four `0xFF` byte stores and folds them into one dword
  store. The four uses of -1 are counted before the fold, so -1 earns EDI.
  The `cmp [ebp+0x370], edi` reuses it. This matches the shape_levers rule
  "a store repeated in both arms makes a constant worth a register": a
  constant register with too few visible uses points to merged duplicates.
- With this declaration, the natural `!isKindOf(25) && !isKindOf(88)`
  (UnsignedInt `w & mask`, as in the BFME 2 donor `thingTemplateIsKindOf`)
  gives retail's `test dword [eax+0xd0],0x1000000` and keeps the CSE. The
  bank's `? false : true` workaround is gone.
- A plain STLport `_STL::bitset<256>::test` isKindOf (`// stlport`) is also
  EXACT (`best.cpp`). The raw-word form avoids STLport COMDATs.

## Trials (family / change / result)
- Baseline: the bank reproduces at 933 B with 6 diffs at +0x171.
- (c) types: the natural UnsignedInt isKindOf with `Int m_lastWeaponCondition`
  scored 934 B, 338 diffs, and dropped the -1 CSE. That is the known coupling.
- (d) visibility: STLport bitset::test isKindOf with an Int field gave 934 B,
  338 diffs. It matches the UnsignedInt form exactly.
- (c) layout: `memset(m_lastWeaponCondition, 0xFF, 4)` and `memset(..,-1,4)`
  each gave 934 B, 338 diffs. memset does not count four uses.
- (c) layout: a 3-byte `Byte[3]` loop (ZH count) gave 938 B, 719 diffs. That
  is three byte stores, unlike retail.
- (c) layout: a 4-byte `Byte[4]` loop is **EXACT** with both the bitset and the
  UnsignedInt isKindOf.
- Identity: `ilt_oracle check ?initObject@Object@@QAEXXZ` is CONTRADICTED.
  `?initObject@Object@@UAEXXZ` is CONFIRMED (exact, p_false 3.3e-4). Retail
  Object vtable 0x0109EE58 slot 8 (+0x20) holds ILT 0x00039D79, the only
  reference to the ILT. No direct call reaches the body. Declaring
  thingSlot00..07 plus `virtual void initObject()` (vptr replaces m_pad000)
  stays EXACT.
- Helper COMDAT: an inline `setReceivingDifficultyBonus` without the ZH early
  `if (receive == m_receivingDifficultyBonus) return;` emitted a 53-byte copy
  against the retail 61-byte row 0x001BE7D0. That would be a link loser.
  Adding the early return keeps initObject EXACT and makes the copy EXACT
  (61/61).

## Landing notes (read-only checks; not landed)
a) ilt_oracle: the old QAE name is CONTRADICTED and `?initObject@Object@@UAEXXZ`
   is CONFIRMED. Land under the UAE name with `--replace-rva 0x001C6870`
   (current row `?d_001c6870@@YAXXZ`, gen_asm). symbols.csv has only
   `?b_001c6870@@YAXXZ` (gen-thunk body), and no other ILT pin is needed. The
   present-unmatched QAE definition in Object.cpp:575 must stop claiming this
   identity. Remove it, or keep its marker for the QAE spelling.
b) The emitted helper COMDATs that have their own rows:
   - `getControllingPlayer@Object` 0x001BE3F0 (18 B) is EXACT.
   - `setReceivingDifficultyBonus@Object` 0x001BE7D0 (61 B) is EXACT in final2.
   - The StringBase/AsciiString helpers come from the canonical ascii_string.h,
     shared by about 1389 units.
   Inline helpers without rows (getTemplate, isKindOf, getNumBattlePlansActive
   and others) are __forceinline or trivial. `find_declared_unmatched.py`
   flags only `Object::initObject`.
c) Globals and their recorded names:
   - TheGameLogic 0x012F0898 (data_rows)
   - TheScriptEngine 0x012F076C (data_rows)
   - TheWeaponStore 0x012EF738 (data_rows)
   - TheEmotionSystem 0x012F0878 (dir32 only)
   - TheLivingWorldLogic 0x012F1028 (data_rows)
   - TheExperienceLevelSystem 0x012F0888 (data_rows)
   - TheGlobalWeatherSystem 0x012F0FE0 (data_rows, RetailGlobalWeatherSystem
     type; the bank reinterprets it as BfmeObjectReferenceStore)
   - `?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB` 0x0107388B
     (symbols.csv pin and retail export)
   The literal "RohanSamWithFrodoPowers" at 0x0109EC04 has no data row; it is
   compared by content.
   All 20 call targets resolve to a functions.csv row or a symbols.csv ILT pin
   (bfmeObjectEnteringInfluence pin 0x29875, updateObjectReference pin
   0x1F816).
d) TU: game/GameEngine/Source/GameLogic/Object/Object.cpp is the readable home,
   but it compiles against the ZH/bfmeobjectlayout headers with a
   non-virtual, divergent layout. A split TU is practical:
   `game/GameEngine/Source/GameLogic/Object/ObjectInitObject.cpp` (BFME 2
   donor naming), with the same flags as the bank. Retire the Object.cpp
   present-unmatched copy. The candidate keeps the bank's descriptive names.
   It has no volatile, asm or pragma, and the `// cl:` line is first.

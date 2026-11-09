# 0x001EDCA0 AutoAbilityBehavior::update (1944 B): EXACT

Symbol defined: `?update@AutoAbilityBehavior@@UAE?AW4UpdateSleepTime@@XZ`
Best source: `build/wf/001edca0/best.cpp` (probe: `result EXACT (modulo relocation slots)`, 1944/1944, no misaligned relocation sites).
Compiler: unchanged bank flags `/DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic`, `// stlport`, probe default /O2.

## Baseline
Bank `targets/game/reverse/attempts/0x001edca0.cpp` still reproduces as logged: 1944 B, 66 non-reloc diffs from +0x27B, shape 0.995.
Residue: in the first target loop (`button->m_options & 7` branch) VC7.1 holds two kind-bit masks in callee-saved registers.
Retail: `mov ebx,0x100; mov edi,0x400` (tests 1 and 2 of the 8/10/9/11 `||` chain use `test [eax+0xc8],reg`, tests 3 and 4 use `mov ecx,[..]; test ch,N`).
Bank: `mov edi,0x100; mov ebx,0x800` (tests 1 and 4 enregistered).

## Fix (one statement, donor-guided)
The cooldown delay copies the float into a by-value local inside the guard, as in BFME 2's
`Code/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorUpdate.cpp` (donor rev 2bac16a6):

```cpp
int delay = 50;
const float &delayRef = button->m_17c;
if (delayRef > 0.0f)
{
    float delayScale = delayRef;
    delay = (int)(5.0f * delayScale);
}
```
The bank's `if (button->m_17c > 0.0f) delay = (int)(button->m_17c * 5.0f);` gives 66. The delay code bytes are the same either way. Only the loop-constant register choice changes.
Other spellings that are EXACT: `float delayScale = button->m_17c;` inside the braces, with or without the reference, and `delayScale * 5.0f`.
`delay = (int)(delayRef * 5.0f)` with no by-value local gives 133 diffs.
This is a measured effect. The probable cause is that the extra local changes VC7.1's internal temp numbering, which breaks the tie between equal-weight loop constants. Supporting observation: one use of a second, otherwise equivalent kind-test accessor anywhere in the function also flips the choice to retail, five uses flip it back, and none of these change the instruction stream. That accessor trick was rejected as unprincipled.

## Ruled out (all 66 diffs unless noted)
- Control flow, first loop: nested positive ifs, merged `&&` (both 1908 B/1446); `bool` local for the kind chain; goto chain; `!a&&!b..` chain; `for` header; found-then-act after the loop; else-if chain; do-while (1908 B).
- Branch order: swapped the `options & 7` arms (1925 B) and the `m_180` arms (589 diffs). Layout follows source order.
- Bit order: permutations of 8/10/9/11 always enregister the first and last tests in chain order (cost 66 or 67). The rule is position-based, not value-based.
- Removing the else-loop kind tests changes the choice to tests 3 and 4. This is a diagnostic only: the constant choice is function-wide.
- State bit spellings (`& 0x800`, `(bool)`, `1U<<11`, `unsigned char`, index 203). `int` or `UInt` locals give 1960 B.
- hasKind: signed shift, pointer to the words, `int` return, `UInt` bit. A named `word` local gives 1934 B/1005, the same as the earlier STLport bitset result.
- Static inline helper: not inlined at /O2 (1394 B). The `__forceinline` helper gives 66 (bool or early-return forms).
- Target or iterator scope: shared `Object *target`, and an inline `next()` returning a pointer (66).
- Donor spellings elsewhere: a cached `options` local (66); `buttonFlags` for the >>5 test (1940 B/159, though it showed retail's EBX/EDI choice); a reference for the button range (133); a ternary relationship (1934 B).

## Landing notes (read-only checks; nothing landed)
a. `tools/ilt_oracle.py check` gives CONFIRMED (p_false 3.91e-04, exact) for the update symbol at 0x001EDCA0. The current row `?dup_001edca0@@YAXXZ` (AutoAbilityBehaviorModuleDataDestructorThunk.cpp, object-symbol `??1AutoAbilityBehaviorModuleData@@UAE@XZ`) is the contradicted alias. Re-home it with `--replace-rva 0x001EDCA0`.
b. Helper bodies the TU defines that have their own ledger rows. Each emitted copy probes retail-identical:
   - `??0PartitionFilterPlayerAffiliation@@QAE@PAVPlayer@@H_N@Z` against 0x00160CE0 (39 B): EXACT. Ledger name `?set@Rva00160CE0@@QAEAAV1@HHD@Z`, home `game/GameEngine/Source/Common/Rva00160CE0Set.cpp`. No symbols.csv pin exists for the ctor name.
   - `??0PartitionFilterValidCommandButtonTarget@@...` against 0x001ED510 (46 B): EXACT. Ledger `?set@Rva001ED510@@QAEAAV1@HHDH@Z` (Rva001ED510Set.cpp); symbols.csv pins this ctor name to ILT 0x0003A5AD.
   - `?next@Rva0025ED50WideResult@@QAEPAVObject@@XZ` against 0x000C44D0 (25 B): EXACT. Ledger `?bfmeGoEOF@BfmeThingEOF@@QAEPAXXZ` (BfmeConv881.cpp). No pin for this name.
   Prefer declaring these out of line (pinned or ledger names) over defining noinline copies. The TU also emits inline filter destructors, `??_G` deleting destructors, local vtables and STLport vector destructor COMDATs. Check these against the gate before landing.
   Callee pins that already exist in symbols.csv: `getFinalOverride@BfmePartitionThingTemplate` (ILT 0x22BB), `doCommandButtonAtPosition ... PBUCoord3D` (0x26EF4), `iterate@PartitionManager` (0x9F2960, ledger name `bfmeForwardWideC@BfmeWideForwardC`), `doCommandButton@Object@@QAEXPBVCommandButton@@HH@Z` (0x63CF, a gen_asm dump body), `Thing::isKindOf`, `getVisionRange`, `getControllingPlayer`, `bfmeCanAutoFire`, `intersects@Rva001ED9A0Mask`, `findCommandButton`, `PartitionFilter::link`, `StringBase<char>::set`.
c. Globals and data the body references:
   - `?TheControlBar@@3PAVControlBar@@A` 0x012F33F8 and `?ThePartitionManager@@3PAVPartitionManager@@A` 0x012ED5B8 (data_rows and dir32).
   - Vtables in dir32: `??_7PartitionFilter@@6B@` 0x01083B5C, `??_7Rva0025ED50ObjectFilter@@6B@` 0x01085DD0, `??_7Rva0025ED50RootFilter@@6B@` 0x01083B80, `??_7Rva00260180SelfFilter@@6B@` 0x01095724, `??_7PartitionFilterPlayerAffiliation@@6B@` 0x0109689C, `??_7PartitionFilterValidCommandButtonTarget@@6B@` 0x010A1A5C.
   - `??_7ObjectFilter010956B0@@6B@` has no record. 0x010956B0 is recorded as `??_7BfmeObjEQT@@6B@`, `_bfmeVftBfmeObjEQT` and the disputed `??_7DistLODPrototypeClass@@6B@`. Rename the class to `BfmeObjEQT`, or settle the dispute first.
   - Empty string 0x0107301C (`?g_Rva0107301CEmptyString@@3QBDB` and others). 0.0f 0x01075350 (several names). 5.0f at 0x01075344 and 0.8f at 0x01096EC0 come in as `__real@` constants.
d. Home TU: tu_map row 0x001EDCA0 names `game/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehavior.cpp` (official path). That file's `// cl:` is `/DNDEBUG /MD /EHsc` with no stlport, so either reconcile its declarations or use a dedicated sibling such as `AutoAbilityBehaviorUpdate.cpp` (the BFME 2 donor's filename) with the bank flags. Rerun the scoped byte gate there, because the register choice is sensitive to TU-level temp numbering.

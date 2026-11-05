# 0x005369A0 BfmeAptScreenOnlineChat slot-4 message handler (821 B): EXACT via probe

Symbol: `?rva005369A0@BfmeAptScreenOnlineChat@@UAEHPAVGameWindow@@III@Z`
Best source: `build/wf/005369a0/best.cpp`. probe.py reports `size ours=821 retail=821 relocs=38` and
`result EXACT (modulo relocation slots)`.
Compiler: the bank's unchanged cl line `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.`. The canonical
`game/Libraries/Source/WWVegas/WWLib/ascii_string.h` and `unicode_string.h` headers are used.

## Residue in the bank (reproduced: 821 B, 6 non-reloc diffs at +0x1A6..+0x1AB)
Retail: `8B CC` `mov ecx,esp`, then `89 64 24 34` `mov [esp+0x34],esp`.
Bank: the same two instructions in the opposite order. This is the by-value AsciiString copy for
`TheGameText->fetch(label)` in the `column == 0` arm.

## Cause (measured)
- A retail-wide scan of `.text` for the saved-ESP/`mov ecx,esp` pair before a call to
  StringBase<char> copy 0x887B60 finds 1378 sites in esp-first order and only 10 in ecx-first order.
  The scanner is `build/wf/005369a0/scan.py` and `scan2.py`.
- `setGroup` 0x0048AD80 is matched (`GameWindowTransitionsHandler.cpp`) and has one site in each
  order. Its ecx-first site is a cross-jumped tail. The function's final
  `m_currentGroup = findGroup(groupName); if (...) init();` merges into the identical sequence in
  the `immediate` branch. Removing either copy (the `no_init1` and `no_tail` scratch variants under
  `build/wf/005369a0/sg/`) turns that site esp-first. Changing the lea register, adding a named
  local, or removing a preceding call did not change the order.
- In retail, the `column == 0` arm's `jne; push A; jmp; push B; call operator=` also points to a
  cross-jumped merge of two complete arms. The original source repeats the tooltip call in each branch:

```cpp
AsciiString label;
if (GadgetListBoxGetItemData(list,row,1) == (void *)1) {
    label = "TOOLTIP:FellowshipIcon";
    TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
} else {
    label = "APT:NULL";
    TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
}
m_unusedName = label;
```
With this change, VC7.1 merges both arms after the `push` of the literal and produces retail's ecx-first pair.
The other 815 bytes are unchanged.

## Checks done
- Relocation names: the +0x1AD copy is `??0?$StringBase@D@@AAE@ABV0@@Z` (retail 0x887B60), not
  the AsciiString constructor at 0x0005EE50 that an earlier masked-only alias produced. All 38
  relocations have the bank's names. This was read from the object with
  `build/wf/005369a0/relocs.py`.
- The `.xdata$x` unwind map is byte-identical to the bank's: 4 states with predecessors
  -1,-1,-1,2.
- `tools/callees.py 0x005369A0 821`: all 15 targets have ledger names, and the bank's declarations
  are unchanged.

## Trials (build/wf/005369a0/trials.tsv)
| family | change | result |
|---|---|---|
| a control flow | ternary `label = cond ? A : B` | 820 B, 330 diffs |
| b lifetime | `const char*` key local then assign | 820 B, 330 diffs |
| b lifetime | item-data `void*` local | 6 diffs (unchanged) |
| b lifetime | named UnicodeString for fetch result | 854 B |
| f rotation | `tools/rotation_sweep.py` (22 toggles) | none better than 6 |
| a cross-jump | duplicate tooltip and `m_unusedName` assignment in both arms | 895 B (the assignment does not merge) |
| a cross-jump | **duplicate tooltip call only in both arms** | **EXACT** |

## Remaining before landing (not done here; sandboxed)
Before landing, the scoped gate must bind the bank's address-derived helper declarations
`?rva005307B0@BfmeAptScreenOnlineChat@@QAEXVAsciiString@@@Z` (ILT 0x2E1E → 0x5307B0) and
`?rva00536870@BfmeAptScreenOnlineChat@@QAEXXZ` (ILT 0x436E9 → 0x536870), as the earlier
handoffs record. The method name stays address-derived. The candidate replaces the
`game/gen_asm/d_0052bd50.asm` dump row.

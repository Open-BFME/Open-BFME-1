# Datum identity at VA 0x012B829C

Corrected the declaration to `?g_ObfRecord012B829C@@3UBigObfSelectorRecord@@A` and defined it once in `game/GameEngine/Source/Common/BigObfHookWrappers.cpp` with a 40-byte data row. This preserves the existing role and address; it does not claim a recovered EA identifier. The pointer-element spelling is refuted by the constructor's arithmetic use of the selected key and by the initialized values that do not denote readable retail objects.

The verified record occupies VA 0x012B829C through exclusive VA 0x012B82C4. It contains two five-dword groups at offsets zero and 0x14. Each group has four selectable unsigned words and a verified trailing zero word. The mask of three limits runtime selection to four words. This is the repository's existing forty-byte BigObfSelectorRecord shape, including its two zero words; the next record or surrounding bytes are shown in the raw retail probe. No fifth selectable entry is claimed.

Retail constructors read a key with a scale-four indexed dword load, read the seed at base plus 0x14 with the same index, write the seed into the ECX receiver, and multiply the key into an XOR chain over eight receiver words. The receiver is the ECX object; the two stack arguments point to input dwords, and the constructor returns with RET 8. The selector reader has two stack out-parameters, writes one selected dword through each, and returns with RET. Its existing int ** ABI is preserved by explicit bit-preserving casts. These stores target the receiver and caller outputs, not the static record. The absolute-operand scan found no writer to this record and no pointer dereference of a selected value in these users. This scan does not rule out an undiscovered indirect writer.

The section is `.data`. The initial bytes are `0b ec bf e7 cb a9 31 02 0b 1d 23 b0 4b a5 cf 7c 00 00 00 00 0b bc 9f eb cb a9 99 46 0b 0d a7 b0 4b b5 43 24 00 00 00 00`. The compiled definition has no data relocations. The retail image is stripped of its PE base-relocation directory, so absence of those entries is not used by itself to infer a numeric type. The arithmetic consumers establish that contract. The reference search under `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine` found no declaration of these BFME selector objects (`build/rlink/initial-users.txt` and `reference-search.txt`). No Zero Hour name is asserted.

The strict-interior DIR32 audit and data-row overlap audit found no other named datum inside the claimed range. Existing DIR32 spellings and symbols.csv pins are retained. The chosen spelling is already pinned in DIR32 except for the corrected thirty-six-byte type, whose decorated spelling is added beside the old rows. Declaration counts include direct declarations and declaration-producing macro invocations, counting each game file once; the raw lines and bounds are in `build/rlink/prepare-corrections.log`.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?g_ObfRecord012B829C@@3UBigObfSelectorRecord@@A` | 1 |
| `?g_twoBitSelectorRecord012B829C@@3UTwoBitSelectorRecord@@A` | 1 |

| Retail user RVA | Instruction RVA | Retail instruction bytes | Operation |
|---|---|---|---|
| `0x0058F530` | `0x0058F545` | `8b0c85b0822b01` | `mov ecx, dword ptr [eax*4 + 0x12b82b0]` |
| `0x0058F530` | `0x0058F54E` | `8b04859c822b01` | `mov eax, dword ptr [eax*4 + 0x12b829c]` |
| `0x00590A70` | `0x00590A87` | `8b0c959c822b01` | `mov ecx, dword ptr [edx*4 + 0x12b829c]` |
| `0x00590A70` | `0x00590A8E` | `8b1495b0822b01` | `mov edx, dword ptr [edx*4 + 0x12b82b0]` |

A retail consumer that dereferences an undecoded selected word as a pointer, indexes a fifth selectable entry, writes to an internal field with an incompatible type, a named datum inside the extent, or any changed verified instruction would refute this correction. The 0x012B7ABC correction is additionally refuted if the neighboring string-pointer table does not begin at 0x012B7AE0.

Raw image bytes, section details, surrounding bytes, complete user disassembly and every initial-ILT five-byte E9 chain to these users are in `build/rlink/retail-probe-v3.log`. Validated data operands and caller instructions through those proven routes are in `build/rlink/focused-retail.log`. The byte, sizeof and relocation gate is `build/rlink/add-data-012b829c.log`. Source byte gates are `build/rlink/build-BigObfHookWrappers-final.log`, `build-Q3SelectorRecordReaders.log` and `build-R3SelectorRecordReadersEbp.log`; ledger, pin and declaration gates are `check-csv-final.log`, `pin-consistency-final.log` and `declared-unmatched-final.log`. LINKED bytes and unrelated blockers are in `link-before.log` and `link-after-final.log`.

The new numeric initializer words are written as unsigned decimal constants. The raw bytes above remain the hexadecimal evidence. This avoids misclassifying numeric seeds as hard-coded image addresses in the source-text linking preview. `build/rlink/normalize-initializers.log` records the representation change and the unchanged address-literal gate result; `build-BigObfHookWrappers-final.log` re-verifies every owned data row and function after it.

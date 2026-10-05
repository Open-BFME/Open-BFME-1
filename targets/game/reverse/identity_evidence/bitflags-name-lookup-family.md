# Retail BitFlags name-lookup family

The queried bodies are 71-byte static cdecl name lookups. The corrected template arguments are 6, 29, 304, 86, 116, 11 and 10 for the rows identified below. RVA 0x001C0870 remains unresolved because its eleven-entry disabled table is distinct from the independently measured eleven-bit armor table. Table length alone does not establish an exact template width when two owners would require the same static member at different addresses.

The hash-bound retail image is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`, image base 0x00400000. Raw retail bytes, instruction-boundary disassembly, every pointer and string, and the exact five-byte ILT jumps are in `build/rlink/bitflags-1791157403/retail-probe.log`; the reproducible probe and machine-readable facts are beside it. `table-analysis-final.log` contains table-range ledger checks and Zero Hour comparisons.

## Receiver and argument contract

There is no receiver. The lookup pushes EBX, EBP, ESI and EDI; its sole `const char *` input is then at `[esp+0x14]`. It reads the first table pointer through `A1 <table VA>`, then scans four-byte pointers until null. Each name is compared through the `_strcmpi` import at VA 0x0135933C. EAX returns the zero-based table index or -1. Verified callers push one pointer and clean four bytes after the call. The bit setters preserve their separate receiver in ESI and use the result as an index. No wrapper, inheritance or forwarder is introduced.

## Per-row retail facts

| RVA | Former ledger identity | Table VA | Count | First name | Last name | ILT RVA | Corrected instantiation |
|---|---|---|---:|---|---|---|---|
| 0x0020E380 | `?getSingleBitFromName@?$BitFlags@$0HE@@@SAHPBD@Z` | 0x012A68D8 | 11 | VETERAN | AS_TOWER | 0x00031246 | BitFlags<11> |
| 0x001C0870 | `?getSingleBitFromName@?$BitFlags@$0ED@@@SAHPBD@Z` | 0x012A9200 | 11 | DEFAULT | DISABLED_SCRIPT_UNDERPOWERED | 0x0000B1AE | Unresolved |
| 0x001C08D0 | `dup_1c08d0` | 0x012AD6B0 | 29 | VETERAN | WEAPONSET_ONE_RING_MODE | 0x000052CC | BitFlags<29> |
| 0x001C0930 | `dup_1c0930` | 0x012A6918 | 304 | TOPPLED | EMOTION_UNCONTROLLABLY_AFRAID | 0x000190F1 | BitFlags<304> |
| 0x001C09C0 | `?getSingleBitFromName@?$BitFlags@$0CN@@@SAHPBD@Z` | 0x012A6670 | 86 | DESTROYED | BUILD_BEING_CANCELED | 0x00026A3F | BitFlags<86> |
| 0x001C0A30 | `?getSingleBitFromName@?$BitFlags@$0N@@@SAHPBD@Z` | 0x012A8D40 | 116 | SPECIAL_INVALID | SPECIAL_HARVEST | 0x0004B218 | BitFlags<116> |
| 0x0037A9D0 | `?getSingleBitFromName@?$BitFlags@$0HF@@@SAHPBD@Z` | 0x012A687C | 10 | TAUNT | ALERT | 0x000448AF | BitFlags<10> |
| 0x0037AA30 | `?getSingleBitFromName@?$BitFlags@$0CG@@@SAHPBD@Z` | 0x012A6858 | 6 | BACK_AWAY | QUARREL | 0x000070A9 | BitFlags<6> |

### RVA 0x0037AA30

The table has 6 names followed by null at VA 0x012A6870. Its verified pointer extent is 28 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a6858.bin`.
Caller `?parseEmotionAIType@Rva0037AD60@@SAXPAVINI@@PAX1PBX@Z` at 0x0037AD60 reaches this body at 0x0037AD73. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
No exact Zero Hour name-table counterpart was found. The EmotionType and EmotionAIType families are established by their retail parser exception strings and the routed callers rather than by inventing a Zero Hour enum.

### RVA 0x001C08D0

The table has 29 names followed by null at VA 0x012AD724. Its verified pointer extent is 120 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012ad6b0.bin`.
Caller `?bfmeSet@Gen_001C4020@@QAE_NPAX@Z` at 0x001C4020 reaches this body at 0x001C4028. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_005c50b0` at 0x1C50B0 reaches this body at 0x001C520F. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/BitFlags.cpp` defines `ArmorSetFlags::s_bitNameList`. The unpreprocessed source lists 8 strings and shares the first 4 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/WeaponSet.cpp` defines `WeaponSetFlags::s_bitNameList`. The unpreprocessed source lists 17 strings and shares the first 4 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
The address-derived ledger name `dup_1c08d0` is retained. Its `object-symbol=` and `dup-of=` notes are corrected to `?getSingleBitFromName@?$BitFlags@$0BN@@@SAHPBD@Z` and the source emits this instantiation explicitly. These are compiler-template object symbols, not claims that this row shares the six-name emotion table or that an independently named canonical duplicate exists.

### RVA 0x001C0930

The table has 304 names followed by null at VA 0x012A6DD8. Its verified pointer extent is 1220 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a6918.bin`.
Caller `?bfmeSet@Gen_001c62b0@@QAE_NPAX@Z` at 0x001C62B0 reaches this body at 0x001C62B8. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_005cb270` at 0x1CB270 reaches this body at 0x001CB3EF. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?iniParseAnim@TransportContain@@SAXPAVINI@@PAX1PBX@Z` at 0x0022CF60 reaches this body at 0x0022CF99. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?iniParseAnim@Rva00268340Contain@@SAXPAVINI@@PAX1PBX@Z` at 0x00268340 reaches this body at 0x00268379. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?doSpecialPower@WeaponChangeSpecialPowerModule@@UAEXI@Z` at 0x0026CF90 reaches this body at 0x0026D032, 0x0026D066, 0x0026D091, 0x0026D0BC. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?parseRiderInfo@Rva0028DDC0RiderInfoParser@@SAXPAVINI@@PAX1PBX@Z` at 0x0028DDC0 reaches this body at 0x0028DE29. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?iniParseAnimAndDuration@SpecialAbilityUpdateModule@@SAXPAVINI@@PAX1PBX@Z` at 0x002A5DE0 reaches this body at 0x002A5E20. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?dispatch@Rva002DECC0Owner@@QAEXIPAVRva001BE220Receiver@@@Z` at 0x002DECC0 reaches this body at 0x002DED1C. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?Rva002E7690LuaValueLookup@@YAHPAUlua_State@@@Z` at 0x002E7690 reaches this body at 0x002E76BF. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?ObjectTestModelCondition@@YAHPAUlua_State@@@Z` at 0x002E77F0 reaches this body at 0x002E7839. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?doSetCounterToNumberObjectsPlayerOwnesWithModelCondition@ScriptActions@@IAEXABVAsciiString@@00@Z` at 0x002F69B0 reaches this body at 0x002F69DF. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_00727260` at 0x327260 reaches this body at 0x00327296. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?d_00606180@@YAXXZ` at 0x00606180 reaches this body at 0x006063C1, 0x00606491. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/BitFlags.cpp` defines `ModelConditionFlags::s_bitNameList`. The unpreprocessed source lists 118 strings and shares the first 15 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
The address-derived ledger name `dup_1c0930` is retained. Its `object-symbol=` and `dup-of=` notes are corrected to `?getSingleBitFromName@?$BitFlags@$0BDA@@@SAHPBD@Z` and the source emits this instantiation explicitly. These are compiler-template object symbols, not claims that this row shares the six-name emotion table or that an independently named canonical duplicate exists.

### RVA 0x001C0870

The table has 11 names followed by null at VA 0x012A922C. Its verified pointer extent is 48 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a9200.bin`.
Caller `?bfmeSet@Gen_001C3FB0@@QAE_NPAX@Z` at 0x001C3FB0 reaches this body at 0x001C3FB8. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_005c4cc0` at 0x1C4CC0 reaches this body at 0x001C4E1F. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/DisabledTypes.cpp` defines `DisabledMaskType::s_bitNameList`. The unpreprocessed source lists 13 strings and shares the first 1 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
The disabled-type setter at RVA 0x001C81C0 checks its enum argument against 0xB (`disabled-bound.log`). The routed named transfer at RVA 0x001C4CC0 also compares its index against 0xB while reading this table (`widths-and-overlaps.log`). These facts establish eleven logical disabled flags. The lookup has no width operand or receiver. The independently witnessed eleven-bit armor table at VA 0x012A68D8 would require the same one-parameter `BitFlags<11>::s_bitNameList` spelling at a different address. `tools/build.py::verify_dir32_addresses` requires one address per spelling. The original owner or an additional template parameter has not been established, so this row and its original table spelling are left unchanged. An original retail type identity distinguishing these two owners, or an independently proven lookup template width distinct from the logical enum count, would settle the row.

### RVA 0x001C09C0

The table has 86 names followed by null at VA 0x012A67C8. Its verified pointer extent is 348 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a6670.bin`.
Caller `?bfmeSet@Gen_001c6340@@QAE_NPAX@Z` at 0x001C6340 reaches this body at 0x001C6348. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_005cb4e0` at 0x1CB4E0 reaches this body at 0x001CB646. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?rva002E7740@@YAHPAUlua_State@@@Z` at 0x002E7740 reaches this body at 0x002E7775. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `?ReadParameter@Parameter@@SAPAV1@AAVDataChunkInput@@@Z` at 0x00357FC0 reaches this body at 0x0035810C. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/ObjectStatusTypes.cpp` defines `ObjectStatusMaskType::s_bitNameList`. The reference lists 45 strings beginning with NONE; starting at reference index 1, it shares 16 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.

### RVA 0x001C0A30

The table has 116 names followed by null at VA 0x012A8F10. Its verified pointer extent is 468 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a8d40.bin`.
Caller `?bfmeSet@Gen_001c63d0@@QAE_NPAX@Z` at 0x001C63D0 reaches this body at 0x001C63D8. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_005cb730` at 0x1CB730 reaches this body at 0x001CB89F. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/SpecialPower.cpp` defines `SpecialPowerMaskType::s_bitNameList`. The unpreprocessed source lists 68 strings and shares the first 5 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
The routed caller at RVA 0x001CB730 reads the same table and compares its save-loop index against 0x74 (`specialpower-width.log`). That independently proves 116 flags. NamedBits1CB730.cpp already represents 116-bit storage and its lookup call is moved from BitFlags<13> to BitFlags<116>.

### RVA 0x0020E380

The table has 11 names followed by null at VA 0x012A6904. Its verified pointer extent is 48 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a68d8.bin`.
Caller `?bfmeSet@Gen_0020EC60@@QAE_NPAX@Z` at 0x0020EC60 reaches this body at 0x0020EC68. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Caller `FUN_0060f000` at 0x20F000 reaches this body at 0x0020F15F. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/BitFlags.cpp` defines `ArmorSetFlags::s_bitNameList`. The unpreprocessed source lists 8 strings and shares the first 5 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
Zero Hour `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/WeaponSet.cpp` defines `WeaponSetFlags::s_bitNameList`. The unpreprocessed source lists 17 strings and shares the first 4 entries with retail; it does not equal the BFME table. Conditional entries are retained in that raw reference count. The BFME argument comes from retail rather than copying Zero Hour's count.
The same table is read by the named transfer at RVA 0x0020F000, while the adjacent packed transfer at RVA 0x0020ECA0 compares its index against 0xB (`armor-xfer-width.log`). The sweep ArmorSet.h enum names all eleven retail entries in order; Zero Hour ArmorSetType has eight entries. This is the armor-set family, not weapon bonuses.

### RVA 0x0037A9D0

The table has 10 names followed by null at VA 0x012A68A4. Its verified pointer extent is 44 bytes. The complete retail pointer bytes are saved as `build/rlink/bitflags-1791157403/table-012a687c.bin`.
Caller `?parseEmotionType@Rva0037AD00@@SAXPAVINI@@PAX1PBX@Z` at 0x0037AD00 reaches this body at 0x0037AD13. Its instruction boundaries, argument setup and ILT destination are recorded in `retail-probe.log`.
No exact Zero Hour name-table counterpart was found. The EmotionType and EmotionAIType families are established by their retail parser exception strings and the routed callers rather than by inventing a Zero Hour enum.

## Table definitions and competing spellings

Each corrected table is defined from the complete retail sequence in the current body source. No private static member data row is added, following the existing WeaponSet.cpp, SpecialPower.cpp and Damage.cpp convention. Each compiled pointer and string is checked entry by entry against retail. The table and literal spellings are appended to DIR32 rows; existing rows and pins are retained. BitFlags<116>'s old DIR32 row at VA 0x012A68D8 belongs to the former armor lookup claim; the corrected spelling is appended at VA 0x012A8D40 after the armor lookup moves to BitFlags<11>.

WeaponSet.cpp defines the Zero Hour WeaponSetFlags table (BitFlags<17>) while the retained BitFlags<17> DIR32 row maps to the 181-name KindOf table at VA 0x012AA068. SpecialPower.cpp defines SpecialPowerMaskType (BitFlags<67>) while the retained BitFlags<67> DIR32 row maps to the eleven-name disabled table at VA 0x012A9200. These unrelated definitions are not changed: no corrected body reads those spellings. Damage.cpp defines BitFlags<38>; no existing s_bitNameList DIR32 spelling for that instantiation was found, so its address is not asserted here. The compiled spellings and source counts are measured in `compiled-tables-final.log`, `existing-table-definitions.log` and `declaration-counts-all.log`; the source table declaration inventory is in `table-analysis-final.log`.

## Refutation tests

A differing operand, table entry, terminator, count, ILT destination, instruction-boundary caller, one-argument cdecl contract, or compiled byte would refute the respective correction. An independently proven template width other than the stated count would also refute it: a null-terminated lookup itself has no width operand. In particular, the disabled lookup is not assigned eleven merely because it reads eleven strings. A Zero Hour enum match is only claimed where the measured source sequence supports it; BFME-specific additional names are not treated as Zero Hour evidence.

## Independent retail width observations

The named transfer for the 29-entry weapon-set table compares EBP against 0x1D at RVA 0x001C51A8. The 304-entry model-condition transfer compares EDI against 0x130 at RVA 0x001CB370. The 86-entry status transfer compares EDI against 0x56 at RVA 0x001CB5E0. The armor transfer compares EBP against 0xB at RVA 0x0020F0F8. These callers read the corresponding tables and route their load-path lookup calls through the ILTs listed above. Full raw bytes and disassembly are in `build/rlink/bitflags-1791157403/widths-and-overlaps.log`. Together with the 0x74 special-power bound, these are independent of the 71-byte lookup shape.

The model-condition table already has a matched datum row named `?Rva00EA6918ModelConditionNames@@3PAPBDA` at RVA 0x00EA6918, size 1220, in parseModelConditionFlags.cpp. The original datum name, source and bytes are unchanged; no second data row is added. The newly verified private static member spelling describes the same table start. The range check finds that existing datum and no other datum in any queried table range. All competing DIR32 names occur at the table starts, with no interior name. Raw range results are in `widths-and-overlaps.log` and `table-analysis-final.log`.

## Zero Hour enum counts

The reference enum counts below are evaluated with ALLOW_SURRENDER and ALLOW_DEMORALIZE undefined, matching the relevant source flags. Raw enum text and evaluated entries are in `build/rlink/bitflags-1791157403/zh-enum-counts-verified.log`. None of these Zero Hour counts equals the corresponding full BFME table cardinality, and the complete sequences differ. The common prefixes in the per-row comparisons identify the families; they are not claims of identical enumerations.

| Reference enum | Count constant | Zero Hour value |
|---|---|---:|
| WeaponSetType | WEAPONSET_COUNT | 17 |
| ModelConditionFlagType | MODELCONDITION_COUNT | 117 |
| ObjectStatusTypes | OBJECT_STATUS_COUNT | 45 |
| SpecialPowerType | SPECIALPOWER_COUNT | 67 |
| ArmorSetType | ARMORSET_COUNT | 8 |
| DisabledType | DISABLED_COUNT | 13 |

## Declaring game-file counts for each competing spelling

These counts concern C++ declarations in the candidate, including verified typedef spellings and parser macros. They are not ownership evidence. Exact file lists and raw source matches are in `declaration-counts-all.log` and `declaration-raw-matches.log`. For the scalar and array spellings of g_bfmeTableDJb, the declarations are counted separately.

| Table VA | DIR32 spelling | Declaring game files |
|---|---|---:|
| 0x012A6858 | `?s_bitNameList@?$BitFlags@$05@@0PAPBDA` | 1 |
| 0x012AD6B0 | `?TheBfmeWeaponSetFlagNames@@3PAPBDA` | 2 |
| 0x012AD6B0 | `?g_bfmeTableDJc@@3PAHA` | 2 |
| 0x012AD6B0 | `?s_bitNameList@Rva001EB180BitFlagsParser@@0QBQBDB` | 1 |
| 0x012AD6B0 | `?s_bitNameList@?$BitFlags@$0BN@@@0PAPBDA` | 1 |
| 0x012A6918 | `?ModelConditionNames@@3QBQBDB` | 3 |
| 0x012A6918 | `?g_bfmeTokA450@@3QBDB` | 1 |
| 0x012A6918 | `_bfmeGlobalTable12A6918` | 0 |
| 0x012A6918 | `?s_bitNameList@?$BitFlags@$0BDA@@@0PAPBDA` | 1 |
| 0x012A9200 | `?g_bfmeTableDJa@@3PAHA` | 2 |
| 0x012A9200 | `?s_bitNameList@?$BitFlags@$0ED@@@0PAPBDA` | 1 |
| 0x012A9200 | `?s_bitNameList@Rva0029C7B0BitFlagsParser@@0QBQBDB` | 1 |
| 0x012A6670 | `?Rva00209130StatusNames@@3QBQBDB` | 3 |
| 0x012A6670 | `?g_bfmeTableENa@@3PAHA` | 1 |
| 0x012A6670 | `?s_bitNameList@Rva00204770BitFlagsParser@@0QBQBDB` | 1 |
| 0x012A6670 | `?s_bitNameList@?$BitFlags@$0FG@@@0PAPBDA` | 1 |
| 0x012A8D40 | `?g_bfmeTableENb@@3PAHA` | 1 |
| 0x012A8D40 | `?names1CB730@@3PAPBDA` | 2 |
| 0x012A8D40 | `?s_bitNameList@?$BitFlags@$0N@@@0PAPBDA` | 0 |
| 0x012A8D40 | `?s_bitNameList@?$BitFlags@$0HE@@@0PAPBDA` | 1 |
| 0x012A68D8 | `?g_bfmeTableDJb@@3HA` | 1 |
| 0x012A68D8 | `?g_bfmeTableDJb@@3PAHA` | 3 |
| 0x012A68D8 | `?s_bitNameList@?$BitFlags@$0HE@@@0PAPBDA` | 1 |
| 0x012A68D8 | `?s_bitNameList@Rva00141320BitFlagsParser@@0QBQBDB` | 1 |
| 0x012A68D8 | `?s_bitNameList@?$BitFlags@$0L@@@0PAPBDA` | 1 |
| 0x012A687C | `?Rva012A687CNames@@3PAPBDA` | 1 |
| 0x012A687C | `?s_bitNameList@?$BitFlags@$09@@0PAPBDA` | 1 |

## Verification

The sanctioned add_match identity replacements were applied with verification deferred until the competing family names had all moved. Five named rows were corrected through add_match and tombstoned; the two existing dup rows retain their ledger names and receive corrected object-symbol and dup-of notes. The lookup bodies are explicitly instantiated in their original files. All source callers spelling the affected old template arguments, and the two now-stale caller ledger notes, were moved to the corrected arguments. Existing pins and DIR32 rows remain byte-for-byte prefixes of the updated files. The five named replacements keep their original row positions; no descriptive name is replaced by an address-derived name.

The duplicate rows receive direct body pins, because pin_consistency rejects route pins whose destination row remains address-derived. The initial unlanded route candidates were removed and replaced before final verification; no pre-existing pin was edited or removed. Raw rejection and final results are `pin-consistency-after.log`, `adjust-duplicate-pins.log` and `pin-consistency-final-fixed.log`.

The actual `./build.sh` gate reports Functions OK 564/564 across all eight changed sources, with string, constant and DIR32 verification passing (`build-shell-final.log`). CSV, pin consistency and declared-unmatched checks pass (`check-csv-passed.log`, `pin-consistency-final-fixed.log`, `declared-unmatched-after.log`). Every pointer and string in each defined table reproduces retail entry by entry, including all null terminators (`compiled-tables-final.log`).

Before and after link checks retain 5 linked bytes in Rva0037AD60LookupEmotionAITypeThunk.cpp and zero in each of the other seven files. Both runs report one of eight files linking; the remaining files have existing blockers. Comparing every source, blocker category, symbol and reason finds zero added blockers and removes the former unresolved BitFlags<116> table reference in BattlePlanUpdate.cpp. Raw logs are `link-before-all.log`, `link-after-all.log` and `final-comparison-corrected.log`. The comparison also verifies unchanged row positions, additive pins and DIR32 records, and no added naked or emit lines.

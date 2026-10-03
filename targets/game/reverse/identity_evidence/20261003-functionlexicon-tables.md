# FunctionLexicon retail callback tables

Severity: WRONG, fixed for the four local tables registered by init.
Rule: docs/matching.md Relocations requires referenced contents to agree;
a masked DIR32 table operand alone is not initializer proof.

The init claim RVA00105640/135B registers four local tables
through independently decoded operands. The source is in the survivingAugust1
cohort, but this135B init row itself is not an August1 survivor. All table Ghidra memory reads
were compared directly with the unpacked PE; they agree byte for byte.

| Operand | Table VA | Source before | Retail and corrected | Bounded bytes |
|---:|---:|---:|---:|---:|
| +04 | 012A93EC, draw | 2 keys | 2 keys | 36 |
| +12 | 012A9410, system | 71 keys | 59 keys | 720 |
| +20 | 012A96E0, input | 61 keys | 52 keys | 636 |
| +2E | 012ED880, tooltip | 1 key | empty | 12 |

Each count excludes its complete12B zero sentinel. loadTable105570 tests the
name pointer at+4 and advances by12, independently establishing termination
and element width. Its full159B ends RET8at10560C..10560E thenCC10560F.
init ends in a tail JMP at1056C2..1056C6, thenCC1056C7; it is not RET-ended.

Remove the source-only callbacks from the system/input arrays, add the two
retail ImageComboBox records in their exact order, and leave the tooltip array
as its actual empty sentinel. Keep all other layout-table bindings unchanged.
GadgetImageComboBoxSystem and Input already have independently identified
matched bodies at4B6190 and4B5E40; the retail records route through199AC and6339.
Their existing source declarations establish the four-argument callback ABI.
No callback body, semantic identity, pin or shared header is added here.

The bounded COFF/PE proof checks all1404bytes across the four separate arrays:
113 complete NUL-terminated key strings, key integer0, callback relocations,
and every zero terminator. It does not force the compiler's section packing
onto retail: the old whole-section warning starts at+28 partly because the
compiler padded between arrays. Each table instead has its own init operand.

108 callback sites agree with existing resolver candidates and the retail
name table. Five existing source callback declarations have no named ledger
provider yet. Their exact runtime-name records and the unchanged Zero Hour
prototypes in GameClient/GUICallbacks.h and Gadget.h independently identify:

| Existing declaration | Retail ILT | Callback body RVA |
|---|---:|---:|
| ReplayMenuSystem | 4B358 | 4E0A70 |
| WOLMapSelectMenuSystem | FF79 | 504600 |
| ControlBarSystem | 80E4 | 4C0560 |
| GadgetComboBoxInput | 2EFD7 | 4B4010 |
| GadgetTextEntryInput | 28033 | 4BEBD0 |

These are explicit bounded data-target proofs, not fabricated resolver pins,
new callback conversions or a claim that the complete app now links. The five
preexisting provider gaps remain. The existing source gate passes11/11 code
claims and8 recorded DIR32 references. No function row, extent or coverage
changes; the repaired initializers are the gain.

Reproduction: build/audit_v3/s5_lexicon_verify.py and s5_lexicon_proof.json.
The proof treats the empty tooltip's COFF BSS as zero-initialized storage,
checks its full12B extent and absence of relocations, and compares it with
retail. Before-image tables and complete named callback routes are retained
in s5_lexicon_tables.json. No invented member/type names or baseline changes.

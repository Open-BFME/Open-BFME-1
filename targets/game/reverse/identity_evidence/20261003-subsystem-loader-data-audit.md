# SubsystemLegend loader lookup initializer

Retrospective data repair, model=gpt-6-astra,2026-10-03. This changes one existing static initializer; no function identity, extent, pin or coverage is added.

## Independent retail chain

- Matched parseLoadSubsystem atRVA009A15C0 is219 bytes: PUSH VA011415C0 at009A1615 selects its FieldParse table; RET4 at009A1698 ends before padding009A169B.
- FieldParse's Loader record atVA011415F0 is `94 15 14 01 30 11 c5 00 58 77 2d 01 28 00 00 00`: name `Loader`, parserVA00C51130, userDataVA012D7758, member offset28.
- Parser RVA00851130 calls RVA00850A70 at00851178. The matched scanLookupList increments its cursor by8 at00850AA0 (`83 c6 08`) and returns `[esi+4]` at00850ACB (`8b 46 04`). Thus the second dword is the record's value, not an independent second record name.
- Baseline and Ghidra agree that the16 bytes atVA012D7758 (RVA00ED7758) are `6c 15 14 01 68 15 14 01 00 00 00 00 00 00 00 00`. The first two pointers read `INI\0` and `STR\0` atVA0114156C/01141568. The final eight bytes terminate the table.

## Contradiction and correction

The old source declared `{ "INI", 0 }, { NULL, 0 }`, contradicting all four bytes of the second field. Its existing comment already described the retail pointer value, but the initializer did not implement it. The correction is `{ "INI", (int)"STR" }`. It preserves the encoded lookup result rather than assigning a speculative enum meaning to it. MSVC emits this as static `.rdata` with a DIR32 relocation; it creates no dynamic initializer.

The independent16-byte object check validates both pointer relocations by comparing their complete pointed-to strings with retail, and compares every non-relocation byte. Before: differences at+4,+5,+6,+7. After: both strings and all remaining bytes equal. This verifies the complete table, rather than masking its pointers and declaring equality.

The whole source's277 matched claims still pass strict byte verification, including parseLoadSubsystem and its cleanup rows;2 empty string references and4 individually anchored DIR32 references pass. The source's wider initialized-data audit still has pre-existing section-packing, vtable-binding and placement diagnostics. This isolated repair does not certify those other sections. No baseline or verifier changed.

Raw reproducible audit artifacts in this worktree: build/audit_v3/s2_subsystem_table_proof.json, s2_verify_subsystem_table.py, s2_subsystem_table_verification.json, s2_subsystem_before.obj, and s2_subsystem_after.log.

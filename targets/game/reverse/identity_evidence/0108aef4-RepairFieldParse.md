# Repair-health FieldParse table

Corrected: the existing address-bearing g_table_00122E10 spelling is retained as a const FieldParse array. Its previous int declaration and the WideFieldParse declaration used by the composite builder are respelled to this one definition. The original class identity remains unclaimed.

Retail has no PE base-relocation directory (`build/rlink/contracts-retail.log`). Here a relocation means a verified pointer field and its compiled COFF DIR32 relocation. FieldParse is the reference structure of four 32-bit fields: token pointer, cdecl parser pointer, userData and destination offset. Retail `INI::initFromINIMulti` at RVA 0x00851910 passes `(INI *, instance, instance + tableOffset + fieldOffset, userData)` and removes the four arguments after the callback at VA 0x00C51A11. Its field lookup helper and MultiIniFieldParse appender provide the record and table contract. `build/rlink/contracts-retail.log` contains the instructions. Table-address consumers pass or return the table; the shared INI routines read it and write the destination instance. No direct table write appears in those measured consumers. The tables lie in retail read-only `.rdata`.

### VA 0x0108AEF4: g_table_00122E10

The retail datum occupies 32 bytes in `.rdata`. Its complete logical array contains 2 records, including the first all-zero terminator. The initial bytes are `f0 a6 08 01 e0 2e c5 00 00 00 00 00 08 00 00 00`. The full bytes, every record, code references and ILT jump bytes are in `build/rlink/0108aef4-retail.log`. Direct address-reference sites have RVAs 0x00122E17, 0x00378178. The next pre-existing named datum is at VA 0x0108AF20; the log also records the bytes immediately after the terminator. There is no pre-existing data row overlapping this extent and no other DIR32 address inside it.

Competing initial spellings: `?WideTblA00378170@@3QBVWideFieldParse@@B` (1 game files), `?g_table_00122E10@@3HA` (1 game files). Counts include macro declarations and do not decide identity.

The first record is RepairHealthPercentPerSecond, INI::parsePercentToReal at RVA 0x00852EE0, null userData and destination offset 8. The next record is entirely zero. The main builder at RVA 0x00122E10 and composite builder at RVA 0x00378170 append it with additional offset zero. Zero Hour `GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp` uses the same key with the same parser in a FieldParse array, but its additional fields and base chaining differ. That resemblance does not prove the BFME owner is DozerAIUpdateModuleData, so no owner rename is made.

A pointer that follows an E9 to a different final body, a token or scalar differing from the saved retail bytes, an interior DIR32 or overlapping data row, or a user passing a different record layout would refute this correction. Function bytes must continue matching in every changed source.

Raw initializer and data verification: `build/rlink/pin-repair-literals.log` and `add-0108aef4.log`.

# TheLookAtTranslator at VA 0x012F4C64

The corrected owner is the existing `LookAtTranslator *TheLookAtTranslator` definition in `game/GameEngine/Source/GameClient/MessageStream/LookAtXlat.cpp`. The datum receives a byte-verified four-byte data row. S3GlobalForwarders.cpp now declares this canonical pointer and casts it to its existing local member-call view. No function identity, verified code byte, or existing pin changes.

The datum is one mutable 32-bit pointer (one element, four bytes) in the zero-filled virtual tail of retail .data. Its initial image value is 00 00 00 00. The unpacked PE base-relocation directory is empty; this initializer contains no address field. Runtime stores of object receivers and pointer loads prove a mutable pointer slot rather than a compiler constant or a table. The original data ledger has no overlapping row and the DIR32 ledger has no name strictly inside the four-byte extent. The exact section bounds, neighboring names, image bytes and direct reads and writes are recorded in the raw probes.

The matched constructor at RVA 0x005A6580 publishes its primary receiver at VA 0x009A65CC when the slot is null. The matched destructor at RVA 0x005A63A0 compares its ECX receiver with the slot and clears it at VA 0x009A63AE. Zero Hour declares the same global type in GeneralsMD/Code/GameEngine/Include/GameClient/LookAtXlat.h and defines it in Source/GameClient/MessageStream/LookAtXlat.cpp; that reference constructor publishes this and its destructor clears the same singleton. The existing symbols.csv pin also names this slot TheLookAtTranslator. The two forwarders load this pointer into ECX before tail-jumping through retail ILT entries; their local address-derived callee spellings are retained. The datum has no argument ABI; the receiver contract is the primary LookAtTranslator object.

| Original DIR32 spelling | Game files directly declaring this type |
|---|---:|
| `?TheBfmeGlobal_012f4c64@@3PAVBfmeGlobal_012f4c64@@A` | 1 |
| `?TheLookAtTranslator@@3PAVLookAtTranslator@@A` | 4 |
| `?g_Va012F4C64@@3HA` | 0 |

A different constructor-published object, a thunk routed to a different member, a non-pointer writer, or an independently named datum inside this four-byte extent would refute the correction.

Raw evidence: `build/rlink/012F4C64-retail.txt`, `build/rlink/012F4C64-accesses.txt`, `build/rlink/identity-0LookAtTranslator-QAE-XZ.txt`, `build/rlink/identity-1LookAtTranslator-UAE-XZ.txt`, `build/rlink/lookat-reference-header.txt`, `build/rlink/reference-identities.txt`, and `build/rlink/add-data-lookat.log`.

# Pointer identity at VA 0x012F4B40

The corrected datum is `BfmeAptScreenQuitMenu *g_obj12F4B40`, spelled `?g_obj12F4B40@@3PAVBfmeAptScreenQuitMenu@@A`. The owner is `game/GameEngine/Source/GameClient/GUI/BfmeAptScreenQuitMenuConstructor.cpp`. A byte-verified data row defines it once; all direct game declarations of the competing spellings are moved to this symbol. Existing DIR32 rows and symbols.csv pins remain additive evidence, not alias definitions.

The datum is one mutable 32-bit pointer (one element, four bytes) in the zero-filled virtual tail of retail .data. Its initial image value is 00 00 00 00. The unpacked PE base-relocation directory is empty; this initializer contains no address field. Runtime stores of object receivers and pointer loads prove a mutable pointer slot rather than a compiler constant or a table. The original data ledger has no overlapping row and the DIR32 ledger has no name strictly inside the four-byte extent. The exact section bounds, neighboring names, image bytes and direct reads and writes are recorded in the raw probes.

The QuitMenu constructor pin is ILT RVA 0x00025153, whose E9 chain ends at RVA 0x0056A2F0. The publishing body installs the primary vtable at VA 0x0110A388 and stores the primary receiver into this cell at VA 0x0096A361. Its destructor at RVA 0x00569720 compares the same cell with its primary receiver and clears it. The constructor callback strings identify AptQuitMenu. The BfmeObj947C and BfmeObj985 structures are local views of the same screen, not additional datum identities.

The receiver contract is the pointer to the primary object published by the witnessed owner. The datum itself has no calling convention or arguments. Constructors receive their ordinary primary receiver in ECX; the pinned constructor signatures and exact stack cleanup are retained in the raw disassembly. Consumer member calls use the loaded pointer as ECX, and field accesses apply to the pointed-to object. Local casts retain existing consumer ABI views and volatile access requirements; no wrapper, inheritance or second datum is introduced.

The Zero Hour tree contains no APT screen or FX category declaration establishing an EA variable name for this slot. Existing role names are retained only where retail use confirms them. Address-derived basenames remain address-derived; no original EA spelling is claimed for them.

| Original DIR32 spelling | Game files directly declaring this type |
|---|---:|
| `?g_Va012F4B40@@3HA` | 1 |
| `?g_bfme947ObjC@@3PAUBfmeObj947C@@A` | 4 |
| `?g_bfmeObj985@@3PAUBfmeObj985@@A` | 1 |
| `?g_obj12F4B40@@3PAXA` | 8 |

A different final target for a recorded E9 thunk, a publishing constructor for a different screen, a store of an integer rather than a receiver, a retail access wider than four bytes to this datum, or an independently named datum inside the four-byte extent would refute this correction. For the opaque subsystem receiver, an incompatible receiver contract in the pinned apply body would refute the selected type.

Raw evidence: `build/rlink/012F4B40-retail.txt`, `build/rlink/012F4B40-accesses.txt`, `build/rlink/add-data-012F4B40.log`, `build/rlink/identity-0BfmeAptScreenQuitMenu-QAE-PAX-Z.txt`. Declaration counts and their source paths are retained in `build/rlink/screen-declaration-inventory.json`; compiler gates and per-file LINKED measurements are indexed in `build/worker-final.md`.

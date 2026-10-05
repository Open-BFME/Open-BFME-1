# Pointer identity at VA 0x012F4B44

The corrected datum is `BfmeAptScreenSaveLoad *TheAptSaveLoad`, spelled `?TheAptSaveLoad@@3PAVBfmeAptScreenSaveLoad@@A`. The owner is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp`. A byte-verified data row defines it once; all direct game declarations of the competing spellings are moved to this symbol. Existing DIR32 rows and symbols.csv pins remain additive evidence, not alias definitions.

The datum is one mutable 32-bit pointer (one element, four bytes) in the zero-filled virtual tail of retail .data. Its initial image value is 00 00 00 00. The unpacked PE base-relocation directory is empty; this initializer contains no address field. Runtime stores of object receivers and pointer loads prove a mutable pointer slot rather than a compiler constant or a table. The original data ledger has no overlapping row and the DIR32 ledger has no name strictly inside the four-byte extent. The exact section bounds, neighboring names, image bytes and direct reads and writes are recorded in the raw probes.

The SaveLoad constructor pin is ILT RVA 0x00003AD0, whose E9 chain ends at RVA 0x0056E980. The body stores its primary receiver into this cell at VA 0x0096EA3B and registers the shipped SaveLoad callback strings. Its destructor at RVA 0x0056E230 clears the cell. showAptSaveLoad at RVA 0x0056BFA0 loads the pointer and writes receiver fields at 0x270, 0x274, 0x278 and 0x27C. The role-bearing TheAptSaveLoad basename is retained, while the ad hoc AptSaveLoad view is replaced by the constructor-proven BfmeAptScreenSaveLoad pointee.

The receiver contract is the pointer to the primary object published by the witnessed owner. The datum itself has no calling convention or arguments. Constructors receive their ordinary primary receiver in ECX; the pinned constructor signatures and exact stack cleanup are retained in the raw disassembly. Consumer member calls use the loaded pointer as ECX, and field accesses apply to the pointed-to object. Local casts retain existing consumer ABI views and volatile access requirements; no wrapper, inheritance or second datum is introduced.

The Zero Hour tree contains no APT screen or FX category declaration establishing an EA variable name for this slot. Existing role names are retained only where retail use confirms them. Address-derived basenames remain address-derived; no original EA spelling is claimed for them.

| Original DIR32 spelling | Game files directly declaring this type |
|---|---:|
| `?R2Glob012F4B44@@3PAXA` | 1 |
| `?TheAptSaveLoad@@3PAVAptSaveLoad@@A` | 4 |
| `?g_Va012F4B44@@3HA` | 2 |
| `?g_bfmeReadyAG@@3PAXA` | 2 |

A different final target for a recorded E9 thunk, a publishing constructor for a different screen, a store of an integer rather than a receiver, a retail access wider than four bytes to this datum, or an independently named datum inside the four-byte extent would refute this correction. For the opaque subsystem receiver, an incompatible receiver contract in the pinned apply body would refute the selected type.

Raw evidence: `build/rlink/012F4B44-retail.txt`, `build/rlink/012F4B44-accesses.txt`, `build/rlink/add-data-012F4B44.log`, `build/rlink/identity-0BfmeAptScreenSaveLoad-QAE-PAX-Z.txt`. Declaration counts and their source paths are retained in `build/rlink/screen-declaration-inventory.json`; compiler gates and per-file LINKED measurements are indexed in `build/worker-final.md`.

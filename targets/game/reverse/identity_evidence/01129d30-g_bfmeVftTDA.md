# g_bfmeVftTDA at VA 0x01129D30

This datum is a 6-entry array of constant 32-bit code pointers, occupying 24 bytes in .rdata. Its chosen spelling is `?g_bfmeVftTDA@@3QBQAXB`. The table is installed as an object vptr by the retail constructors, factories and destructor shown in the raw probe. A scalar pointer object, scalar int, or byte string does not describe these initial bytes and slot use. The class identity is not established and no new native class identity is claimed. The existing vtable-role spelling is retained with its array type.

The complete initial bytes are `60b7be0080b7be00b0b8be0020b9be00c0b9be0070b8be00`. Every entry points to a ledger-backed retail body listed below. All 6 entries are DIR32 relocations in the compiled definition. The original datum ends at VA 0x01129D48; the following bytes are a narrow assertion string. No other DIR32 start lies inside this range and no data row overlaps it.

The receiver contract is that the constructor or destructor stores this address at the observed vptr field. Slot-specific contracts remain those of the existing function rows. The declarations used to initialize the table take addresses only; they do not invoke the bodies or introduce forwarding functions. Retail code reads the table indirectly through object vptrs; the direct references install its address and do not write its storage.

Raw bytes, slot identities and vptr stores are recorded in `build/rlink/identity-types-1791185133/retail-all.txt`; declaration counts are in `declaration-counts.csv`; compilation and data-gate receipts are in `vtables.txt` and the `add-data` log for this address.

| Slot | Retail VA | Ledger spelling |
|---|---|---|
| 0 | 0x00BEB760 | `?setFields_007EB760@Rva007EB8B0Log@@UAEXHH@Z` |
| 1 | 0x00BEB780 | `?bfmeGoELF@BfmeThingELF@@QAEXPAX@Z` |
| 2 | 0x00BEB8B0 | `?Rva007EB8B0@@YAXPAVRva007EB8B0Log@@IPBDZZ` |
| 3 | 0x00BEB920 | `?assertFailed@Rva007EB8B0Log@@QAEHPBD0H@Z` |
| 4 | 0x00BEB9C0 | `?errorFrom@Rva007EB8B0Log@@QAEHHPBD0H@Z` |
| 5 | 0x00BEB870 | `?bfmeDelTQD@BfmeThingTQD@@QAEPAXE@Z` |

A slot with non-code contents, a different pointer target, a vptr store to another address, an interior datum start, or a caller that dereferenced this address as a scalar pointer cell would refute this correction. The identity decision does not rely on declaration popularity.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?g_bfmeVftTDA@@3PAPAXA` | 1 |
| `?g_bfmeVftTQD@@3PAPAXA` | 1 |
| `?vftable_01129D30@@3HA` | 1 |

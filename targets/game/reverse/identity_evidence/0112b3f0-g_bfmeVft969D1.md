# g_bfmeVft969D1 at VA 0x0112B3F0

This datum is a 3-entry array of constant 32-bit code pointers, occupying 12 bytes in .rdata. Its chosen spelling is `?g_bfmeVft969D1@@3QBQAXB`. The table is installed as an object vptr by the retail constructors, factories and destructor shown in the raw probe. A scalar pointer object, scalar int, or byte string does not describe these initial bytes and slot use. The class identity is not established and no new native class identity is claimed. The existing vtable-role spelling is retained with its array type.

The complete initial bytes are `a04bbf00804bbf00b04bbf00`. Every entry points to a ledger-backed retail body listed below. All 3 entries are DIR32 relocations in the compiled definition. The original datum ends at VA 0x0112B3FC; the following bytes are a distinct vtable whose own DIR32 start is already recorded. No other DIR32 start lies inside this range and no data row overlaps it.

The receiver contract is that the constructor or destructor stores this address at the observed vptr field. Slot-specific contracts remain those of the existing function rows. The declarations used to initialize the table take addresses only; they do not invoke the bodies or introduce forwarding functions. Retail code reads the table indirectly through object vptrs; the direct references install its address and do not write its storage.

Raw bytes, slot identities and vptr stores are recorded in `build/rlink/identity-types-1791185133/retail-all.txt`; declaration counts are in `declaration-counts.csv`; compilation and data-gate receipts are in `vtables.txt` and the `add-data` log for this address.

| Slot | Retail VA | Ledger spelling |
|---|---|---|
| 0 | 0x00BF4BA0 | `?handle@Rva007F4BA0@@W3AEXXZ` |
| 1 | 0x00BF4B80 | `?eq@Rva007F4B80@@QBEHPBVObj007F4B80@@HH@Z` |
| 2 | 0x00BF4BB0 | `?d_007f4bb0@@YAXXZ` |

A slot with non-code contents, a different pointer target, a vptr store to another address, an interior datum start, or a caller that dereferenced this address as a scalar pointer cell would refute this correction. The identity decision does not rely on declaration popularity.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?g_bfmeRva0112B3F0Vt@@3PAXA` | 1 |
| `?g_bfmeVft969D1@@3PADA` | 1 |

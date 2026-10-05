# Codec apply table at VA 0x01141D08

The datum is the 64-entry constant 16-bit coefficient table used by bfmeApply1040, Rva009A4D00Init and Rva009A6780BuildQuantizers. It occupies 128 bytes in retail .rdata and has no relocations. The chosen spelling is `?g_bfmeApplyTableC@@3QBGB`, already mapped at this address. The existing role describes the apply table; the address-derived mutable short-array spelling is retired from these users. The following coefficient table starts at 0x01141D88, and neither a data row nor any DIR32 name starts inside the chosen range.

Retail Rva009A4D00Init iterates short-width loads from 0x01141D08 through the exclusive endpoint 0x01141D88. It sign-extends each element, halves it with signed rounding, adds two and stores a dword. Rva009A6780BuildQuantizers sign-extends an indexed element before forming a reciprocal. bfmeApply1040 zero-extends the indexed element before shifting left by two and storing a 16-bit coefficient. These signed and unsigned views are retained explicitly. The bytes prove the width, count and uses; they do not distinguish the original author's signedness declaration. The canonical const unsigned-short definition retains the existing apply-table representation, and the corresponding signed-short views preserve all observed arithmetic.

Every initial value is read from retail and listed in `build/rlink/identity-types-1791185133/codec.txt`. The exact bytes and disassembled readers are in `retail-all.txt` and `01141d08.bin`. The data gate is in `add-data-01141d08.txt`. There is no datum receiver or argument; the consumer routines index the table using their existing receiver's index field. The complete loop is additional evidence that this is a table, not a compiler arithmetic constant. Direct references only read it.

A loop endpoint other than 0x01141D88, non-16-bit element accesses, a pointer relocation in the initializer, any changed signed or unsigned instruction, or an interior datum start would refute this correction. The source gates must keep all functions byte-identical.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?g_Rva01141D08@@3PAFA` | 2 |
| `?g_bfmeApplyTableC@@3QBGB` | 1 |

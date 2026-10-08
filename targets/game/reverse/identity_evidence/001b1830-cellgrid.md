# CellGrid identity at retail RVA 0x001B1830

The 516-byte constructor was named `BfmeCellGrid` while its identity was unresolved. The strong `chain+direct` name row in `ea_evidence.csv` now pairs it with EA's `CellGrid::CellGrid`. This label alone is not the proof.

The retail constructor independently references the literal `Could not create Cell Grid for VictorySystem!` for both cell-array allocations. Its body constructs a 0x1c-byte grid containing dimensions, spacing/origin and two arrays. The matched VictorySystem callers allocate/use that grid; its reset, destructor, point lookup, accumulation, evaluation and xfer methods share the same layout and call routes. This corroborates the labelled constructor's class ownership rather than borrowing a label from an unrelated inlined method.

Rename the class to `CellGrid` across its declarations, definitions, matched callers and existing pins. Preserve all existing method identities, RVAs, extents, parameter types and member names. Do not infer names for the separate `BfmeCell` type or the address-derived grid methods. Byte-verify all touched source files and every corrected ledger row.

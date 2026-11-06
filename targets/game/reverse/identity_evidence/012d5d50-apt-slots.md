# Apt availability slots at VA 0x012D5D50

The BFME 1 image contains fourteen 8-byte records in .data. The matched availability scan at RVA 0x008D2070 reads the flags at offset 0 and the signed index at offset 4, walks from VA 0x012D5D54 to the exclusive VA 0x012D5DC4 and scales the index by four for its lookup at VA 0x01338480. The definition keeps the existing volatile accesses and DIR32 name. The fourteen records are integers with no relocations. No owner for this table was found by its current names in the pinned BFME 2 reference dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce.

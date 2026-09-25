# RVA 0x0035AB70: cleanup of indexed string records

The full 143-byte thiscall body ends at 0x0035ABFF with a plain RET. Its receiver uses exactly the existing Rva00359330StringRecordTable layout: records at +0x0C, active tail index at +0x1C, twenty-byte records with previous/next links, AsciiString at +8, released byte +0x0C, reference word +0x0E and node pointer +0x10.

The original previous index is saved across deletion and release. A released record unlinks and destroys exactly its first node, then calls the established release(int) at 0x00359330 through ILT0x19574. The full 153-byte release body confirms the record stride, links, flags and AsciiString lifetime. For an unreleased record, cleanup retains the first node, deletes its successors, stores each saved successor link after destruction, and resets the reference word to one. There is no first-node null guard in retail.

Both node destructor calls go through ILT0x42A32 to the existing address-derived Rva00354A00Node destructor at 0x00354A00 (72 bytes). Its full body leaves the next link at offset zero intact and destroys the owned members at +8/+0x0C. Existing native destructor and release symbols suffice; no pins or semantic owner invention are needed.

The initial worker draft incorrectly drained all nodes in the released case; the follow-up preloaded a successor before checking whether it existed. Neither draft is retained as matching evidence. The reviewed source places the successor load inside the loop before delete and the store after delete, reproducing all 143 bytes. add_match verifies 1/1 including all five call relocations. The original ASM is retained and total exact coverage is unchanged.

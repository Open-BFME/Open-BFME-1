# Apt diagnostics value at VA 0x013377F4

The datum is one zero-initialized `int` (four bytes) in retail `.data`, with no initial pointer relocations. The established address-derived spelling `?g_rva00891FA0Value@@3HA` describes its arithmetic and formatted numeric use. The competing `?g_bfmeJ1017Other@@3PAXA` pointer spelling occurs in one game declaration; the chosen spelling occurs in two game declarations before the correction. No original EA variable name is established.

Retail RVA 0x00891FA0 loads this cell for `sprintf` with the `%06d` format and again as the first word of an eight-byte diagnostics record. RVA 0x00892150 writes zero to the cell. At RVA 0x00892A70, VA 0x00C92B05 adds ESI to its loaded value, and VA 0x00C92B07 writes the sum back. RVA 0x008C8120 passes its value to the existing AptInteger creation path. The other measured readers are listed in the raw address log.

The receiver contract is a global scalar load, not an object receiver or a pointer dereference. BfmeJ1017::bfmeInsert copies this same value into the first four bytes of its callback record. Retyping that record word from `void *` to `int` preserves its width and every retail instruction. The main diagnostics translation unit owns the definition.

The next DIR32 datum starts at VA 0x013377F8. There is no other data row or DIR32 name strictly inside the four-byte extent. Both rival names are at its start. Initial bytes are `00 00 00 00`; this writable zero-filled cell is not a compiler constant. A retail dereference of this word as an address, a nonnumeric original declaration, or changed instructions in a corrected consumer would refute the correction.

Raw evidence is in `build/rlink/identity-types-1791203017/013377F4-retail.txt`, `retail-summary.json`, `selected-bodies-fixed.txt`, and `game-hits.txt`. Gate and LINKED receipts are recorded in `build/worker-final.md`. The chosen DIR32 row already exists, so no duplicate row or alias is added.

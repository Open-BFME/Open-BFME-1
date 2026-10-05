# STLport classic character mask table at VA 0x0112EC48

The two questioned addresses describe one object. `_STL::ctype<char>::_S_classic_table` is a private static const ctype_base::mask[257] at VA 0x0112EC48, occupying 1028 bytes in .rdata. VA 0x0112EC4C is its element 1, the start of the 256 ordinary character classifications returned by classic_table(). It is not a second int table. The canonical spelling is `?_S_classic_table@?$ctype@D@_STL@@0QBW4mask@ctype_base@2@B`, already recorded at the true object start.

The existing STLport 4.5.3 declaration in inputs/vendor/stlport/stl/_ctype.h defines enum ctype_base::mask at lines 39 through 52, classic_table() as &_S_classic_table[1] at line 124, and the private 257-entry member at line 145. The matched wide-character scan source uses this exact header and member. Its retail do_scan_is and do_scan_not pass VA 0x0112EC4C as the classification base, matching the member's +4 view. The narrow constructor also uses that base. Retail T2WideCtype::isRange and Gen_00840910 bound character indices to 256 and load dword masks from that base. Their complete raw disassemblies are in retail-all.txt. They read the table; direct references do not write it.

Every one of the 257 initial entries is read from retail and verified against the compiled enum-array definition. The separately compiled public enum sizeof probe gives four bytes per entry. There are zero COFF relocations in the array; retail has no PE base-relocation directory. The final element ends at VA 0x0112F04C, with padding before the upper-case table's named start at 0x0112F050. No independent data row overlaps this range. The only interior DIR32 rows are the two retired tail-view names at 0x0112EC4C; the retail consumers and reference prove these are the same member's +4 projection, not additional datum starts. These historical rows are retained, but no definition or data row is created for the tail view.

The member is defined once in the existing canonical STLport scan translation unit. The character constructor's ABI view retains its existing unsigned-mask parameter signature, while its address reference now spells the actual enum member. Its function identity is outside this data correction. T2CtypeTableFacets.cpp and S3MaskedTableTest.cpp use the actual enum type and element 1 view. No inheritance or forwarding function is added, and the old table labels are no longer referenced by these game files.

The private member cannot be sized by add_data_match.py: its decorated template-member spelling cannot be named from its TU by the tool's probe grammar. Per the identity brief's explicit private-static exception, it is defined without a data row after verifying every entry and the complete compiled bytes. The refusal receipt is add-data-0112ec48-private.txt. The complete per-entry retail and COFF comparison, public enum sizeof probe and layout checks are in `build/rlink/identity-types-1791185133/ctype.txt`; the vendor declaration is in stlport-reference.txt and the initial bytes and consumer bodies are in retail-all.txt. This single definition serves both questioned addresses; there is no alias identity at the interior address.

A table base other than member+4, a mask element width other than four, any unequal initial entry, any relocation in the classification values, a genuine independent datum inside the extent, or a source gate that changes a consumer instruction would refute this correction. A source gate refusal restores this shared-object correction without discarding the other verified addresses.

The competing spellings below are counted from original explicit game-source declarations, including macro expansions. Included vendor declarations are separate; the enum classic-table spelling is proven by the vendor header and canonical wide-scan use regardless of its direct game-source count. Raw declaration lines and source paths are retained in `build/rlink/identity-types-1791185133/declaration-counts.txt`; the authoritative count rows are in `declaration-counts.csv`.

| Spelling | Original game CPP declarations (files) |
|---|---|
| `?_S_classic_table@?$ctype@D@_STL@@0QBIB` | 1 |
| `?_S_classic_table@?$ctype@D@_STL@@0QBW4mask@ctype_base@2@B` | 0 |
| `?TheBfmeMaskTable@@3PAHA` | 1 |
| `?t2_mask_table@@3QBIB` | 1 |

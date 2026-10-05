# STLport num_put facet ID at VA 0x012F64E4

The datum is `_STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >::id`, an `_STL::locale::id` containing one four-byte `size_t` index. It is one object rather than a char or an array. Its extent is four bytes in `.data`, with initial bytes `00 00 00 00` and no initial relocation. The next distinct DIR32 start is the FX category head at 0x012F64E8. `build/rlink/identity-15/retail-probe.log` finds no other datum or DIR32 name inside the extent. Retail has no PE base relocation directory, and `retail-extra-complete.log` finds no data-section reference into the extent.

## Retail facts and contract

The direct-reference inventory in `retail-probe.log` identifies readers at RVAs 0x005C0FD0, 0x005C4D00, 0x005C5E40 and 0x005F0120, and the initializing writer at RVA 0x00831F90. The three numeric-output bodies format unsigned long, double and long values. They push VA 0x012F64E4 and call VA 0x00C321D0, `_STL::locale::_M_use_facet`. The shorter body at RVA 0x005C0FD0 performs the same facet lookup. `facet-lookup.log` shows that the lookup takes ECX as a locale receiver and one stack reference to the ID, loads a four-byte index from the referenced object, compares it against the facet-table length, and indexes the facet pointer array at stride four. The direct-call target is the body, not an inferred thunk. The E9 chains for the callers are preserved in the main probe.

The initializer writes the dword value 14 to VA 0x012F64E4. This agrees with `inputs/vendor/stlport/stl/_num_put.h`, where the narrow `ostreambuf_iterator` specialization's `id._M_index` is initialized to 14. The same header declares its static member as `locale::id`, and `stl/_locale.h` declares that object's public `size_t _M_index`. `stl/_num_put.c` defines the template's static `locale::id`. The relevant raw reference search is `build/rlink/identity-15/stl-id-reference.log`, with exact excerpts in `reference-contracts.log`. No interpretation of a decompiler draft is used.

The competing `g_bfmeSlot06VA` spelling is declared by one game source, `BfmeOneHundredTwentyTwo.cpp`; its store is the facet-index initialization. The competing `g_rva005c0fd0_id` spelling is defined by one source, `Rva005C0FD0Facet.cpp`, as `locale::id`, despite its stale DIR32 spelling declaring char. The selected `num_put::id` is declared through STLport headers by the numeric-output users. `spelling-census.log` records the explicit declaration counts and the header-backed users separately. A higher occurrence count is not the identity evidence; the upstream type, index and retail use determine the spelling.

## Correction and refutation

`Rva005C0FD0Facet.cpp` includes the existing vendored declaration and explicitly instantiates this ID once. Its lookup now names the real static member. `BfmeOneHundredTwentyTwo.cpp` uses an extern template declaration and initializes that member's index, preserving its original store. The selected decorated DIR32 spelling already exists and is reused beside the retained losing spellings. There is no symbols pin deletion or rewrite. `build/rlink/identity-15/add-data-facet.log` proves the compiler's four-byte size and retail zero bytes before registering the data row.

A different facet index for this upstream specialization, a byte-sized retail access, a reader using this slot as a pointer, another interior datum, or a different facet specialization returned by the numeric-output lookup would refute the correction. Every affected source must continue to verify every ledger row with identical retail bytes; the raw gate logs and link measurements are recorded in `build/worker-final.md`.

## Spelling census before the correction

Counts below come from the original source snapshots. Template-static counts include the shared game header and owning explicit instantiation, plus files with explicit extern-template declarations. Ordinary pointer counts require the decorated pointer type. For the STLport member, zero means no explicit game declaration; the vendor header and the three known retail numeric-output users are recorded in the raw census. Stale decorated types whose current source already differs are identified in the notes.

| VA | Existing decorated spelling | Game files | Notes |
|---|---|---:|---|
| 0x012F64E4 | `?g_bfmeSlot06VA@@3HA` | 1 |  |
| 0x012F64E4 | `?g_rva005c0fd0_id@@3DA` | 1 | Its sole source defines locale::id, while this stale DIR32 spelling says char. |
| 0x012F64E4 | `?id@?$num_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@2V0locale@2@A` | 0 | No explicit game declaration before this correction. The declaration is in vendored _num_put.h; the known retail numeric-output users are game/GameEngine/Source/GameClient/System/FXParticleSystem/FXParticleSystemOstreamPutNum.cpp, game/GameEngine/Source/GameClient/System/FXParticleSystem/FXParticleSystemOstreamPutNumDouble.cpp, game/GameEngine/Source/GameClient/System/FXParticleSystem/FXParticleSystemOstreamPutNumUnsignedLong.cpp. |

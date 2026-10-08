# Retail dispatch array at VA 0x01121B30

The missing datum is defined in game/GameEngine/Source/Common/Rva0074A680ParserRegistrationCtor.cpp with its existing exact compiler symbol ?g_01121B30@@3PAPAXA and element type void *. This claims the complete two-cell dispatch array, without proposing an EA class name. The ordinary identifier g_01121B30 is declared and consumed by one game source file. No competing recorded spelling, data owner, interior DIR32 name or overlapping data row exists; the streaming owner scan is in build/rlink/dir32-six-20261008/contracts-boundaries-owners.log.

Retail SHA-256 is 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. The .rdata initial bytes are ad b1 41 00 a7 d5 41 00. The constructor's store at VA 0x00B4A6F4 installs the array base at receiver offset zero. retail-probe.log records the constructor, adjacent bytes and each five-byte E9 entry.

| Slot | Retail pointer VA | Five-byte ILT contents | Final body VA |
| --- | --- | --- | --- |
| 0 | 0x0041B1AD | E9 7E F5 72 00 | 0x00B4A730 |
| 1 | 0x0041D5A7 | E9 44 AA 72 00 | 0x00B47FF0 |

Slot 0 takes ECX as receiver and one stack flags word. It calls the registration destructor, tests flags bit zero, optionally frees the receiver, returns the receiver in EAX, and uses RET 4. The registration destructor reinstalls base VA 0x0107C7D0 and unregisters receiver +8 through receiver +4. Slot 1 at VA 0x00B47FF0 reads the first parser argument as its input, consumes two stack arguments, returns AL=1 and uses RET 8. It is the recorded GlobalLighting parser; the array definition makes no new class identity claim.

The registered cdecl callback at VA 0x0041579E contains E9 2D D1 0E 00 and reaches VA 0x005028D0. It takes its third argument as receiver, forwards the input and chunk-info arguments, and calls vptr +4. The base at VA 0x0107C7D0 has the deleting-destructor pointer and purecall pointer. These witnessed contracts identify the two complete virtual slots; no third slot is inferred.

The first following dword at VA 0x01121B38 is zero and excluded. The independently installed neighboring arrays and referenced strings bound the physical pointer runs: VA 0x01121AE8 belongs to Gen_00749740, VA 0x01121B14 is the BlendTileData literal, and VA 0x01121B3C is the Art/Terrain/ literal. Every file-backed section was scanned for each byte-address of the proposed extent and the separator: each base has exactly its constructor reference and no interior or separator reference. absolute-refs.json and contracts-boundaries-owners.log retain the results. The retail PE has no base-relocation directory. The data row's compiled COFF DIR32 fields are verified against the exact retail pointer cells by normal add_data_match.py admission.

Zero Hour DataChunk.h establishes the callback argument types; WorldHeightMap.cpp contains direct callback registrations rather than these BFME scoped classes, so it does not establish a canonical class name. reference-contracts.log preserves the exact excerpts. Source and compiler-reference scope are checked in names-consumers.log, implicit-symbols-fixed.log, and consumer-coff.log. Initializer ILT declarations are used only as pointer values. No inheritance, function body, function ledger identity, shared header or linker alias changes.

A different ILT target, an additional virtual slot belonging to this lead, an interior owner, another actual source consumer of this compiler symbol, a pointer extent including a neighboring literal or array, or any changed verified constructor byte would refute this admission.

Compiler probes of every additional game source containing these class names emit no reference or definition for any of the six array symbols, and no corresponding implicit vftable symbol. The eight additional TUs compile successfully; implicit-coff.log preserves their actual compiler output and zero relevant-symbol counts. constructor-routes.log records each real caller and the five-byte ILT route to the constructor.

Normal admission, the unchanged official key test and ./build.sh each exit zero; their raw logs are admit-01121B30.log, pass-01121B30.log and build-01121B30.log under the evidence folder. The official test deletes this key's baseline line. The function body remains textually identical, and every row in its source passes byte verification. source-body-preservation.log records the textual comparison.

Final ledger checks pass: check-csv-after.log, pin-consistency-after.log and declared-unmatched-after.log. Ordinary linking is measured in link-before.log and link-after.log. This source remains LINKED 0 to 0 bytes because of existing unresolved __bfmeVftVE, unresolved ?bfmeChunkParserVE@@YAXXZ and duplicate BfmeParserRegistrationVE constructor definitions. The new array key is resolved; these independent census blockers precede the repair and are outside the assigned identity correction.

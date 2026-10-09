# RVA 0x00228F10: partial reconstruction and lifetime evidence

The preferred reconstruction remains a partial. Its complete C++ body measures 1965 bytes with 852 non-relocation differences. The previous bank measures 1961 bytes with 1337 differences. The authoritative measurements are `build/228f10-retry/final-probe.log` and `build/228f10-retry/baseline-current-probe.log`. No function ledger row or symbol pin is changed by this attempt. The tested checkout starts at revision `2509058cf6d33b0a5b9a50768252464ddd07b301` and the actual model is `gpt-6.1-sol`.

## Retry hypothesis and result

The new hypothesis was that established StringBase inheritance, the canonical Object layout, and the native signed index-map comparator could resolve the earlier ABI and lifetime uncertainty before stack-slot iteration. The current index-map declaration and pin are witnessed in `HordeContain/Rva002435F0Formation.cpp` and `identity_evidence/002435f0-native-map.md`. The neighbouring OpenContain exit bodies and the real Zero Hour `putObjAtNextFirePoint` source supplied declarations and the eight-byte suffix buffer. Allocation sizes and donor names were not accepted as value-type evidence. Failure to improve the measured bank after these corrections would refute the retry. The measured improvement supports retaining the body, but does not establish an exact recovery.

## Boundary and identity

The complete target has one `ret 8` at +0x7AA and ends at +0x7AD. Its branches stay inside that extent. Ten following bytes are INT3 padding. The raw complete decode with lookahead is `build/228f10-retry/decode-0x00228F10.log`; the exact-extent callee inventory is `target-checked-exact.log`. `flow-audit-corrected.json` records every return and outgoing jump for the target and the principal type helpers. The earlier `flow-audit.json` used an incorrect address-base subtraction and is superseded by the corrected audit.

Primary vtable VA 0x010AC2B8 slot 25 reaches ILT RVA 0x0000D233, which jumps to this target. The same table is installed by the named OpenContain constructor and destructor. The constructor source remains a naked lift and supplies no independent C++ layout proof. The EA aligned identity row calls the body `OpenContain::privateRedeployOccupants`; the Zero Hour `positionContainedObjectsRelativeToContainer` method is empty and supplies no byte-matching donor. This attempt retains the bank's descriptive method name without claiming a naming correction. Raw tables are `primary-vtable.log` and `secondary-vtable.log`.

## Value types and ownership

The input index lookup follows 0x00226FA0 through 0x00224AD0 and 0x00223D20 to the complete 23-byte copy helper at 0x00222520. That helper copies exactly a dword at value+0 and a dword at value+4. The target uses the second dword as a signed bone index, and the search branches compare signed keys. `Rva00226FA0Less` reuses the existing native pin without editing it.

The bone-name lookup follows 0x00228310 through 0x00225CF0 and 0x00225460 to the complete 76-byte helper at 0x002233E0. It copies the key at value+0, then invokes StringBase<char>'s copy constructor on value+4. Complete StringBase copy, assignment, release, C-string construction and concatenation bodies were decoded, including the lock-release tail jumps. The stored string is one owning pointer, not a scalar payload inferred from node size. The helper's EH cleanup releases that pointer.

The module condition map follows 0x00227030 through 0x00224DC0 and 0x00223EC0 to the complete 34-byte copy helper at 0x00222540. It copies the key dword and all ten payload dwords at offsets +4 through +40. The search uses unsigned comparisons. This proves forty bytes of mask storage. It does not distinguish a 304-bit logical mask from a 320-bit one. The existing 0x001ED160 constructor clears ten words and sets five unchecked indices; its existing BitFlags<304> declaration is used through an inline ModelConditionFlags wrapper. The descriptive type name is retained. No new constructor identity or bit-count claim is made.

Every helper above has its full decode and `checked_callees.py` output under `build/228f10-retry/decode-*.log` and `checked-*.log`. The mask, status-mask and string widths are also compile-time assertions in the candidate.

## Calling convention and cleanup

The target takes two stack references and an ECX receiver, with `ret 8`. OpenContain's Object pointer is at +8. The complete 0x001BFAC0 body takes six stack slots and returns a count with `ret 24`. Its final slot passes unchanged through Drawable's complete 0x00413850 body and virtual slot 3. The complete W3DModelDraw implementation at 0x00775760 writes bone indices through that argument, including the missing-bone path. The bank uses the canonical intermediate Int declaration with a pointer-width cast. The matrix and position calls use the canonical Thing declarations at 0x00132200 and 0x00132CE0.

The secondary interface is at this+0x20. Slot 39 reaches 0x00221A50, which copies twelve bytes from module data+0x12C into hidden return storage and returns with `ret 8`. Its second stack slot is ignored. The established opaque Rva221A50Triple name is retained. Slot 22 reaches 0x00219460, a bare `ret 8`; the target supplies an Object pointer and a Boolean stack slot. A pointer's semantic meaning cannot be inferred from that empty callee. The primary slot 12 reaches 0x00219500, which returns AL=1 and cleans one stack slot. Unrelated aliases at those addresses are not identity evidence.

The target's four unwind states are recorded in `target-eh-complete.log`. State 0 cleans the persistent string; state 1 cleans the passenger bone string; states 2 and 3 both unwind to state 1 and clean the two candidate strings. Every cleanup tail reaches StringBase<char>::releaseBuffer through the AsciiString destructor thunk. The candidate has those four owning lifetimes, but the compiled cleanup slots have not matched retail. That remains a blocker.

## Control-flow corrections and remaining mismatch

The body now uses signed passenger-index and bone-name keys, unsigned condition keys, unconditional zero prefixing in the first suffix search, and the correct comparison receiver. Exhausting positive-count bones leaves the index at -1; non-positive bone counts take the zero-index assignment path. Condition flags are cleared on the passenger and only in the non-turret branch. The status-bit-28 tail falls back to setting position instead of skipping placement.

Retail also reloads the passenger ID at +0x42E before updating the bone-name map. The preferred body still caches that ID. This is a known semantic discrepancy in the preferred shape. The complete named-reload variant `build/228f10-retry/key-named.cpp` preserves that reload and fixes the persistent string's first stack slot, but measures worse overall. It must be considered when reopening the body; the preferred score does not certify its semantics.

| Experiment | Compiled bytes | Non-relocation differences | Raw output |
| --- | ---: | ---: | --- |
| Existing bank | 1961 | 1337 | `baseline-current-probe.log` |
| Native strings and corrected key types | 1969 | 1168 | `corrected-probe.log` |
| Eight-byte suffix buffers | 1969 | 1113 | `suffix8-probe.log` |
| Correct non-positive-count branch | 1953 | 1029 | `scan-do-probe.log` |
| Flags scoped inside non-turret branch | 1965 | 852 | `turret-scope-probe.log` |
| Canonical declarations and final bank | 1965 | 852 | `final-probe.log` |
| Cached module data | 1967 | 1009 | `module-cache-probe.log` |
| Explicit secondary-base pointer | 1979 | 1210 | `inherit-probe.log` |
| Inherited virtual call expression | 1958 | 1404 | `inherited-call-probe.log` |
| Direct temporary ID reload | 1959 | 938 | `key-reload-probe.log` |
| Named ID reload | 1971 | 1017 | `key-named-probe.log` |
| Reassigned ID reload | 1971 | 1022 | `key-update-probe.log` |
| Scoped ID reload | 1971 | 1026 | `key-scoped-probe.log` |

All table paths are relative to `build/228f10-retry/`. Eight EH configuration combinations did not improve the corrected body; their full trial sources and raw outputs are under `build/shape_search/5e0800ffd814418f912605bd43bff65f`. The generated store-order choices did not improve the preferred shape; their four trials are under `build/shape_search/b3457d4a8a974d4e9e2b25be9218d89c`. Native concat visibility, the mask constructor declaration, and alternate interface views did not change the preferred byte score. No unchanged register or x87 sweep was pursued.

The first differing byte in the preferred body is +0x30, in the instruction at +0x2D: retail constructs the persistent string at ESP+0x40 after the push; the candidate uses ESP+0x3C. The Boolean suffix flag and several scalar/string slots remain displaced. Normalized instruction streams first differ structurally at +0x344, where retail keeps the OpenContain receiver, passenger and secondary interface in a different arrangement. Twelve relocation sites also differ in layout. A justified reopening needs native STLport headers or a supported lifetime/access-expression hypothesis that preserves the ID reload and reduces these measured differences. Blind declaration reordering is not supporting evidence.

## Checks and scope

The scoped candidate gate fails byte equality. Its string references, constant references, DIR32 addresses and body guard pass. Raw output is `build/228f10-retry/final-gate.log`. The gate invokes the repository's normal verification functions on an in-memory candidate row and never edits the function ledger. CSV and pin consistency checks pass in `csv-check.log` and `pin-check.log`. The direct bank/source name comparison using the repository's regression routine passes in `final-name-pair-fixed.log`. The documented CLI accepts Git revisions rather than two file paths, so the initial literal-path CLI invocation failed; its raw diagnostic is retained in `name-regression.log`. The source claim checker reports the expected unmatched target for this partial; it is not waived. No shared header, shim, policy, tooling, ledger row or pin changes, and no full gate or Git write, are part of this attempt.

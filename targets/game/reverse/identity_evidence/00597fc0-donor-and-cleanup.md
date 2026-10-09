# Constructor donor and cleanup evidence for 0x00597FC0

The assigned Open BFME 2 donor does not reconstruct this owner. The saved BFME 1 body still has the historical `GameClient` name, but the current constructor pin identifies `Rva00597FC0Client`. This investigation preserves that bank without asserting its old identity or changing its names.

## Donor hypothesis and refutation

The supplied donor is `GameClient::GameClient` in Open BFME 2's `Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp`, at game.dat RVA `0x0023BC36`. Its constructor initializes the drawable lookup, translator array and drawable table of contents, then creates `TheDrawGroupInfo`. Its class declaration has the drawable hash at +0x18 and translator array at +0x30. It contains no Palantir callback registrations.

BFME 1's assigned constructor installs vtables `0x0110C2D8` and `0x0110C2C4`, initializes its deque at +0x20, constructs the GUI members through +0x488, and registers eleven Palantir callbacks. At +0x190 it zeros a dword at receiver+0x18 and a word at receiver+0x1C. Those operations cannot initialize the donor's drawable hash. The independently decoded AptPalantir constructor at `0x0079D9F0` calls ILT `0x0000DA58`, which resolves to this assigned constructor, with the original receiver in ECX and no stack argument.

The already landed BFME 1 `GameClient` constructor at `0x00433340` installs `0x010F37F0` and `0x010F37DC` and follows the donor's drawable and translator structure. The assigned owner's primary vtable instead has pure calls in slots 9 and 10. See [the existing identity correction](00431380-gameclient-vs-00597fc0-client.md). This refutes the same-name donor as a source of types or statement order for the assigned owner. A donor containing the assigned owner's callback strings and independently corresponding receiver fields would reopen the cross-port hypothesis.

Raw evidence is retained in `build/r00597fc0-donor/retail-vtables.log`, `donor-conflicting-vtable.log`, `decode-target.log`, `decode-caller.log`, `decode-native-gameclient.log`, and `target-history.log`. The supplied donor remains under `build/bfme2-donor/`.

## Complete target and callback contract

The assigned body decodes through its only return at +0x7A0, followed by INT3 padding. All its direct conditional branches and direct jumps remain within the decoded extent. Its epilogue restores FS:[0], returns the original receiver in EAX and uses plain RET. `checked-callees-target.log` inventories the direct calls; it does not by itself certify their declarations.

The first registration uses ILT `0x0003A0BC` to `0x0046DBC0`, the already landed `WindowManager::bindShownWithArg`. Its complete body has two RET 12 paths and reads the name address, argument dword and callback-holder pointer in that order. It stores the argument at the mapped entry's +4 field, increments the holder's refcount at pointee+4 when retaining it, and releases the by-value holder through virtual slot 0 with deleting flag 1. The caller supplies a name address, zero argument and four-byte holder. No hidden result storage appears at that call.

The first wrapper table's deleting slot goes through `0x00029C17` to `0x0058D5C0`, whose complete body returns the receiver with RET 4 after testing deleting flag 1 and conditionally calling operator delete. Its destructor call resolves to `0x0058D5F0`, a vptr store followed by RET. The invoke slot resolves through `0x0003246B` to `0x0058D260`, which loads the receiver adjustment at wrapper+0x14, adds wrapper+8 and tail-jumps through wrapper+0x10. The complete copy constructor `0x0058D220` reads all four binding dwords at source+0, +4, +8 and +0xC and writes wrapper+8, +0xC, +0x10 and +0x14. This supports the bank's multiple-inheritance binding layout, without proving the historical callback class names.

Raw decodes and checked-callee inventories are retained for those extents, the other wrapper constructor at `0x0058D270`, and the other direct callback registries at `0x0046DD10` and `0x0046DA70`. The latter registries use RET 8. The trial's new first registration declaration follows the existing landed declaration and the decoded stack contract; it adds no pin.

## Cleanup and container blockers

Retail's constructor unwind map has 24 states. States 0 and 1 destroy SubsystemInterface and Snapshot; states 2 through 8 destroy receiver members at +0x20, +0x68, +0x154, +0x17C, +0x2B8, +0x460 and +0x488. State 9 adjusts the receiver to +0x4CC and calls `0x00589B60`, which loads that slot and passes its pointer to operator delete. States 10 through 12 destroy the string at +0x4D8, four eight-byte Coord2D elements at +0x4DC, and the tree at +0x4FC. States 13 through 23 destroy the scoped callback names and return to state 12. The raw map and compiled maps are retained in `retail-eh-raw.log` and `coff-eh-audit.log`.

Six destructors in the preferred bank only store zero to their first byte. Retail's actions instead enter complete destructor bodies at `0x00591640`, `0x00591890`, `0x00591C40`, `0x00591D60`, `0x0058DBC0` and `0x005927F0`. The cleanup trial replaces those dummy stores with the decoded calls, but its funclets still reference emitted local wrapper destructors. Their direct target identities and exact action bytes have not been accepted as retail recoveries. The bank's tail action also adjusts to +0x4C4 and calls its locally emitted destructor rather than using retail's +0x4CC action. Neither trial certifies an exact unwind implementation.

The deque cleanup at `0x00595730` calls `0x005914E0`, a complete range helper that steps by twelve bytes and calls ILT `0x00026562` on every value. That route reaches `0x0058C030`, which jumps to the matched narrow-string release at `0x00887940`. The bank's `Gen_t_0058f2f0_p12cd` contains only a twelve-byte char array and has no destructor. That declaration therefore omits retail's per-value cleanup. The complete value constructor or copy helper and the other fields have not been established; the stride alone does not establish the value type.

The tree constructor allocates its sentinel and initializes links. It constructs no populated value. The complete tree destructor at `0x005908C0` exposes links, node count and node deallocation, but no value copy fields. Neither its node allocation width nor the update TU's `map<int,bool>` spelling independently proves the bank's `pair<const int,GameClientTreePayload>` or its integer payload. The key and payload remain unresolved. No STL ledger row or pin was added during the paused STLport work.

## Measured trials and reopening condition

The preferred bank, the six-destructor cleanup trial and the canonical first-registration trial each emit 1953 bytes with 108 relocations. Each probe reports 24 non-relocation differences and one shifted relocation. Each native `build.compile_function` comparison resolves every main-body REL32 symbol but fails on those same differences. The first differing byte is +0x191 in XOR at +0x190: retail uses ECX, while every candidate uses EAX. The candidate moves the two state stores across the pushed first name and ECX receiver setup, then swaps the temporary registers inside the first registration. The complete offset list is in each `*-gate.json` and raw `gate-*.log`.

Trial sources, copied COFF objects, compiler receipts and unedited probe output remain under `build/r00597fc0-donor/`. `baseline.cpp` changes only the bank's relative include paths for that scratch location. `canonical-cleanup.cpp` is the first rejected hypothesis. `canonical-signature.cpp` adds the independently decoded first-registration contract and is the second rejected hypothesis. Neither improves the saved body, and no further unchanged register experiment is justified in this run.

Reopen only with a constructor donor for this actual owner or independently established member/value construction and cleanup declarations that provide a new source-level lifetime or register witness. Fixing XOR alone would still leave the ownership and unwind checks above unresolved. The preferred tracked bank remains byte-for-byte unchanged. No source recovery or new matched byte is claimed.

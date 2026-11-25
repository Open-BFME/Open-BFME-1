# Channel nick-change callback identity

Round baseline: `90a9e571a9d3a9ad7e478bcb00089d8023bb0677`.
One logical linking repair; no reconstructed body or new code/data coverage.

## Original identity and source change

`peerGlobalCallbacksSetChannel.c` owns `_piSetChannelCallbacks`,
RVA `0x0086BA10`, 94 B through its final RET. Original instruction
`0x0086BA42: mov dword ptr [edx+0x10],0x00C6B810` binds the
userChangedNick slot to RVA `0x0086B810`. That independently witnessed
68 B callback already has exactly one authored matched row and one actual
strong provider, `_piUserChangedNickCallback` in
`peerUserChangedNickCallback.c`; both complete original extents end in RET.
There is no conflicting data owner or COMDAT selection exception.

Replace only the obsolete callback declaration/reference with the real
provider and its existing five-argument C declaration. Its CHAT/PEER handles
are `void*`; channel/oldNick/newNick are `const char*`, param is `void*`.
The original plain RET and stack-argument accesses agree with the existing
cdecl provider; its matched source supplies the full declared type contract. An unused handle alone does not prove
the original typedef spelling. Preserve the existing 12-pointer table view,
field order, slot offset, flags and all other callbacks. No body definition,
header, layout, pin, alias or linker directive is added.

The native `dir32_record.py retire` accepts the old recorded identity at
VA `0x00C6B810` for the existing actual owner. It is the sole record writer;
the native trailer is retained for the commit. No baseline was edited.

## Changed prerequisite and measured controls

The previous refusal in `peer-callback-owner-retirement.md` was specifically
native C code ownership for this DIR32. Existing verifier commit
`8337c57e34b8f7be226a42017bb89af2bf8cfebb` now recognizes unique authored
matched native-C rows, while retaining data conflicts and ambiguity checks.
No tool change is part of this repair.

The ordinary before/after family builds pass 158/158 rows in five TUs,
66 DIR32 checks, five string literals and two empty strings, with zero
baselined body findings and three proven static references. FDU says all
defined functions are already matched. A separate strict comparison of all
five actual normal objects permits exactly the DIR32 target-name change at
caller offset `+0x35`. All preexisting runtime/FPO/COMDAT/EH/CRT/SafeSEH/
directive sections, definitions and weak edges otherwise remain equal;
there are no additional functions, data, initializers or helper emissions.
Actual compiler arguments/compiler digest/generated INCLUDE/LIB/PATH are
unchanged. Full inherited host-environment equality is not claimed.

Two transitive native RetailTruth results remain `unknown`: the 120 B
`_piPlayerChangedNick` calls its genuine TU-static 225 B `_piAddPlayer`,
and the 79 B `_piAddPlayerChangedNickCallback` calls its genuine TU-static
197 B `_piAddCallback`. The normal full-source byte verifier accepts these
with static ownership; no relocation was guessed or pinned. The 79 B source
is freshly byte-verified but not cacheable because native dependency analysis
cannot resolve its macro/parent-traversing search roots. Its ordinary-current
result remains false; no current/retail result is manufactured.

## Link preview and limits

Before: normal `link_check.py peerGlobalCallbacksSetChannel.c`, exit 1,
585.2 s, LINKED 0 -> 0; sole missing `_piChannelUserChangedNickA`.
After: normal native exit 0, 1022.5 s, 1/1 LINKS, LINKED 0 -> 94.
Both are scoped legacy-census previews anchored to `42237e2367`
(2026-11-21 10:53), not a new full-image census or a runtime test.
Existing caller 94 B and callback 68 B are retained; new C++ exact bytes,
new unique code bytes and new static-data bytes are all zero.

## Donor and header review

Read-only historical BFME2 donor
`e2e99959950e6eebfe1ced5663aa05de320afc52`, checked 2026-11-24,
and current native sweep fingerprints remain valid. Reviewed corresponding
`Code/GameEngine/Source/GameNetwork/GameSpy/peer/` setter/provider source,
its relevant history, and the previous handoff. The donor setter still uses
the obsolete spelling; its provider uses a forbidden `/alternatename`.
That adaptation is rejected. No donor source/address/flag/linker alias is
ported; BFME1's original pointer and actual owned provider establish this
repair. Donor naming agreement alone is not used as identity evidence.

An exact search of all `game/**/*.h` and `inputs/reference/shims/**/*.h`
finds no chatChannelCallbacks/CHAT/piUserChangedNickCallback declaration.
The sweep Peer.h describes PEERCallbacks, a different SDK interface.
The native header-adoption rules therefore provide no existing header for
this split. No new shared model is introduced.

Independent read-only review also verified all five actual object pairs and
366 relevant sections with no blocking finding. The sibling JSON binds the
source/object/receipt hashes.

Related unchanged callback spellings for ChangeNick and AuthenticateCDKey
were reviewed in the previous family handoff and remain in the current
peerOperationsListGroupRooms.cpp declarations/call sites and recorded at
VA 0x00C5FCD0/0x00C60020. They are not changed or claimed by this one-slot task. HostedGameRequest was inspected read-only and parked
on separate genuine constructor/vtable prerequisites, with no source trial.

Private diagnostics retain complete original decodes, source/control copies,
five normal objects before/after, compiler context and claim fences. The
tracked review note should carry compact results/hashes, not duplicate large
inventories. Publication follows the normal hooks and claim-lease trailers; no runtime
result or global census improvement is inferred from this scoped preview.

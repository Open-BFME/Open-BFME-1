# 006ADAE0: bounded native whole-TU recheck, not landable

No new C++ recovery. Root holds the claim. No production source, flags,
register, ledger, claim, Git/index, shared match object, or generated source
was changed. Three private compiler controls were run under their respective
original source directives; no flag sweep or new lookup source variants.

## Physical extent and identity

The complete target is 458 bytes, 006ADAE0..006ADCAA. Sixteen INT3 bytes
precede the entry, RET8 begins at +1C7 and is immediately followed by INT3
padding. Ghidra independently records 458 bytes; native BoundaryValidator
accepts the entry, whole range and two-stack-argument thiscall arity without
warnings. Lookup69D620 is similarly INT3-bounded with RET12 at +11A and
285-byte extent. Native list erase69DBE0 has a complete 73-byte RET8 body.
These are physical evidence, not the picker's inventory-count estimate.

Two current native consumer objects bind the exact existing ILT21C1F:
Rva006AE610SetIfGreater.cpp at 006AE610 +1D, and BfmeConv906.cpp's 006ADD20
+0F. The entire consumer source row sets are strict-equal (1/1 and 6/6),
their objects report current, and there are no unresolved calls. The ILT
preserves the existing receiver/two-argument ABI. It establishes routing,
not the proprietary helper name. The address-qualified existing helper
spelling was retained for this diagnosis. No new semantic name or pin.

## Native controls

| Control | Existing real-TU rows | Helper6ADAE0 | Lookup69D620 |
|---|---|---|---|
| Unmodified bank, bank's original flags | not the real TU | 458B, zero masked differences; strict fails on two unknown callees | 285B, 13 strict differences |
| Complete current MilesAudioManager.cpp, original flags | 2/2 exact | absent | absent |
| Complete current TU plus bank, unchanged current flags | 2/2 exact | 324B versus458; many opaque STL calls | 257B versus285 |

The real TU explicitly has /Ob0. The bank has default /Ob1 behavior. This
is a measured whole-TU integration failure, not permission to silently
transfer bank flags. The sole original quoted include was privately mapped
to the exact same canonical UnsignedInt header; path and hash are recorded.
No existing body was split out. The private full-TU experiment remains
nonlandable and is not an integration patch.

Under bank flags, native list<ThingRef>::erase69DBE0 is strict-exact73B and
deque<ThingRef>::_M_push_back_aux_v6A7DF0 is strict-exact212B. Their allocator
and map-reallocation bindings resolve through the existing native names.
The helper itself still has unbound getSlot and native list::erase calls;
the masked458B score therefore is not a strict match. Its visible lookup
still has the known13-byte scratch-allocation/cleanup-crossjump residue.
The prior lookup record has201 trials; none was repeated or hidden behind
an unmatched provider. Native EH predecessor graphs agree for the bank's
helper and lookup, with one state each, but that does not repair main bytes
or unbound calls.

The old handoff's suggested --replace-rva69DBE0 alone is not a current safe
admission recipe: the erase_Open269DBE0 row is existing handwritten C++,
not gen-dump. Any future identity correction must follow the current native
--correct-identity/evidence route and normal verification. No such operation
was attempted. New provider/link ownership remains unverified because the
strict source prerequisites already fail. No linked-byte claim is made.

## Donor and target facts

BFME2 reference147fd3e52b36ee0306aaeef5b316beb09f7c7671, current
Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp lines
6540 onward, has WorldBuilder-led putPlayingMusicOnStack at5A812..5A908:
select a per-view music system, push a counted playing reference, clear the
active slot or pause/requeue a stream. That supports the structural family,
including visible nonescaping deque helpers, not BFME1's offsets or name.
BFME2 uses a three-argument lookup, different stack/list offsets and stream
wrapper, so it is not a directly interchangeable target implementation.
Both tested public/private HH putPlayingMusicOnStack decorations contradict
BFME1's ILT window. No rename is justified by the donor alone.

Zero Hour referenced7c72d052989ca2689a5eaeefda8e6ebca1f9441, GeneralsMD
MilesAudioManager.cpp, supplies raw-pointer list/pause-stream operations.
Its raw pointers cannot replace BFME1's decoded atomic counted handles.
BFME1's already matched PlayingAudio constructor/destructor, stop chain,
lookup consumers and the target's decoded offsets remain the local ABI
evidence. No new shared header, canonical class or layout was created.

The target has no address-bound application data; its DIR32 uses are the
native exception chain/handler and actual PE IAT slots for increment,
decrement and AIL_pause_stream. Its field accesses and index dimensions are
the original bank's observed target views, not new complete EA declarations.

## Reproduction and retained inputs

Run control-006adae0-whole-tu.py and audit-006adae0-relationships.py from the
BFME1 root under the established native environment. All compiler output is
under build/agent-melee-20261120/006adae0-whole-tu/. Complete flags, hashes,
row comparisons, EH maps, call bindings and physical boundary bytes are in
006adae0-whole-tu-controls.json and006adae0-relationships.json.

Original bank SHA256:
c371994ded0bef795f544b18e728b290097bc5322b6c9cfe7b55713850ed896d.
Original real TU SHA256:
fec9f7bacb6933a6fa707d2015347bb257affa013e20be743ce6eb8ed6ac8a37.
Five shared generated source files were only streamed for diagnostic hashes;
none was written. Counts: zero promoted bodies, zero new exact C++ bytes.

# Quickmatch map-pointer partition contract: 0x00450B90 / 0x00451E60 / 0x00452120

## Independent native evidence

Baseline: retail-1.03-unpacked lotrbfme.exe, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Actual Ghidra MCP read_bytes responses on 2026-10-04 exactly reproduce the
208/30/30-byte extents at VA 00850B90/00851E60/00852120 (image base 00400000).
The three byte-block SHA-256 values are respectively
`1f1d3ab9a1ca3aad52ed8f3ed815aaec24590111797b60c623d15183b2e32565`,
`d27bdd4b057b081c891c8e5a94306151a13ea888f08059a168eb280eedfd1c15`, and
`33730515783254a9058af9de7153c33c560663e9db7d88896471f92af6718dbc`.
Ghidra closed with save=False. Its decompiler infers void and omits the unused
fourth argument; the native assembly and caller stack accounting override
that inference. Its undefined outer ILT xrefs are not absence evidence.

The 208-byte leaf is cdecl, accepting first, last, a four-byte predicate, and
an unused category address. It swaps four-byte pointer slots and returns an
iterator in EAX. Each search applies the same six mask bits to read-only
bytes at metadata offsets 24/25/26: select official/nonofficial by bits01/02;
reject multiplayer/nonmultiplayer by04/08; reject scenario/nonscenario by10/20.
MapMetaData construction/assignment and the independently recovered collector
establish the BFME flags. name_oracle has no BFME witness; its ZH offset25
hint is official and must not replace BFME's inserted scenario byte.

The matched MapCache::findMap at454500 returns const MapMetaData*. The native
fillMapMask body at55AE10 appends this result directly and calls this leaf at
55AFB2 with mask25 (0x19), retaining official multiplayer nonscenario maps.
This establishes the canonical const MapMetaData** iterator, beyond what raw
pointer bits establish alone. The predicate's shared declaration deliberately
matches the exact fillMapMask bank: struct Rva0055AE10MapPredicate, int value,
inline int constructor, and bool operator()(const MapMetaData*) const. The
address records that the original predicate name remains unknown. The prefix
view is not a competing full MapMetaData layout.

451E60 has three cdecl arguments. Its initial push ecx allocates four local
bytes; it passes a one-byte category temporary, predicate, last, first to
ILT43004, preserves EAX, discards20 bytes, and returns. A native STLport
random_access_iterator_tag temporary binds to the bidirectional overload.
Neither the category's original empty concrete type nor the wrapper's original
semantic name is distinguishable. In particular, partition, uninitialized_copy,
and uninitialized_fill_n templates can all emit these30 wrapper instruction
bytes. Therefore the wrapper keeps its address-qualified identity.

452120 has two cdecl arguments: predicate and a read-only two-iterator prefix.
It reads last at[arg2+4], first at[arg2], passes its dead arg2 home as category,
and calls ILT43004. No vector receiver or capacity field is witnessed. The
canonical contract emits all30 bytes without the old _ReadWriteBarrier; that
artificial barrier is removed rather than carried forward.

## Retired identities and consumer closure

The old Rva00450B90Item**/Rva00450B90Predicate specialization encoded a mutable
fabricated struct payload, not the independently witnessed const class pointer.
The old range signature carried that same private payload contract. Both are
replaced coherently; no aliases, adapters, extra native bodies, or new pins
bridge the old signatures. The genuine vendored STLport bidirectional leaf is
explicitly instantiated, and 451E60's actual native wrapper is authored beside it.

The generated Gen_helpmd_00451e60 row claimed uninitialized_copy, but retail
partitions pointers in place. The generated __uninitialized_copy pin to450B90
is independently false: fam_013's own current provider is126 bytes, calls a
12-byte object's copy constructor, and has EH cleanup; retail is208 bytes with
no calls or EH. Remove this pin, not its unrelated generated code or siblings.
The generated fam_013 source is untouched. Its237-row baseline gate passed;
only this one30-byte row is rehomed, retaining236 siblings.

An E8/E9 scan across every PE section, validated at instruction boundaries in
containing ledger bodies, finds only451E75,452135,55AFB2 calling ILT43004 and
ILT31C8C/7D4C/43004 targeting the three bodies. It finds no direct caller of
either outer wrapper or its ILT; indirect callers are not excluded. Authored
source search confines old item/predicate/range types to these two TUs. The
canonical bank remains evidence, unchanged. Address-only generated thunk/body
routes are preserved. The range's old signature and old leaf helper providers
have no additional authored typed production consumer.

## Whole objects and scope

Before: leaf has five function COMDATs (predicate90, swap19, iter_swap19,
leaf208, standard wrapper30) and an unused anchor datum. After: the same five
code roles use canonical types, with the wrapper address-qualified; the unused
anchor is removed. The leaf has no undefined/runtime/EH imports. The range
retains its30-byte function and all538 incidental STLport data COMDATs, with
only its canonical leaf REL32 reference. The complete fam_013 object and its
13318 COMDATs remain selected through its unchanged sibling ledger ownership.
The false generated specialization and EH machinery remain incidental code;
they acquire no replacement retail pin or claimed identity.

All three exact extents are verified independently with the original MSVC7.1.
The two wrappers' sole REL32 operand is+22 and routes through ILT43004 to the
canonical leaf; EAX return and cdecl arity remain intact. Supported delta,
header-dependent, pin-consumer, and current selected-provider gates must pass.
This is a bounded contract repair, not a global/native-link gain:238 bytes
were already authored, and only451E60's30 bytes are newly authored source.
Vector/collector, fillMapMask bank, filename sorts, and string scope are unchanged.

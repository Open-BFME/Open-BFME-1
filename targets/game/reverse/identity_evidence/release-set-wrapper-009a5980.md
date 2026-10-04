# Release-set wrapper at RVA 0x009A5980

This is a correction of an unresolved source-local stand-in and a generated
scaffold owner. It does not recover the wrapper's original semantic name.
`bfmeTwoBZB` was only an undefined declaration and six calls in
`game/GameEngine/Source/Common/BfmeReleaseSetBZB.cpp`; its symbols.csv row says
only `pin` at 0x009A5980. The caller's old ledger note cites those pinned labels
as its identity evidence. That circular metadata does not establish an original
descriptive identity for this callee. The pre-change ledger owns the address as
`?j_009a5980@@YAXXZ`, a generated no-argument wrapper in `thunks_037.cpp`.
No retail export names `bfmeTwoBZB` or resolves through initial ILT to either
0x009A5980 or 0x009A58E0. Absence of an export does not recover another name.

The replacement free function `Rva009A5980(void*)` deliberately admits the
unknown identity. It preserves the real wrapper and its physical contract;
it does not promote the different direct-body identity or a guessed allocator
name. No metric is used to justify this naming correction. Other old pins
at this address remain untouched; this is only the exact source pair below.

## Exact snapshots

- Base: `ef91c2a8a8f43af92b3c8dd187ecb364a35573b8`
- Path before and after: `game/GameEngine/Source/Common/BfmeReleaseSetBZB.cpp`
- Correction pair: `bfmeTwoBZB` -> `Rva009A5980`
- Before source SHA-256: `0b5adaa49c87ed1fccdaae098d44887c582a5f0692a0d2a787b2d3d846d6f58f`
- After source SHA-256: `3c5e09860403a6902a11a1a8442fad68f1f2bbce7a63600af80b842daac94f68`
- Baseline PE SHA-256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`

## Independently decoded complete retail bodies

Caller `[0x009A5B80,0x009A5C36)` is exactly 182 bytes. RET at 0x009A5B70
and fifteen INT3 bytes precede it; its final RET at 0x009A5C35 is followed by
ten INT3 bytes. It preserves ESI/EDI and reads one incoming stack pointer.
Its direct call sites are 0x009A5B93, 0x009A5BB2, 0x009A5BCE, 0x009A5BEA,
0x009A5C06 and 0x009A5C22. Each pushes one pointer and then cleans four stack
bytes. Signed E8 displacement arithmetic at every site yields 0x009A5980;
none calls 0x009A58E0. EAX is unused after these calls.

Wrapper `[0x009A5980,0x009A5985)` is exactly `E9 5B FF FF FF`: signed
relative displacement -165, so 0x009A5985 - 165 = 0x009A58E0. Previous RET
at 0x009A597D plus two INT3 bytes establishes its start; eleven INT3 bytes
follow it before the next body at 0x009A5990. It is outside the independently
recognized packed initial ILT `[0x00001005,0x0004B6BE)`, 60,965 entries.
Thus this is a real padded tail function, not an ILT entry to erase from the
identity chain. It forwards the untouched frame and cdecl pointer argument.

Direct provider `[0x009A58E0,0x009A58FD)` is exactly 29 bytes, followed by
three INT3 bytes. It loads ECX from VA 0x0134C7DC. If nonzero, it loads the
pointer from [ESP+4], loads the receiver's vptr, pushes zero and the pointer,
calls slot +4, and executes plain RET. The virtual method must clean those
two pushed arguments. If zero, the provider tail-jumps through VA 0x013593D4,
verified in the PE import table as MSVCR71.dll!free. Together with caller
cleanup and the unused return value this proves compatible cdecl void(void*)
for both the wrapper and the provider, retaining their distinct addresses.

The unchanged provider is `bfmeGo930C(void*)` in `BfmeConv930.cpp`. Its whole
29-byte code and both DIR32 bindings match retail, with the existing sole
`Rva009A58C0::s_value` storage owner and real free import. Its other three
function bodies are unchanged and also pass complete byte gates.

### Caller complete retail bytes

SHA-256: `08d171a1ce59ecf666cf100d736b36c93f90cd98596218653cc2f315ec9e485e`

```text
568b7424088b86b80000005733ff3bc7740950e8e8fdffff83c4048b86a00000003bc789beb800000089bebc000000740950e8c9fdffff83c4048b86a40000003bc789bea0000000897e34740950e8adfdffff83c4048b86a80000003bc789bea4000000897e3c740950e891fdffff83c4048b86ac0000003bc789bea8000000897e24740950e875fdffff83c4048b86b00000003bc789beac000000897e28740950e859fdffff83c40489beb0000000897e2c5f5ec3
```

### Wrapper complete retail bytes

SHA-256: `5fc155db69abe4ddbf3c6cdcfe0683d805109c24e5bcf05f7fb5517a21b26e74`

```text
e95bffffff
```

### Provider complete retail bytes

SHA-256: `bbda4af23883ba3f0c41b6e5aae742033aad68f93d1fdd295f16f0838947a948`

```text
8b0ddcc7340185c9740d8b5424048b016a0052ff5004c3ff25d4933501
```

## Source, COFF and ownership proof

The noinline typed wrapper is necessary to preserve six same-TU calls to the
separate wrapper. Original caller code remains all 182 identical raw bytes;
only the six REL32 names at offsets +20, +51, +79, +107, +135 and +163 change.
Each still resolves to 0x009A5980. New helper code is exactly E9 plus one REL32
at offset +1 to `?bfmeGo930C@@YAXPAX@Z` at 0x009A58E0. It is an EXTERNAL
function in a NODUPLICATES COMDAT, not a weak/COMMON/associative code alias.
The original directives, caller section aux record and frame bytes are
unchanged; only the helper section, helper frame and required indices/layout
are added. Provider and generated objects are wholly byte-identical.

Only the old generated ledger row is replaced, at its original position,
with the same five-byte extent. The supported add_match flow appends its
explicit tombstone. No generated source, provider source, pin, baseline or
guard is changed. This snapshot-bound correction does not authorize any
other rename. Complete source gates pass 426/426, with string/constant/DIR32
checks, global pin checks, and scoped DIR32 consistency. Independent read-only
review verified the physical ABI and parsed the complete final COFF objects.

The historical source preview is 0->187 bytes: 182 newly unblocked caller
bytes and five bytes of existing generated-wrapper ownership migration.
Those five bytes are not new instruction recovery. The new wrapper has one
current emitter and no historical MAP receipt. The old generated symbol
remains emitted by unchanged generated source but has no live ledger owner.
The frozen index cannot establish fresh global selection or retirement;
that impact is unmeasured. The provider TU retains three unrelated unresolved
names. No recursive/full LINK claim is made.

Strict classifier blob remains
`88cf1f2ea4eebc05f6fec948d765fa8d47da831e`; immutable index SHA-256 remains
`034ebdbd7f13546b5fd7f5f79240e5d75e973fabcc4bad425a0f4ee9dd0d9573`.
Local verification receipts are in `build/release_set_audit`.

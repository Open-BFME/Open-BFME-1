# RVA 0x00077340: AsciiString-key tree erase, opaque specialization

## Boundary, ABI, and independent identity

Retail SHA256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
The executable's image base is `0x00400000`; addresses below are RVAs.
The body occupies `[0x00077340, 0x0007737D)`, exactly 61 bytes. INT3 padding
ends immediately before its first PUSH and begins immediately after `ret 4`.
Fresh Ghidra MCP read_bytes, disassemble, decompile_function, and list_xrefs
calls independently confirmed the body and routes on 2026-10-04. Nine relevant
MCP byte blocks were compared with the pinned PE; all matched with no tool
errors. The caller check used VA 0x0085790A (RVA 0x0045790A). An initial
unrelated window mistakenly requested at VA 0x0045790A is retained separately
in the scratch receipts but is not evidence for the MapCache caller.
Decompiled C is supporting control-flow evidence, not byte-match proof.

The live owner is passed in ECX and saved in EBX. There is one root-node
pointer at entry ESP+4 (ESP+0xC after two PUSHes). The function cleans that
argument with `ret 4`. Recursive calls use the original owner in ECX and one
child argument. Observed callers do not consume a return value.

The matched `MapCache::loadUserMaps` body at `0x004577C0` calls ILT
`0x0000DB2A` at `0x0045791A` (+0x15A). This thunk jumps to `0x00077340`.
The independently reconstructed caller and its existing evidence file
`mapcache-load-user-maps-004577c0.md` identify the erased seen-map's key as
AsciiString. The mapped value is observed as a byte in that caller, but the
semantic char-versus-bool choice is unproved. Its operator[] keeps its existing
char ABI. This recovery therefore claims only address-derived owner/node
names, not an invented `_Rb_tree<...>` specialization. The four physical bytes
at node+0x14 remain an opaque field/padding region. The first eight bytes are
also opaque; only the child links actually used here are named.

Other decoded callers at `0x00077690`, `0x00077FC0`, and `0x00341840` still
have generated template identities. Their placeholder types are not evidence
of an integer key, mapped identity, or duplicate real specialization.

## Operations and exact callee contracts

- Read node+0x0C and recurse through `0x0000DB2A` using the same owner.
- Save node+0x08 before releasing any storage, then use that child as the next
  loop node. These are the usual right/left tree-erasure links.
- Pass node+0x10 in ECX to `0x000479D3`, with no stack arguments or result.
- Push size `0x18`, then the node pointer; call `0x0082E5F0`, and remove eight
  stack bytes at the caller. Thus this helper is cdecl(pointer, unsigned size).

The key-release route is established by raw branch displacements:

```
0x00077361  e8 6d 06 fd ff  call 0x000479D3
0x000479D3  e9 f8 a9 02 00  jmp  0x000723D0
0x000723D0  e9 6b 55 81 00  jmp  0x00887940
```

The final body is exported as private
`?releaseBuffer@?$StringBase@D@@AAEXXZ`, and is reconstructed in
`game/Libraries/Source/string/StringBase.cpp`. Its char-buffer refcount,
free, and pointer-clear operations independently support the AsciiString key
interpretation. The canonical `ascii_string.h`/`string_base.h` layout is used;
there is no redeclaration of either type.

The existing verifier's relocation candidate policy stops the two-hop release
route at `0x000723D0`. A direct canonical releaseBuffer/destructor expression
therefore has the exact instruction shape but is rejected at this relocation.
The source preserves the existing address-named `j_000479d3` ledger identity
and uses a four-byte MSVC member-pointer union to give that existing thunk its
independently observed thiscall receiver ABI. It emits a direct call, not an
indirect call. This does not define the thunk, invent a callee alias, add a pin,
or change verifier policy. No cast helper COMDAT is emitted.

The allocator uses the existing STLport header's public inline `deallocate`
entry; the constant 24-byte size folds the large-allocation branch away and
emits the canonical private
`?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z` call. Raw retail
`0x0082E5F0` buckets `(size-1)>>3`, links the node into the small-block free
list, and uses the allocator lock. No node allocator redeclaration is needed.

The canonical header also emits two SELECT_ANY helper COMDATs. The public
`deallocate` wrapper independently byte-matches its existing 34-byte retail
body at `0x00061D10`, with canonical delete and private allocator relocations.
The five-byte `__stl_delete` forwarder has no independent pinned retail identity;
its bytes/relocations match existing copies, including the historical selected
provider. A read-only historical-census diagnostic with this object appended
reported no newly wrong selected definitions. This is bounded selection
evidence, not a fresh full LINKED verification.

## Byte verification and impact

The recovered body has exactly three COFF REL32 relocations:

```
+0x17 ?erase@Rva00077340Owner@@QAEXPAURva00077340Node@@@Z
+0x22 ?j_000479d3@@YAXXZ
+0x2A ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z
```

The patched 61 bytes are identical to retail:

```
53568b74240c85f68bd9742c578d49008b460c508bcbe8cf67f9ff8b7e088d4e10e86d06fdff6a1856e882727b0083c40885ff8bf775d95f5e5bc20400
```

`tools/add_match.py --replace-rva 0x00077340` verified the replacement and
retired the generated ledger row. The generated TU is deliberately untouched.
`tools/explain_mismatch.py` reports `classification: exact match` and a
61-byte compiled symbol. The real MapCache caller still verifies at its full
1358-byte extent.

The unchanged
`tools/tests/test_inventory.py::test_game_end_closure_coverage_never_regresses`
now passes. The original corrected MapCache extent newly exposed this helper
in the E_leave closure; native recovery reduces that SMALL tier from 23/3304
to the frozen 22/3243 without editing any test, baseline, seed, or extent.
This is one genuine 61-byte recovery, not a LINKED-byte claim.

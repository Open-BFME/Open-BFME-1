# RefCountClass deleting-destructor identity

Baseline: `bfme1.retail-1.03-unpacked`, image base `0x00400000`, executable
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Verified 2026-10-03 using Ghidra 12.1.2 / pyghidra-mcp 0.2.7 `read_bytes`,
`disassemble`, and `list_xrefs`, then independently reading the same addresses
through the repository's retail PE reader. All quoted byte reads agreed.
Addresses below are explicitly VA or RVA.

## Independent owner and route witnesses

The matched RefCountClass constructor at RVA `0x005F38A0` stores vptr
VA `0x011135AC` and reference count 1 at `this+4`. The matched
`RefCountClass::Delete_This` at RVA `0x005F38C0` null-tests `this`, pushes 1,
and calls vtable slot `+4`. This agrees with the canonical `WWLib/refcount.h`:
`Delete_This` is the first virtual and the protected virtual destructor is second.
The in-place destructor at RVA `0x005F38D0` is `C7 01 AC 35 11 01 C3`.

The table at VA `0x011135AC` contains these two little-endian words:

- VA `0x00405D5D`: `E9 5E DB 5E 00`, routing to VA `0x009F38C0`
  (the independently matched `Delete_This`).
- VA `0x0041C4A4`: `E9 37 74 5D 00`, routing to VA `0x009F38E0`
  / RVA `0x005F38E0` (the deleting-destructor slot).

RVA `0x005F38E0` is exactly 31 bytes, followed by `CC`:

```text
F6 44 24 04 01 56 8B F1 C7 06 AC 35 11 01 74 09
56 E8 BA E5 28 00 83 C4 04 8B C6 5E C2 04 00
```

It tests the scalar-delete flag, saves `this`, stores RefCountClass's vptr,
conditionally calls the existing `operator delete(void*)` at RVA `0x00881EB0`,
returns `this`, and uses `RET 4`. `tools/callees.py 0x005F38E0 31` confirms
that sole direct target. The target's full 21-byte body null-checks its argument
and calls the retail memory-manager function pointer with two arguments; its existing `mem_ops.cpp`
identity and cdecl ABI agree. No new callee or pin is needed.

## Reject the old CullSystem alias

RVA `0x008E2260` is also 31 bytes but stores VA `0x01137818`, not
RefCountClass's vtable. The first word at VA `0x01137818` is VA `0x00CE2260`,
which points back to that CullSystem deleting destructor. Its existing
`??_GCullSystemClass@@UAEPAXI@Z` source is retained unchanged. The old
`??_GRefCountClass@@MAEPAXI@Z` alias at RVA `0x008E2260` is therefore false,
regardless of the successful relocation-tolerant byte comparison.

## Reject the old PersistClass emitter

The old RVA `0x005F38E0` row named `??_GPersistClass@@UAEPAXI@Z` came from
a TU-local fake PersistClass base in `RenderObjClassDestructorThunk.cpp`.
The parent destructor at RVA `0x0091FC10` has a third independent witness:
after destroying its secondary base at `this+8`, its instruction at VA
`0x00D1FC74` stores VA `0x011135AC` into the primary base. Ghidra's xrefs
also identify this exact final store. It is RefCountClass's primary base.

Use the existing canonical `refcount.h`, remove the fake PersistClass and
truncated RefCountClass declarations, and derive RenderObjClass from
RefCountClass. The native compiler now emits the protected deleting destructor
`??_GRefCountClass@@MAEPAXI@Z` at the proven RVA. Preserve the matched parent
119-byte body and its 39-byte secondary-base EH cleanup at RVA `0x00C5C148`;
including the header only renumbers that cleanup's local COFF label from
`$L384` to `$L733`. No shared-header change, guessed pin, alternate name, or
new scalar layout is required. Other pre-existing CullSystem aliases and other
RenderObjClass duplicate emitters are outside this scoped repair.

## Verification and remaining link scope

- `./build.sh` passes all three rows in the repaired provider, and 29/29 functions
  with 21 DIR32 references when checking that source together with `cullsys.cpp`
  and `RenderObjClassCtor_Thunk.cpp`. The existing memory-operations provider
  independently passes its four rows and four DIR32 references.
- `tools/check_csv.py` and `tools/pin_consistency.py --check` pass. No pin changed.
  The one-identity surplus drops by one; no retail byte coverage is removed.
- `tools/link_check.py` before and after passes the three provider/consumer
  sources together against the official `1677ebdc33` census snapshot, dated
  2026-10-03 17:32 UTC. CullSystem links (359 bytes) in both previews. The repaired
  destructor TU no longer reports the fake Persist destructor/table conflicts.
  Its existing RenderObj destructor duplicate and selected-definition conflicts
  remain, together with the already-known primary RenderObj table selection
  blocker exposed under its correct RefCount base identity. The constructor
  retains its existing table/destructor blockers and unresolved
  `WW3D::DefaultNativeScreenSize`.
- This establishes a minimal identity repair, not a new full-tree census or a
  new completely linked translation unit. Other snapshot entries are not
  refreshed; hosted weak-root proofs remain disabled locally.

# Data identity at VA 0x012B9690

Unresolved: const char* table into 20-byte value buffers.

## Retail facts and extent

The candidate lies at VA 0x012B9690, RVA 0x00EB9690, in `.data`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B9690-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan.

Eight initial pointers target VA 0x012F7468 plus 20 times the entry index. The reference s_values points into PeerThreadClass::s_valueBuffers, and retail six-key dispatchers pass this base alongside the verified key base. DualIndexedDispatchSecond is named at VA 0x012B96A8, inside a proposed eight-entry extent. The values are buffer pointers, not integers.

The candidate extent is 32 bytes. Its initial bytes are `68 74 2f 01 7c 74 2f 01 90 74 2f 01 a4 74 2f 01 b8 74 2f 01 cc 74 2f 01 e0 74 2f 01 f4 74 2f 01`. This is a candidate of eight four-byte pointer elements; the six-element boundary is disputed. Pointer-word targets are `0x012F7468`, `0x012F747C`, `0x012F7490`, `0x012F74A4`, `0x012F74B8`, `0x012F74CC`, `0x012F74E0`, `0x012F74F4`. No data row overlaps this range. The interior DIR32 name described below prevents accepting it. There is no PE base-relocation directory. No COFF initializer relocation count is accepted for this unresolved address. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00643BC0` (`?d_00643bc0@@YAXXZ`, address immediate), `0x00643C10` (`?d_00643c10@@YAXXZ`, address immediate), `0x0064FB90` (`?Thread_Function@PeerThreadClass@@UAEXXZ`, address immediate).

## Receiver and argument contract

The ECX dispatchers pass this address as the final pointer-array argument of the same cdecl API used for s_keys. No direct write to a table element was found; writes target the buffers.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B9690-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?DualIndexedDispatchSixSecond@@3HA`: 1 game file(s).
- `?s_values@PeerThreadClass@@0PAPBDA`: 2 game file(s).

## Change and verification

No changes. Two source files define six-entry s_values arrays. The interior boundary and the complete eight-entry ownership remain to be settled together with s_keys.

The raw datum gate output is `build/rlink/identity-data-20261005/retail-details.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A proven bound and owner for all eight pointers, with the +24 named boundary resolved, would settle this. A separate six-pointer array and adjacent two-pointer array would refute the eight-element hypothesis.

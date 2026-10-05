# Data identity at VA 0x012D6D80

Unresolved: WW3D::PrelitMode, PrelitModeEnum scalar.

## Retail facts and extent

The candidate lies at VA 0x012D6D80, RVA 0x00ED6D80, in `.data`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012D6D80-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan.

Retail initially holds 1, the reference PRELIT_MODE_LIGHTMAP_MULTI_PASS. W3DDisplay::init at RVA 0x006ED5B0 stores 1; the setter at RVA 0x006E7040 stores its argument; MeshModelClass::Load_W3D at RVA 0x009702F0 switches on 0, 1 and 2 to select prelit loading modes. The reference ww3d.h and ww3d.cpp declare and define private PrelitMode with that enum type. The int placeholders identify the same physical scalar but discard the proven enum role.

The candidate extent is 4 bytes. Its initial bytes are `01 00 00 00`. This is one object. No data row or DIR32 name lies strictly inside the candidate range. There is no PE base-relocation directory. No COFF initializer relocation count is accepted for this unresolved address. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x006E7040` (`?store@Rva006E7040@@SAXH@Z`, write), `0x006ED5B0` (`?init@W3DDisplay@@UAEXXZ`, write), `0x009702F0` (`?Load_W3D@MeshModelClass@@UAE_NAAVChunkLoadClass@@@Z`, read).

## Receiver and argument contract

The setter is cdecl with one dword argument; the display and mesh loader use ECX receivers. The datum is a mode selector, not a pointer.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012D6D80-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?PrelitMode@WW3D@@0W4PrelitModeEnum@1@A`: 2 game file(s).
- `?Rva012D6D80@WW3D@@0HA`: 1 game file(s).
- `?s_value@Rva006E7040@@2HA`: 1 game file(s).

## Change and verification

No changes. add_data_match.py refuses the private enum member because it cannot be named for sizeof. The private-table exemption does not authorize a scalar without a data row, and this run forbids shared-header changes.

The raw datum gate output is `build/rlink/identity-data-20261005/private-prelit-probe.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A supported private scalar size probe and a passing byte gate for the canonical enum would settle application. A mesh-mode branch inconsistent with the reference enum, or a different initial value, would refute its identity.

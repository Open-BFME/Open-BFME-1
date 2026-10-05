# Data identity at VA 0x012D6D98

Unresolved: WW3D::TextureFilter, int scalar.

## Retail facts and extent

The candidate lies at VA 0x012D6D98, RVA 0x00ED6D98, in `.data`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012D6D98-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan.

Set_Texture_Filter at RVA 0x008FD2B0 clamps an int argument to 0 through 2, stores this dword, and tail-calls the filter initializer at RVA 0x00920D10. DX8Wrapper::Do_Onetime_Device_Dependent_Inits at RVA 0x0090ADC0 reads it and calls the same initializer. The reference declares WW3D::TextureFilter as private int, so the standalone TextureFilterMode enum is a callee view, not the storage type. Retail initially holds 1; the current owner source instead initializes 0.

The candidate extent is 4 bytes. Its initial bytes are `01 00 00 00`. This is one object. No data row or DIR32 name lies strictly inside the candidate range. There is no PE base-relocation directory. No COFF initializer relocation count is accepted for this unresolved address. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x008FD2B0` (`?Set_Texture_Filter@WW3D@@SAXH@Z`, write), `0x0090ADC0` (`?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ`, read).

## Receiver and argument contract

The setter is cdecl with one int argument. The one-time initializer has no receiver or arguments. Its enum parameter view does not determine the datum type.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012D6D98-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?Rva012D6D98FilterMode@@3W4TextureFilterMode@@A`: 1 game file(s).
- `?TextureFilter@WW3D@@0HA`: 2 game file(s).

## Change and verification

No changes. The private int symbol is refused by add_data_match.py before initial-byte verification. Shared-header changes are prohibited, and a scalar cannot use the private-table no-row exemption.

The raw datum gate output is `build/rlink/identity-data-20261005/private-filter-probe.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A supported private scalar probe, correction of the initial value to 1 and passing source gates would settle application. A non-int access or a different clamping/initializer contract would refute the identity.

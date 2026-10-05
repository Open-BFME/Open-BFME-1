# Data identity at VA 0x012C7ED0

Corrected: _STL::_Filebuf_base::_M_page_size, unsigned int scalar.

## Retail facts and extent

The accepted row is `?_M_page_size@_Filebuf_base@_STL@@1IA` at VA 0x012C7ED0, RVA 0x00EC7ED0, with 4 bytes in `.data`, owned by `game/Libraries/Source/WWVegas/WWLib/stlport_filebuf_base_ctor.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012C7ED0-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially holds 0x1000. The constructor at RVA 0x00849F40 reads and writes this dword, calls GetSystemInfo when it is zero, takes dwPageSize at stack-structure offset +4, and assigns 0x1000 if still zero. File-buffer allocation and mmap readers use it arithmetically as a page size. The existing symbols.csv pin explicitly records that identity and the protected spelling.

Initial bytes: `00 10 00 00`.

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x008433C0` (`?_M_switch_to_output_mode@?$basic_filebuf@DV?$char_traits@D@_STL@@@_STL@@AAE_NXZ`, read), `0x00843590` (`?_M_switch_to_output_mode@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@AAE_NXZ`, read), `0x00843680` (`?_M_switch_to_input_mode@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@AAE_NXZ`, read), `0x00849F40` (`??0_Filebuf_base@_STL@@QAE@XZ`, read, write), `0x0084AC20` (`?_M_allocate_buffers@?$basic_filebuf@DV?$char_traits@D@_STL@@@_STL@@AAE_NXZ`, read), `0x0084AC40` (`?_M_allocate_buffers@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@AAE_NXZ`, read), `0x0084B210` (`?_M_doit@?$_Underflow@DV?$char_traits@D@_STL@@@_STL@@SAHPAV?$basic_filebuf@DV?$char_traits@D@_STL@@@2@@Z`, read).

## Receiver and argument contract

The constructor receives _Filebuf_base in ECX and has no stack arguments. Other filebuf methods receive their filebuf in ECX and read this module-wide scalar; it is not an object pointer.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012C7ED0-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?_M_page_size@_Filebuf_base@_STL@@0IA`: 1 game file(s).
- `?_M_page_size@_Filebuf_base@_STL@@1IA`: 2 game file(s).

## Change and verification

Defined the protected scalar once in stlport_filebuf_base_ctor.cpp with its retail initial value. Changed the mmap TU-local declaration from private to protected. The already protected input-mode declaration is unchanged.

The raw datum gate output is `build/rlink/identity-data-20261005/add-page-size.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A different GetSystemInfo field, pointer use, an initial value other than 0x1000, or a byte mismatch in any dependent filebuf body would refute this correction.

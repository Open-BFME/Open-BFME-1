# Data identity at VA 0x012B8B2C

Unresolved: DLListClass<Smudge>, one candidate 12-byte polymorphic list.

## Retail facts and extent

The candidate lies at VA 0x012B8B2C, RVA 0x00EB8B2C, in `.data`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B8B2C-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan.

The reference Smudge.cpp defines SmudgeSet::m_freeSmudgeList. Retail starts with the already pinned DLListClass<Smudge> vtable at VA 0x0111015C, followed by null head and tail. SmudgeSet::reset at RVA 0x005D3D50 and removeSmudgeFromSet at RVA 0x005D40A0 splice nodes through offsets +4 and +8; addSmudgeToSet at RVA 0x005D4320 and the SmudgeManager destructor at RVA 0x005D4390 also use its head. RVA 0x00C70430 writes the vtable dword, so g_Va012B8B2C names only that field and cannot describe the whole list.

The candidate extent is 12 bytes. Its initial bytes are `5c 01 11 01 00 00 00 00 00 00 00 00`. This is one object. No data row or DIR32 name lies strictly inside the candidate range. There is no PE base-relocation directory. No COFF initializer relocation count is accepted for this unresolved address. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x005D3D50` (`?reset@SmudgeSet@@QAEXXZ`, address immediate, read, write), `0x005D40A0` (`?removeSmudgeFromSet@SmudgeSet@@QAEXAAUSmudge@@@Z`, address immediate, read, write), `0x005D4320` (`?addSmudgeToSet@SmudgeSet@@QAEPAUSmudge@@XZ`, read), `0x005D4390` (`??1SmudgeManager@@UAE@XZ`, read), `0x00C70430` (`?Rva00C70430SetGlobal@@YAXXZ`, write).

## Receiver and argument contract

The list has no receiver contract of its own. Its users are ECX member calls; reset has no stack argument and addSmudgeToSet returns a node. The startup store has no receiver or arguments.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B8B2C-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?g_Va012B8B2C@@3IA`: 1 game file(s).
- `?m_freeSmudgeList@SmudgeSet@@0V?$DLListClass@USmudge@@@@A`: 1 game file(s).

## Change and verification

The private templated member is refused by add_data_match.py because it cannot be named for sizeof. The existing definition also relies on a constructor for its vptr. No source or ledger row at this address changed.

The raw datum gate output is `build/rlink/identity-data-20261005/private-smudge-probe.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A supported private-member size and initial-image verification for the real list would permit the definition; a different vtable, different head/tail offsets, or another datum inside the candidate extent would refute this identity.

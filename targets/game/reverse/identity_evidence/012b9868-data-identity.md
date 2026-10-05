# Data identity at VA 0x012B9868

Corrected: NAT::m_connectionPairs, int[7][7][8].

## Retail facts and extent

The accepted row is `?m_connectionPairs@NAT@@1PAY167HA` at VA 0x012B9868, RVA 0x00EB9868, with 1568 bytes in `.data`, owned by `game/GameEngine/Source/GameNetwork/nat.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B9868-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

The reference NAT.cpp initializer and NAT.h protected declaration match the retail table. RVA 0x006726B0 computes (pairIndex * 7 + round) * 8 + node and reads a dword. RVA 0x00672A60 uses the equivalent pairIndex * 0xE0 byte stride. Entries are signed node indices and -1 sentinels, not pointers. The extent ends exactly at m_timeBetweenRetries. All initial entries were compared by add_data_match.py.

Initial bytes: `01 00 00 00 00 00 00 00 ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff` (prefix; the complete initializer is in the raw retail log).

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00671F90` (`?processGlobalMessage@NAT@@QAEXHPBD@Z`, indexed read), `0x006726B0` (`?doThisConnectionRound@NAT@@IAEXXZ`, indexed read), `0x00672A60` (`?establishConnectionPaths@NAT@@QAEXXZ`, address immediate, indexed read).

## Receiver and argument contract

NAT member bodies receive this in ECX. doThisConnectionRound has no stack arguments; establishConnectionPaths has no stack arguments. The table is read, never used as a receiver.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B9868-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?m_connectionPairs@NAT@@0PAY167HA`: 1 game file(s).
- `?m_connectionPairs@NAT@@1PAY167HA`: 2 game file(s).

## Change and verification

Registered the existing definition in nat.cpp. The TU-local declaration in NAT_doThisConnectionRound_BFME.cpp now uses protected visibility, matching the reference and the existing owner.

The raw datum gate output is `build/rlink/identity-data-20261005/add-nat-pairs.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

Any retail stride other than 7 by 8 dwords, a write that changes the table layout, a different initializer, or another datum inside the range would refute this correction.

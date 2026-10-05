# Data identity at VA 0x012B9E88

Corrected: NAT::m_timeBetweenRetries, int scalar.

## Retail facts and extent

The accepted row is `?m_timeBetweenRetries@NAT@@1HA` at VA 0x012B9E88, RVA 0x00EB9E88, with 4 bytes in `.data`, owned by `game/GameEngine/Source/GameNetwork/nat.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B9E88-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially contains 500. ConnectionUpdate at RVA 0x006721D0 and doThisConnectionRound at RVA 0x006726B0 add the dword to timeGetTime results. The reference NAT.cpp defines the same retry interval as 500, and NAT.h places it in protected scope. The next named datum starts at VA 0x012B9E8C.

Initial bytes: `f4 01 00 00`.

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x006721D0` (`?connectionUpdate@NAT@@IAE?AW4NATConnectionState@@XZ`, read), `0x006726B0` (`?doThisConnectionRound@NAT@@IAEXXZ`, read).

## Receiver and argument contract

The readers use ECX as the NAT receiver and have no stack arguments. The scalar supplies a millisecond interval, not an address or receiver.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B9E88-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?m_timeBetweenRetries@NAT@@0HA`: 1 game file(s).
- `?m_timeBetweenRetries@NAT@@1HA`: 2 game file(s).

## Change and verification

Registered the existing definition in nat.cpp and corrected the private TU-local declaration in NAT_doThisConnectionRound_BFME.cpp to the reference protected spelling.

The raw datum gate output is `build/rlink/identity-data-20261005/add-nat-retry.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A non-dword access, pointer use, different shipped initial value, or another object inside the four-byte range would refute this correction.

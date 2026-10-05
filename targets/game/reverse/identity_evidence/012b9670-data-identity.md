# Data identity at VA 0x012B9670

Unresolved: const char* table with six reference entries and two retail extensions.

## Retail facts and extent

The candidate lies at VA 0x012B9670, RVA 0x00EB9670, in `.data`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B9670-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan.

The first six targets are b_locale, b_wins, b_losses, b_points, b_side and b_pre, in the same order as reference PeerThread.cpp. Retail appends b_rank1v1 and b_rank2v2. RVA 0x00643BC0 passes the base with count 6; RVA 0x0064EC80 passes it with count 8. The scalar spellings therefore do not describe the observed storage. A named DIR32 boundary, DualIndexedDispatchFirst, exists at VA 0x012B9688, inside a proposed eight-entry extent.

The candidate extent is 32 bytes. Its initial bytes are `1c 94 11 01 14 94 11 01 08 94 11 01 fc 93 11 01 f4 93 11 01 ec 93 11 01 e0 93 11 01 d4 93 11 01`. This is a candidate of eight four-byte pointer elements; the six-element boundary is disputed. Pointer-word targets are `0x0111941C`, `0x01119414`, `0x01119408`, `0x011193FC`, `0x011193F4`, `0x011193EC`, `0x011193E0`, `0x011193D4`. No data row overlaps this range. The interior DIR32 name described below prevents accepting it. There is no PE base-relocation directory. No COFF initializer relocation count is accepted for this unresolved address. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00643BC0` (`?d_00643bc0@@YAXXZ`, address immediate), `0x00643C10` (`?d_00643c10@@YAXXZ`, address immediate), `0x0064EC80` (`?bfmeGo1053E@BfmeE1053@@QAEXHH@Z`, address immediate), `0x0064ECC0` (`?joinRoomCallback@@YAXPAXHW4PEERJoinResult@@W4RoomType@@0@Z`, address immediate), `0x0064FB90` (`?Thread_Function@PeerThreadClass@@UAEXXZ`, address immediate).

## Receiver and argument contract

The six-key dispatcher has an ECX receiver and one stack PEER argument. It passes key and value bases to the same six-argument cdecl API twice, for room identifiers 1 and 2. The eight-key requester passes a callback, count 8 and the key base.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B9670-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?DualIndexedDispatchSixFirst@@3HA`: 1 game file(s).
- `?g_bfmeTab1053@@3HA`: 1 game file(s).
- `?s_keys@PeerThreadClass@@0PAPBDA`: 2 game file(s).

## Change and verification

No changes. Both PeerThread.cpp and PeerThread_ThreadFunction.cpp currently define only six keys. Defining an eight-element owner would cross the existing +24 named boundary; defining six alone does not settle the eight-key consumer.

The raw datum gate output is `build/rlink/identity-data-20261005/retail-details.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

Independent ownership evidence for the last two keys, followed by resolution of the interior named boundary and duplicate source definitions, would settle the extent. A separate six-element array plus a proven adjacent two-element array would refute the eight-element hypothesis.

# NetPacket parser donor retry

At revision `61d1641db70600cb157dd2ce7a7648ed5d06224a`, the assigned ledger entry still owns 940 bytes at RVA `0x0067EE40` as a generated assembly dump. Open BFME 2 donor `Code/GameEngine/Source/GameNetwork/NetPacket.cpp` at game.dat `0x00592607` is a changed 917-byte sequel body. Its source also cites a BFME 1 donor, so its shared spelling is not independent BFME 1 identity evidence.

The new hypothesis was that the donor's wider command ID, statement order, compiler flags or visible genuine callees would recover the parser's register allocation without clearing the message receiver before detach. The hypothesis would be refuted if those measured forms retained the existing mismatch.

## Native evidence

The complete target decodes through returns at `+0x396` and `+0x3AB`, followed by INT3 at `+0x3AC`. All direct conditional branches and jumps remain inside this extent. The checked inventory resolves all 31 distinct direct calls. The complete matched caller `NetCommandWrapperList::getReadyCommands` at `0x00676890` pushes length from node `+0x10`, then data from `+0x0C`, calls ILT `0x00048301`, and consumes the returned reference pointer in EAX. The parser reads the low word of its length parameter and uses cdecl cleanup. The matched caller and existing parser pin support the established identity independently of the donor.

The parser writes execution frame, command ID, player ID and command type at message offsets `+8`, `+0x10`, `+0x0C` and `+0x14`. The complete reference constructor at `0x00676240` writes message, next, previous, relay and timestamp at `+0`, `+4`, `+8`, `+0x0C` and `+0x10`, then returns with `ret 4`. The complete 27-byte detach body at `0x00673610` decrements the count at `+0x18` and checks both zero and negative counts before invoking virtual deleting destructor slot zero with flag one. Retail passes the actual message in ECX at target `+0x35B`; the preferred historical draft passes null there.

The native unwind map has one state. Cleanup `0x00C45DB0` passes the saved allocation to global operator delete. It protects the reference constructor, not an owning STL container. These checks do not certify the virtual destructor's complete downstream ownership implementation or every reader's proposed source type.

## Measurements and preserved work

Raw outputs and exact trial sources are retained under `build/donor-retry-20261009/`. `net_baseline.log` reproduces the historical 940-byte draft with 19 non-relocation differences starting at byte `+0x35C`. That draft clears the receiver and remains a diagnostic, not a valid recovery.

`net_donor.log` records 871 emitted bytes and 706 differences using the donor's `/O1` flags and 32-bit command ID. `net_donor_o2.log` records 946 bytes and 725 differences starting at `+0x1A` with the native optimization flags. The visible genuine constructor trial in `net_visible_ctor.log` is byte-identical to the latter caller; `net_ctor_verification.log` independently matches all 45 constructor bytes. The visible reader trial in `net_visible_readers_fixed.log` is also byte-identical to that caller. Reader helper emissions were not individually certified, so their visibility is a rejected compiler experiment, not an exact helper recovery. Each required mechanical search was capped at three trials and two unchanged trials; `net_eh_search.log` and `net_family_search.log` record no improvement.

`net_correct_baseline.cpp` restores the real detach receiver and reproduces the previously known semantic form: 944 emitted bytes, 186 differences starting at `+0x21`, and four excess bytes. Its raw probe is `net_correct_baseline.log`; its scoped strict byte gate fails in `gate_net.log`. The best semantic source is also preserved as immutable attempt-history evidence. The preferred historical bank remains untouched because it records the earlier diagnostic. No production source, ledger, pin, shared header or baseline changes were made.

The two new unchanged register experiments close the visibility hypothesis under the assigned limit. Reopening needs evidence for a different native local lifetime or a verified helper whose visibility changes this caller, rather than another tail permutation. Unknown indirect signatures and complete reader type evidence would still need review before any exact landing.

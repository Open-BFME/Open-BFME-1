# Verified rank-name table storage

Both existing address-derived spellings are retained. No original EA table identifier is established. Each row owns only its independently bounded ten-pointer extent in retail `.data`; no terminator is part of either row.

## Retail facts and routes

The retail callback at RVA `0x00566B10` has a ledger extent of 626 bytes. Its call at `+0xF9` reaches VA `0x00427093`, whose complete five-byte jump is `e9 58 62 07 00` and whose final target is VA `0x0049D2F0` (RVA `0x0009D2F0`). That matched producer sets ECX to zero, compares points against receiver fields beginning at `+0x18`, increments ECX at most nine times, and returns ECX + 1. The caller therefore receives an integer from 1 through 10. This bound is independent of spacing between data addresses. The points helper route is VA `0x00441510` (`e9 fb ae 05 00`) to VA `0x0049C410`; the numeric points value cannot enlarge the nine-step rank scan. Raw five-byte routes are in `build/rlink/tables-012b7dac-012b7dd4/producer-routes.log`, with complete producer instructions in `rank-disassembly.log` and `rank-points-disassembly.log` in the same folder.

The callback compares the selector argument with four full faction selector strings. Gondor and Rohan select the first table; Isengard and Mordor select the second. Each branch loads a four-byte pointer, checks it for NULL, then reads one-byte characters through the first NUL and passes that payload and length to the ASCII string setter. The two table operands carry HIGHLOW fixups at VA `0x00966C3E` and VA `0x00966C1E`. The former uses displacement `0x012B7DA8` and the latter `0x012B7DD0`, each with EAX scaled by four. With rank 1 through 10, these are exactly element indices 0 through 9 of the two assigned tables. See `build/rlink/tables-012b7dac-012b7dd4/consumer-exact-disassembly.log`.

## VA 0x012B7DAC

The supported type is writable array storage containing ten pointers to NUL-terminated const narrow characters (`const char *[10]`), spanning `[0x012B7DAC, 0x012B7DD4)`, or 40 bytes. Every pointer has a retail HIGHLOW fixup. In index order the complete literals are Peasant, Page, Squire, Knight, RoyalGuard, CaptainOfTheGuard, HighLord, Prince, King, and Wizard. None of these ten entries is NULL. The next dword begins the independently accessed second table and is not a terminator.

## VA 0x012B7DD4

The supported type is writable array storage containing ten pointers to NUL-terminated const narrow characters (`const char *[10]`), spanning `[0x012B7DD4, 0x012B7DFC)`, or 40 bytes. Every pointer has a retail HIGHLOW fixup. In index order the complete literals are Scum, Vermin, Beast, Goblin, Orc, MountainTroll, Berserker, DarkWizard, RingWraith, and DarkLord. None of these ten entries is NULL. Retail has a zero dword at `0x012B7DFC`; no observed producer or consumer accesses it as a table element or sentinel, so it is excluded from the supported extent.

## Pointees, ownership, and all users

`build/rlink/tables-012b7dac-012b7dd4/retail-tables.log` records all twenty initialized pointer dwords, every complete NUL-terminated literal as hexadecimal bytes, each pointee section, every HIGHLOW site, and the neighboring dwords. None of the twenty literal payloads contains a HIGHLOW fixup. The same probe streams data rows, DIR32 names, pins (both VA and RVA interpretations), and function extents; it finds no owner or competing identity within either table extent. Its full retail HIGHLOW target scan finds only the two callback operands, including the negative element displacement. `producer-routes.log` additionally searches embedded table-base and displaced-base dwords throughout retail `.text`.

The ordinary and numeric source survey is in `table-spellings.log` and `numeric-neighbor-spellings.log`. Both table identifiers are declared in one game file each, the assigned source. No competing recorded spelling names either table. `all-coff-users-before.log` surveys existing complete objects for implicit references and finds only that source, with one DIR32 load for each spelling. `table-literal-spellings.log` finds no literal counterpart in game sources or the Zero Hour reference. The reference is not used to assert an EA identity.

## Storage and preservation

The ordinary declarations retain their existing identifiers and gain the proved bound of ten. Genuine initialized arrays are appended after the existing method under the exact existing decorated names using `extern "C" __identifier`. All existing source line positions and explanatory comments are preserved. Literal initializers provide actual compiler relocations to pooled character payloads; there are no raw address-valued stand-ins, aliases, artificial users, or data rows at compiler constants. The two table identities are added to DIR32. Twenty additive compiler-literal pins in symbols.csv bind the complete emitted payloads, including their NUL terminators, to the verified retail pointees. Compiler constants receive no data rows. The unmodified staged DIR32 record guard passes with these bindings.

The original current-head source is preserved in `head-source.log`, the original working source in `Rva00566B10.original.cpp`, and the complete original same-path object in `Rva00566B10.original.obj`, all under `build/rlink/tables-012b7dac-012b7dd4/`. `complete-coff-preservation-resolved.log` and `coff-preservation.json` compare every complete CODE section, relocation kind and semantic target (external identity or local section and offset), every original readonly payload, and the complete EH graph. Compiler-generated numeric local labels are decoded by target section and offset. SafeSEH symbol indices are decoded to `__ehhandler$?method@Rva00566B10@@QAEXPAX@Z` at offset 48 in the unchanged 58-byte `.text$x` section. No original CODE or readonly/EH bytes change.

## Receiver and argument contract

The callback receives its original receiver in ECX, constructs per-user battle honors from the preferences member at receiver +4, and takes one selector pointer on the stack (`ret 4`). The rank producer receives the battle-honors receiver in ECX and a by-value one-word ASCII side string on the stack (`ret 4`). It reads nine integer thresholds from receiver +0x18 through +0x38 and returns rank in EAX. Table contents are used as ASCII suffixes of `TOOLTIP:` for the existing game-text call; no new class relationship is inferred.

## Refutation

Either correction is refuted by a retail route returning rank below 1 or above 10 before that table load, any additional actual user outside the assigned source, any table write or scan proving a different element type or count, a mismatching complete pointee payload or HIGHLOW site, or any recorded datum, DIR32 identity or pin inside the proposed extent. A proven consumer of `0x012B7DFC` as the second table's sentinel would require revisiting its extent; it is not assumed from adjacency. Any change in a complete CODE section, relocation target, original readonly payload, or decoded EH/SafeSEH graph also rejects the source candidate.

## Gate results

The unmodified CLI pass tests both exit 0 and delete their independent DIR32 baseline lines (`pass-test-012b7dac.log` and `pass-test-012b7dd4.log` under `build/rlink/tables-012b7dac-012b7dd4/`). The second pass-test gates the sole actual user with both lines deleted: Functions OK 1/1, both data rows verified, and zero baselined body-guard findings. `final-check-csv.log`, `final-pin-consistency.log`, and `final-declared-unmatched.log` all exit 0. `review-diff.log` has no whitespace errors. `final-complete-coff-preservation.log` repeats complete code, readonly, EH and decoded SafeSEH preservation against the final same-path object.

The final literal pins and both table initializers were independently reproduced in `coordinator-good-initializer.log` and `coordinator-evil-initializer.log` in the same raw folder. `coordinator-pinned-record-guard.log` passes the original staged record guard. Both original CLI tests were repeated unchanged with the final pins, and `coordinator-full-coff-preservation.log` verifies the actual final object, including its decoded SafeSEH handler.

`initial-link.log` and `final-link.log` both report LINKED 0 bytes and exit 1. The two assigned table identities no longer appear in the unresolved list after this correction. The remaining unrelated unresolved string-helper identities and existing COMDAT selection differences are outside the assigned scope; the independent repair pass tests pass. `all-coff-users-after.log` and `decimal-and-full-pointer-spellings.log` complete the source and object user survey.

# Current-level tooltip arrays at 0x012B7FF0 and 0x012B8018

## Decision

The existing decorated identities are retained. The evil-side reference at VA 0x012B8018 is an independently bounded 11-element array of pointers to NUL-terminated narrow strings, covering [0x012B8018, 0x012B8044). Its first element is unused by this consumer. The good-side reference at VA 0x012B7FF0 independently requires indices 1 through 10, and its complete base-relative extent is [0x012B7FF0, 0x012B801C). These supported extents overlap at the Wizard pointer dword at 0x012B8018. A 40-byte definition at 0x012B7FF0 would omit the supported index 10. The good-side repair remains unresolved because the ordinary data ledger requires disjoint ownership; it must not be shortened merely to fit adjacency.

## Retail facts and contract

The hash-bound target is retail-1.03-unpacked, SHA-256 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. Both bases are in .data. The PE base-relocation directory is stripped, but the final section retains the linker's original relocation blocks, which tools/retail_relocs.py reads. Every nonzero pointer dword in both supported extents has its HIGHLOW entry, and both callback address fields have theirs. The unused zero at the good base has none. Every dword and complete NUL-terminated pointee is retained in build/rlink/current-level-1791448115/initial-probe.log. There is no sentinel claim.

The complete callback is RVA 0x0057A200, size 498. Its receiver supplies the honors object at receiver+0x3C4. It retrieves slot 0 and the player's template, copies the side string at template+0x08, and passes the one-word AsciiString by value to the rank producer. The E9 thunk at RVA 0x00027093 has bytes e958620700 and jumps directly to RVA 0x0009D2F0. The entire 117-byte producer starts its counter at 0, compares signed points against nine thresholds starting at receiver+0x18, increments until counter==9, and returns counter+1 with ret 4. This proves the independent range 1..10 for both branches, without relying on neighbouring data.

The points call routes through RVA 0x00041510 (e9fbae0500) to the complete 128-byte body at RVA 0x0009C410. That body appends Points to the side and returns getInt with default 0. Its getInt thunk RVA 0x000443B9 leads to RVA 0x000A9490. The complete 222-byte getInt returns either the default or the parsed signed integer without a side-dependent rank clamp. At callback VA 0x0097A298, template+0x118 selects the evil branch. VA 0x0097A2A5 loads [eax*4+0x012B8018]; VA 0x0097A2AF loads [eax*4+0x012B7FF0]. Neither branch adjusts or clamps eax. The chosen pointer is passed to the AsciiString assignment path through RVA 0x00028BB9, then concatenated after TOOLTIP:. The callback's void-pointer argument is not read.

| Index | Good base 0x012B7FF0 | Evil base 0x012B8018 |
| --- | --- | --- |
| 0 | 0x00000000 (unused) | 0x0107FE34 Wizard |
| 1 | 0x0107FE98 Peasant | 0x0107FE2C Scum |
| 2 | 0x0107FE90 Page | 0x0107FE24 Vermin |
| 3 | 0x0107FE88 Squire | 0x0107FE1C Beast |
| 4 | 0x0107FE80 Knight | 0x0107FE14 Goblin |
| 5 | 0x0107FE70 RoyalGuard | 0x0107FE10 Orc |
| 6 | 0x0107FE58 CaptainOfTheGuard | 0x0107FE00 MountainTroll |
| 7 | 0x0107FE4C HighLord | 0x0107FDF4 Berserker |
| 8 | 0x0107FE44 Prince | 0x0107FDE4 DarkWizard |
| 9 | 0x0107FE3C King | 0x0107FDD4 RingWraith |
| 10 | 0x0107FE34 Wizard | 0x0107FDC8 DarkLord |

The Zero Hour SkirmishBattleHonors header and implementation under inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine contain the preferences contract but neither BFME getRank nor these current-level tables. Their contents are retained in reference-honors-read.log. No EA table-name identity is asserted.

## Ownership and users

Each existing spelling is declared by one game source: game/GameEngine/Source/GameClient/GUI/SkirmishScreenTooltipCurrentLevel.cpp. The case-insensitive ordinary and numeric source search, complete retail pointer-span scan, and scan of all 688 available build/match COFF objects find only that consumer for the two identities. No existing data row, DIR32 name, pin, or function owner overlaps either supported extent before this repair. Raw evidence is in array-all-spellings.log and complete-survey.log. This is a survey of the available object set, not a claim that every repository source was compiled. The full source search complements it.

The evil definition and a bounded ordinary redeclaration are appended at EOF using extern-C __identifier under its exact existing decorated identity. The bounded redeclaration completes the unchanged earlier unsized declaration for the ordinary sizeof probe. Ordinary declarations, descriptive and EA declarations, explanatory comments, and all existing source line positions remain intact. Compiler literals remain constants: they receive no data rows and no new DIR32 records. All eleven emitted literal payloads, including their NUL bytes, match the pointed-to retail strings; the needed literal RVA pins already exist and are retained unchanged.

## Preservation and verification

The complete original current-head source and same-path object are saved as original-source.cpp and original.obj in build/rlink/current-level-1791448115/. The original object SHA-256 is 2cd8c2e588c3bf5ee1f615609a4a16753912d74e7f3a8870a18bfb55a542ea60. final-preservation.log checks all 12 original CODE sections, relocation kinds and addends, original readonly payloads, the recursive code/EH graph, and the actual handler decoded from each SafeSEH entry. Compiler-generated local label numbers and COFF symbol indices are compared by their referenced section and offset. All those bytes and resolved internal targets are preserved.

Raw callback and producer evidence: retail-tooltip.log, rank-producer-retail.log, complete-points-body.log, complete-int-getter.log, full-body-callee-routes.log and complete-survey.log under build/rlink/current-level-1791448115/. coordinator-retail-tables.log independently re-derives the complete callback and rank body, every supported pointer and full NUL pointee, all retained HIGHLOW entries and the whole-image address-field census. The ordinary evil admission passed in evil-add-data-sized.log, proving sizeof 44 and all eleven relocation targets. Its official CLI pass test passed in evil-official-pass-test.log and removed only its own exemption. The complete 44-byte good candidate was rejected for overlap in good-add-data.log; good-official-pass-test.log failed the DIR32 ownership check and restored its own exemption. Only the good candidate source edits were restored, preserving the evil repair. final-all-user-build.log reports Functions OK 1/1 and Data rows OK. final-check-csv.log, final-pin-consistency.log and final-declared-unmatched.log all pass. record-staged-guard.log passes against the untouched index; record-working-guard.log separately runs the unchanged official problems function against the actual working-copy addition and reports no problems. No staging occurred. before-link.log and after-link.log both report LINKED 0 to 0 bytes; the evil unresolved symbol is removed, while the good datum, BFMEEmptyUnicodeString and existing COMDAT/selection debt still prevent full linking.

## Refuting observations

An additional retail producer or consumer that indexes below 1 or above 10, a different final E9 target, or a side-dependent clamp contradicts the stated bound and requires re-evaluation. Any unequal pointer dword, emitted pointee byte including NUL, relocation kind or resolved target, recursive EH payload, or decoded SafeSEH handler refutes the candidate. An existing overlapping owner or another source/implicit COFF consumer outside the assigned source blocks exemption removal. A successful ordinary disjoint admission of the independently supported good extent would settle its current ledger blocker; shortening it without proving rank 10 impossible would not.

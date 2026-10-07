# Ten linking and verifier tasks — 2026-10-07

Model: gpt-6.1-sol. Starting pull: 16be98e9da -> caacbe3444; master remains active.

| Task | Result | Verification |
| --- | --- | --- |
| 1. Object dead-state COMDAT conflicts | Six files link; +1,449 B | Eight matched rows pass; remove unused external helpers and keep their exact bit tests |
| 2. PreferenceMap lookup binding | Eight of nine callers link; +1,143 B | Thirteen matched rows pass; use recorded ILT 0000AEAC -> 00080600. Starting-supplies caller restored and recorded blocked because the wrapper changes EH state and registers |
| 3. Object template-getter COMDAT conflicts | Five files link; +1,157 B | Five matched rows pass; keep differing inline load/override behavior in static TU-local helpers |
| 4. CommTCPResolve diagnostic | Remove static-data exception | Full literal at VA012C4AB0; repair_queue pass-test and both source rows pass |
| 5. CommSRPResolve diagnostic | Remove static-data exception | Full literal at VA012C4C68; repair_queue pass-test and all five source rows pass |
| 6. CommSRPListen diagnostic | Remove static-data exception | Actual newline at VA012C4CF4; repair_queue pass-test; existing independent jump-table/tail debt remains |
| 7. Nested entry sink binding | Matched sink identity at 004135C0 | 167-byte caller passes; preserve byte-extension instruction shape with ABI-compatible member call view |
| 8. Audio handle member destructor | Matched Rva006910F0Handle destructor | 105-byte owner destructor passes; ILT000298E8 -> 00691130 |
| 9. FESL ECNL message getter | Matched BfmeThingRF field getter | 102-byte caller passes; matched callee source establishes two word arguments and word result |
| 10. Script player-mask getter | Recorded retail ILT0004B290 reaches the proven two-argument selector | 137-byte caller passes and links; preserve const AsciiString reference, optional Boolean pointer and 16-bit result while avoiding a competing selected definition |

The per-file linking checks now report 23 files newly linking, +4,260 B. Scoped builds and normal commit hooks verify 37 matched rows across 25 changed source files. Three static-data baseline exceptions are removed after their independent pass tests.

All changes use existing ledger owners and pins. No shared header, new pin, assembly dump, or function-ledger change.

The additional Apt string-call binding attempt failed register/order byte matching and was fully restored. The ShareBuffer constructor candidate was inspected but left untouched. Unused claims were released.

Original user changes to .gitignore were saved in /tmp/open-bfme-user-gitignore-20261007.patch for restoration after the final pull. The existing pyproject.toml and uv.lock are unrelated and unstaged.

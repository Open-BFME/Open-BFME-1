# Retail literal extern correction, sixth batch

Corrected 15 addresses in 14 source files. Eight indexed lookup addresses remain unchanged because their retail accesses do not meet the literal-only contract. Two verified literals have no source declaration or use of the requested spelling. No function identity, extent, instruction sequence, shared header, generated source, pin, DIR32 ledger row, or data ledger row was changed.

The hash-bound baseline is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`. All requested VAs are in `.rdata`. `build/rlink/batch6-1791172570/retail-probe-v2.log` records the bytes at and before each VA, exact escaped NUL-terminated contents when present, all DIR32 spellings, source occurrences, matched-row disassembly, and every relevant five-byte ILT entry with its final target. The initial probe stopped on a table with no NUL in its 320-byte window; that raw output remains in `build/rlink/batch6-1791172570/retail-probe.log`.

The executable has no base relocation entries. `build/rlink/batch6-1791172570/interior-scan.log` therefore scans every file-backed PE section for the little-endian address of each candidate byte, including interior bytes and the terminator. None of the corrected literals has an interior address occurrence or an interior DIR32 spelling. The scan is a conservative byte search; positive occurrences are separately interpreted through the matched source disassembly in the retail probe.

The corrected call operands are immediate addresses pushed as string keys, formats, messages, or source filenames. The argument and receiver declarations stay unchanged. The flag-name string at `0x0112A410` is stored as an immediate address in a `const char *` local at RVA `0x007ECAF0`, then walked until NUL; retail neither embeds an indexed DIR32 byte read nor writes to the string. The exact literal replaces that pointer initializer. Its explanatory comment now describes the bit order without the old incorrect character count.

MSVC's unoptimized flag-name literal is the local symbol `$SG501`, rather than a `??_C@` pooled literal. The standard string checker reports zero pooled literals for that source. `build/rlink/batch6-1791172570/verify-replacements-final.log` independently locates each changed DIR32 slot in its compiled function, reads the referenced COFF symbol plus addend, and compares every byte including NUL with the bytes read from the requested retail VA. All 19 changed references pass, including `$SG501`. The scoped builds verify all 58 matched rows across the changed sources.

The filename at `0x0112C24C` already has a verified definition and data row in `game/GameEngine/Source/GameNetwork/Y2FeslUtilFileName.cpp`. That definition and row remain; only its three external callers now use the literal. Neither unused requested spelling at `0x0112BC58` or `0x0112BC80` was added, removed, or renamed. No datum was newly defined.

An interior reference, write into a corrected string, a DIR32 memory-value access instead of the recorded immediate address, a mismatching compiled literal byte, or a changed verified instruction would refute a correction. A reference to either unused spelling would require reopening its source-use assessment. The indexed lookup rows would require an independent data-definition lane, with verified extents and overlap checks, to resolve their missing definitions.

## Address decisions

File IDs refer to the single per-file verification table below. For unchanged lookup data, the retail probe retains all 320 measured bytes and the access instructions rather than mislabeling a prefix as a literal.

| VA | Exact C literal or data classification | Changed files | Decision |
|---|---|---|---|
| `0x011293A0` | Lookup data; exact bytes in retail probe. | None | Unchanged. Indexed byte lookup table; retail directly reads [index + VA]. A following NUL does not establish string use. |
| `0x011294A8` | Lookup data; exact bytes in retail probe. | None | Unchanged. Indexed byte lookup table; retail directly reads [index + VA]. A following NUL does not establish string use. |
| `0x01129908` | `"email"` | F01 | Replaced extern and uses with the verified literal. |
| `0x01129AB0` | `"Error entering critical section\n"` | F02 | Replaced extern and uses with the verified literal. |
| `0x01129AD4` | `"Error leaving critical section\n"` | F03 | Replaced extern and uses with the verified literal. |
| `0x01129E10` | Lookup data; exact bytes in retail probe. | None | Unchanged. Indexed byte lookup table, contiguous with the table at the next requested address. No NUL occurs within the first 320 bytes. |
| `0x01129F10` | Lookup data; exact bytes in retail probe. | None | Unchanged. Indexed byte lookup table; retail directly reads [index + VA]. |
| `0x0112A010` | Lookup data; exact bytes in retail probe. | None | Unchanged. Binary unsigned-byte hex lookup table. Its zero first byte is not an empty-string contract. |
| `0x0112A110` | Lookup data; exact bytes in retail probe. | None | Unchanged. Binary unsigned-byte hex lookup table used in two files. Its zero first byte is not an empty-string contract. |
| `0x0112A410` | `"@ABCDEFGHIJKLMNOPQRSTUVWXYZ0123"` | F14 | Replaced extern and uses with the verified literal. |
| `0x0112A530` | Lookup data; exact bytes in retail probe. | None | Unchanged. Integer month-length table accessed through a scaled index; its first bytes are 1f 00 00 00. |
| `0x0112AC04` | `"targetIds.%d"` | F10 | Replaced extern and uses with the verified literal. |
| `0x0112AC20` | `"chatLog.%d.chat"` | F10 | Replaced extern and uses with the verified literal. |
| `0x0112AC30` | `"chatLog.%d.userId"` | F10 | Replaced extern and uses with the verified literal. |
| `0x0112ADB0` | `"numberOfReporters"` | F01 | Replaced extern and uses with the verified literal. |
| `0x0112B4B8` | `"NUM-REGIONS"` | F06 | Replaced extern and uses with the verified literal. |
| `0x0112B4D0` | `"NUM-GAMES"` | F13 | Replaced extern and uses with the verified literal. |
| `0x0112B52C` | `"LID"` | F08, F09, F13 | Replaced extern and uses with the verified literal. |
| `0x0112B558` | `"UGID"` | F07 | Replaced extern and uses with the verified literal. |
| `0x0112B560` | `"SECRET"` | F07 | Replaced extern and uses with the verified literal. |
| `0x0112B918` | Lookup data; exact bytes in retail probe. | None | Unchanged. Sixteen indexed hex digits have no NUL at offset 16; the first NUL-terminated byte sequence also contains decodedSize. Direct indexed byte reads establish the lookup-array contract. |
| `0x0112BC58` | `"lookupIndex != NAMING_TOO_MANY_LOOKUPS"` | None | No source edit. Verified literal, but the requested spelling has no declaring game file or source use. |
| `0x0112BC80` | `"\\views\\feslbuild_main\\jabba\\fesl\\source\\naming.cpp"` | None | No source edit. Verified filename literal, but the requested spelling has no declaring game file or source use. |
| `0x0112C00C` | `"PROT"` | F05 | Replaced extern and uses with the verified literal. |
| `0x0112C24C` | `"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp"` | F04, F11, F12 | Replaced extern and uses with the verified literal. |

## Spellings and declaring files

These are all DIR32 spellings at each requested VA. The count includes a definition when one exists; it is the number of game files declaring that spelling, not a popularity argument for identity.

| VA | DIR32 spelling | Declaring game files |
|---|---|---|
| `0x011293A0` | `?g_Rva011293A0HexFirst@@3PADA` | 1 |
| `0x011294A8` | `?g_Rva011294A8HexSecond@@3PADA` | 1 |
| `0x01129908` | `?TheBfmeSetupSecondText007E9520@@3QBDB` | 1 |
| `0x01129AB0` | `?g_bfmeMsg1037@@3PADA` | 1 |
| `0x01129AD4` | `?g_bfmeMsg1038@@3PADA` | 1 |
| `0x01129E10` | `?g_Rva01129E10HexFirst@@3PADA` | 1 |
| `0x01129F10` | `?g_Rva01129F10HexSecond@@3PADA` | 1 |
| `0x0112A010` | `_g_Rva0112A010HexHigh` | 1 |
| `0x0112A110` | `_g_Rva0112A110Hex` | 2 |
| `0x0112A410` | `?g_Rva0112A410FlagLetters@@3PADA` | 1 |
| `0x0112A530` | `_g_Rva0112A530MonthDays` | 1 |
| `0x0112AC04` | `?g_Rva012DAC04@@3QBDB` | 1 |
| `0x0112AC20` | `?g_Rva012DAC20@@3QBDB` | 1 |
| `0x0112AC30` | `?g_Rva012DAC30@@3QBDB` | 1 |
| `0x0112ADB0` | `?TheBfmeSetupSecondText007F26A0@@3QBDB` | 1 |
| `0x0112B4B8` | `?g_bfmeNumRegions803B60@@3PADA` | 1 |
| `0x0112B4D0` | `?g_bfmeNumGamesKey@@3PADA` | 1 |
| `0x0112B52C` | `?g_bfmeLidKey@@3PADA` | 3 |
| `0x0112B558` | `?g_feslUserIdKey@@3PADA` | 1 |
| `0x0112B560` | `?g_feslSecretKey@@3PADA` | 1 |
| `0x0112B918` | `?g_Rva0112B918HexDigits@@3QBDB` | 1 |
| `0x0112BC58` | `?g_bfmeNameABD@@3QBDB` | 0 |
| `0x0112BC80` | `?g_bfmeKindABD@@3QBDB` | 0 |
| `0x0112C00C` | `?g_bfmeKey803A00A@@3PADA` | 1 |
| `0x0112C24C` | `?g_bfmeFileUVB@@3QBDB` | 4 |

## Per-file LINKED measurements and scoped gates

Before is the current-object result measured before edits, not the historical census figure. After is the current-object result after edits. `link_check.py` exits 1 when any source has remaining blockers, while reporting each source independently. The two utility joins link after the correction; all other sources retain unrelated unresolved names. Raw before logs are `build/rlink/batch6-1791172570/link-before.log` and `build/rlink/batch6-1791172570/link-before-flags.log`. Raw after logs are `build/rlink/batch6-1791172570/link-after.log` and the final comment-only refresh `build/rlink/batch6-1791172570/link-after-flags-final.log`.

| File ID | Changed source | LINKED before | LINKED after | Functions OK | Build log |
|---|---|---:|---:|---|---|
| F01 | `game/GameEngine/Source/Common/Bfme5SetupPairs.cpp` | 0 | 0 | 8/8 | `build/rlink/batch6-1791172570/build-v3-01-Bfme5SetupPairs.log` |
| F02 | `game/GameEngine/Source/Common/BfmeConv1037.cpp` | 0 | 0 | 4/4 | `build/rlink/batch6-1791172570/build-v3-02-BfmeConv1037.log` |
| F03 | `game/GameEngine/Source/Common/BfmeConv1038.cpp` | 0 | 0 | 6/6 | `build/rlink/batch6-1791172570/build-v3-03-BfmeConv1038.log` |
| F04 | `game/GameEngine/Source/Common/BfmeConv1344.cpp` | 0 | 0 | 2/2 | `build/rlink/batch6-1791172570/build-v3-04-BfmeConv1344.log` |
| F05 | `game/GameEngine/Source/Common/BfmeConv803A00.cpp` | 0 | 0 | 1/1 | `build/rlink/batch6-1791172570/build-v3-05-BfmeConv803A00.log` |
| F06 | `game/GameEngine/Source/Common/BfmeConv803B60.cpp` | 0 | 0 | 1/1 | `build/rlink/batch6-1791172570/build-v3-06-BfmeConv803B60.log` |
| F07 | `game/GameEngine/Source/GameNetwork/FeslEchoNotifier.cpp` | 0 | 0 | 1/1 | `build/rlink/batch6-1791172570/build-v3-07-FeslEchoNotifier.log` |
| F08 | `game/GameEngine/Source/GameNetwork/Rva0080A110Route.cpp` | 0 | 0 | 2/2 | `build/rlink/batch6-1791172570/build-v3-08-Rva0080A110Route.log` |
| F09 | `game/GameEngine/Source/GameNetwork/Rva0080AB50Handle.cpp` | 0 | 0 | 1/1 | `build/rlink/batch6-1791172570/build-v3-09-Rva0080AB50Handle.log` |
| F10 | `game/GameEngine/Source/GameNetwork/V2FeslFeedbackRequest.cpp` | 0 | 0 | 3/3 | `build/rlink/batch6-1791172570/build-v3-10-V2FeslFeedbackRequest.log` |
| F11 | `game/GameEngine/Source/GameNetwork/Y2FeslUtilJoin.cpp` | 0 | 261 | 1/1 | `build/rlink/batch6-1791172570/build-v3-11-Y2FeslUtilJoin.log` |
| F12 | `game/GameEngine/Source/GameNetwork/Y2FeslUtilJoinI64.cpp` | 0 | 316 | 2/2 | `build/rlink/batch6-1791172570/build-v3-12-Y2FeslUtilJoinI64.log` |
| F13 | `game/GameEngine/Source/GameNetwork/Y4FeslFavGameList.cpp` | 0 | 0 | 1/1 | `build/rlink/batch6-1791172570/build-v3-13-Y4FeslFavGameList.log` |
| F14 | `game/Libraries/Source/DirtySock/Y2Rva007EBAE0Module.cpp` | 0 | 0 | 25/25 | `build/rlink/batch6-1791172570/build-final-14-Y2Rva007EBAE0Module.log` |

## Remaining gates and mechanical repairs

CSV validation passes in `build/rlink/batch6-1791172570/check_csv-final.log`. Pin consistency passes in `build/rlink/batch6-1791172570/pin_consistency.log`. `find_declared_unmatched.py --fail` passes for every changed source in `build/rlink/batch6-1791172570/find_declared_unmatched.log`. `git diff --check` passes in `build/rlink/batch6-1791172570/diff-check.log`. Raw command receipts are in `build/rlink/batch6-1791172570/receipts.jsonl`.

The first CMD invocations did not find `build.cmd`; explicit `.\build.cmd` then reached a Python launcher that reported no installed Python. These launches ran no build. Their raw logs are retained under `build-*.log` and `build-v2-*.log`. Invoking the repository's `./build.sh` through Git Bash repaired the launch path and produced the successful logs above. No semantic gate refused any correction. No files were staged or committed; no network Git operation, claim command, or subagent was used.

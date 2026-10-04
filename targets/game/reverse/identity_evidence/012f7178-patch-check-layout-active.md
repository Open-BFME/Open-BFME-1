# One patch-check flag at VA 0x012F7178

The one-byte mutable datum at VA `0x012F7178` (RVA `0x00EF7178`) has one external definition and one address-derived spelling, `g_rva012F7178PatchCheckLayoutActive`. No EA variable name is established. The spelling describes the observed patch-check layout lifetime and retains the address. It follows `g_rva01142308`, `g_rva01110180Names` and `g_Rva0130A50CTxn` in `data_rows.csv`, and the address-qualified flag spellings in `dir32_addresses.csv`. The naming precedents are printed verbatim in `build/rlink/patch-check-012f7178-1791148216/retail-datum.log`.

## Retail storage and accesses

`reloc_ledger.Image` maps the byte to the zero-filled virtual tail of retail `.data`. Its initial value is `00`. The PE mapping, nearby bytes, and overlap checks are in `build/rlink/patch-check-012f7178-1791148216/retail-datum.log`; the reproducible probe is `probe_datum.py` in that folder. No existing data row covers `[0x012F7178, 0x012F7179)`. There is no different DIR32 address inside that interval. The three competing external DIR32 spellings are all at its start and are retained unchanged. `configBuffer` starts at `0x012F7174`, and the separate DNS flag starts at `0x012F717A`.

A scan of the file-backed bytes of every retail section finds thirteen direct absolute operands for this address, all in `.text`. Their containing instructions read or write one byte. Zero and one stores establish mutable state rather than a compiler constant. This census concerns direct absolute operands, not arbitrary computed pointers.

| Body RVA | Byte reads at instruction offsets | Byte writes at instruction offsets | Observation |
|---|---|---|---|
| `0x0062EA60` | `+0x0E` | `+0x2F`, zero | Online startup conditionally cleans up and clears the flag. |
| `0x0062EE00` | `+0x76` | `+0x92`, zero | MOTD completion decrements the pending-check counter, then cleans up and clears the flag when it reaches zero. |
| `0x0062EEE0` | `+0x134`, `+0x183` | `+0x14F`, `+0x19E`, zero | Both Config.txt completion paths use the same counter, cleanup and flag. |
| `0x0062F130` | `+0x1D4` | `+0x1EF`, zero | A matching cached Content-Length completes a check and performs the same cleanup. |
| `0x0062F760` | `+0x18` | `+0x31`, zero | Patch cancellation clears checking state and the pending-check counter, then cleans up and clears the flag. |
| `0x006304A0` | None | `+0x48`, one | The patch-check start-shaped body sets the flag and references `GUI:CheckingForPatches`. |

Each full retail disassembly is saved as `build/rlink/patch-check-012f7178-1791148216/dis-<eight-digit-rva>.log`. The probe also reads the exact bytes of `GUI:CheckingForPatches`, `servserv.generals.ea.com` and `%sLoTRB4MEOnline\Config.txt` at their retail addresses. These anchor the operation, not an original variable spelling.

## Receiver and argument contract

The datum is a global scalar. Its absolute byte operands require no receiver and pass neither its address nor value to cleanup. The conditional call target is VA `0x00442A50`, whose five bytes `e9 3b 2a 48 00` jump to VA `0x008C5490`. The final nine-byte wrapper pushes a null argument, calls VA `0x00449AD0`, pops that stack argument and returns. That second five-byte thunk is `e9 6b 8c 4d 00` and ends at VA `0x00922740`. `symbols.csv` already pins `ReleaseWindowLayout(WindowLayout *)` to RVA `0x00049AD0`. The route bytes and existing pin are in `retail-datum.log`, and the wrapper is in `dis-004c5490.log`.

The HTTP bodies remain free cdecl callbacks with request, result, buffer, 64-bit buffer length and callback parameter arguments. The startup and cancellation bodies retain their existing free-function contracts. No function identity, signature, instruction or extent is changed. The separate start-shaped body at RVA `0x006304A0` consumes a byte stack argument, which this datum repair does not rename or retype.

## Competing spellings and the definition

The pre-edit declaration scan in `retail-datum.log` counts one game file declaring `g_rva012F7178ReleaseLayout`, one declaring `onlineCancelFlag`, two declaring private `s_rva012F7178`, and three declaring `reOpenPlayerInfoFlag`. Only the cancellation file's external `reOpenPlayerInfoFlag` targets this byte. The other two declarations belong to the separate overlay question and are untouched.

Retail `CheckReOpenPlayerInfo` at RVA `0x00628270` tests and clears VA `0x012F70B0`, as recorded in `dis-00628270.log`. Zero Hour defines `reOpenPlayerInfoFlag` for that reopen operation and defines `GameWindow *onlineCancelWindow` for patch-check notification cleanup. `zero-hour-names.log` contains the reference occurrences. Neither proves an EA name for BFME's byte. The earlier investigation is preserved verbatim as `prior-findings.md` in the raw evidence folder.

`MainMenuHTTPBufferRva0062EE00.cpp` owns `volatile unsigned char g_rva012F7178PatchCheckLayoutActive = 0`. The other four scoped files declare that exact type and spelling externally. A common volatile byte type preserves the cancellation file's volatile accesses and gives every translation unit the same C++ data symbol, `?g_rva012F7178PatchCheckLayoutActive@@3EC`. The scoped builds prove all five function rows still match retail exactly (`build-five.log` and `build-final.log`, Functions OK 5/5). `add_data_match.py` independently proves the one-byte definition and zero initializer (`add-data.log`), and the final build verifies the added data row. The object definition occupies a one-byte `.bss` section; the data row uses retail's `.data` mapping. Existing DIR32 spellings remain additive evidence; no symbol pin is deleted or rewritten.

## Refutation and verification

An independently authenticated BFME declaration naming this precise byte would settle its original spelling. A different thunk endpoint would refute the cleanup interpretation. A retail mapping with nonzero initial data, an overlapping datum, a wider access or a changed byte in any scoped function would refute the storage or code-preservation claims. `definition-census-final.log` finds exactly one external definition and four undefined external references to the same COFF spelling in the five objects, with all twelve scoped DIR32 operands resolving to VA `0x012F7178`. It also proves both ledger edits are single-row additions preserving every prior byte. `link-comparison.log` finds no added link blockers and confirms that only the three unresolved old external data spellings disappear.

Raw addition, scoped byte verification, CSV, pin consistency, declared-unmatched and before/after link outputs are retained under `build/rlink/patch-check-012f7178-1791148216/`. `build/worker-final.md` records their exit statuses, LINKED measurements and remaining unrelated blockers. The link result is a preview against the recorded census rather than a whole-program link.

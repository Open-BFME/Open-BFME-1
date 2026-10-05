# Datum identity at VA 0x012B7430

Corrected four competing declarations to the existing `g_guiFxWindowHandle` spelling and defined it once as a signed four-byte int initialized to -1 in `AptGuiFXRegisterCallbacks.cpp`.

Retail RVA `0x00510FA0` loads the `GuiFX.apt` name, calls the window-manager vtable slot at byte offset `0x3C`, and stores EAX to this datum. RVA `0x00510B50` tests it against -1, passes it to the window manager for release, then stores -1. RVA `0x00510BF0` returns whether it differs from -1. RVAs `0x00510C10`, `0x00510C70`, and `0x00510DC0` pass its value with the EA strings `HideToolTip`, `MoveToolTip`, and `ShowToolTip`. These are handle-value operations, not pointer dereferences.

Its initial bytes are FF FF FF FF; the definition has no relocation. The window-manager receiver is the separately pinned global at VA `0x012F19E8`. The datum is a loader return and first action/release argument, with -1 as the invalid sentinel. There is no evidence that it points to a `BfmeX1074` instance.

The moved tooltip source now declares the datum as int. Its existing separately pinned action callee still has a legacy pointer parameter, so the source converts the handle bits explicitly at that call boundary while retaining the callee identity and the matched function ABI. No callee wrapper, forwarder or alias was introduced. This BFME Apt GUI role has no exact Zero Hour declaration.

A retail dereference of the datum as an object pointer, a different loader-return contract, a sentinel other than -1, a datum inside its four-byte range, or a changed verified function would refute the correction.

The inspected extent is VA `0x012B7430` through exclusive `0x012B7434` in `.data`. Initial bytes are `ff ff ff ff`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?Data00EB7430@@3HA` | 1 |
| `?TheBfmeHeldHandle@@3HA` | 1 |
| `?g_bfmeVal995B@@3HA` | 2 |
| `?g_bfmeY1074@@3PAVBfmeX1074@@A` | 1 |
| `?g_guiFxWindowHandle@@3HA` | 1 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x00510B50` | `?Gen_00510b50@@YAXXZ` | VA 0x910b6f: `mov eax, dword ptr [0x12b7430]`; VA 0x910b85: `mov dword ptr [0x12b7430], 0xffffffff` |
| `0x00510BF0` | `?Rva00510BF0@@YA_NXZ` | VA 0x910bf0: `mov ecx, dword ptr [0x12b7430]` |
| `0x00510C10` | `?bfmeGo995B@@YAXXZ` | VA 0x910c10: `mov eax, dword ptr [0x12b7430]` |
| `0x00510C70` | `?bfmeGo1074A@@YAXMM@Z` | VA 0x910cbd: `mov edx, dword ptr [0x12b7430]` |
| `0x00510DC0` | `?Rva00510DC0@@YAXPAVUnicodeString@@PAVAsciiString@@HEI@Z` | VA 0x910f1e: `mov eax, dword ptr [0x12b7430]` |
| `0x00510FA0` | `?registerGuiFXCallbacks00510FA0@@YAXXZ` | VA 0x91100d: `mov dword ptr [0x12b7430], eax` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b7430.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.

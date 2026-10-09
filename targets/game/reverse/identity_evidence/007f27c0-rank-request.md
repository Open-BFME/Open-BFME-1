# RVA 0x007F27C0 rank request builder

The recovered body is `buildRva007F27C0`, an address-derived name. The retail category store is `'rank'`, followed by the `TXN`, `gsid`, `u.%d.o`, `u.%d.ot`, `u.%d.s.%d.ut`, `u.%d.s.%d.k`, `u.%d.s.%d.v`, `u.%d.s.%d.t`, `u.%d.s.[]` and `u.[]` fields. These establish the behavior but do not establish EA's original function or class name. No original owner is claimed.

## Boundary and ABI

The tested base revision is `37546667b555aebb95e03d0afd82848799c31380`. The retail image SHA-256 is `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`, matching the checked-in baseline manifest.

The complete target decode is retained in `build/007f27c0-retry/decoded.txt`. Its entry is at 0x007F27C0, its only normal return is `ret 0x10` at 0x007F29DE, and the return instruction ends at 0x007F29E1. INT3 alignment follows it. All conditional branches and both loop backedges remain inside this 545-byte extent; there is no target tail jump or indirect call. `build/007f27c0-retry/checked-target.txt` records the checked direct-call inventory.

The four incoming stack slots are read at EBP+8 (message), EBP+0x0C (`gsid`), EBP+0x10 (user array) and EBP+0x14 (signed count). Incoming ECX is overwritten before use. The reconstruction therefore uses a four-argument `__stdcall` free function. No hidden return storage or return-value construction exists. The address-derived void declaration makes no claim about a caller consuming unspecified register contents.

`build/007f27c0-retry/caller-decode.txt` records a raw direct CALL/JMP screening pass through every image section, including possible incoming jump chains. It found no direct hits on this target. There are consequently no screening hits to promote to caller evidence. `callers_of.py` likewise found no named direct caller. The ABI is established by the target's complete argument reads and cleanup, not by a guessed caller.

## Layout and type evidence

| View | Offset | Decoded use |
|---|---:|---|
| Message | 0x1C | The target stores the immediate category 0x72616E6B. |
| User header | 0x00 | Two dwords are copied, tested together for zero and passed low/high as a 64-bit value to 0x007E8E90. |
| User header | 0x08 | A dword is copied and passed to the signed integer writer as the owner type. |
| User header | 0x0C | Four bytes are copied into the local header but never interpreted; `field0C` remains opaque byte storage. It may include native padding. |
| User data | 0x10 | A signed dword bounds the inner loop and is serialized as the stat count. |
| User data | 0x14 | A pointer is reloaded for each stat access. |
| Stat | 0x00 | A dword is passed to the signed integer writer as user type. |
| Stat | 0x04 | A pointer is passed to the byte-string field writer as the key. |
| Stat | 0x08 | `fld dword ptr` loads a float, which is promoted to an eight-byte floating argument for `sprintf` with `%.4f`. |
| Stat | 0x0C | A pointer is passed to the byte-string field writer as text. |

The outer induction advances by 0x18 and the inner address offset advances by 0x10. The proposed views reproduce both strides. They are observed layouts, not inferred STL value types. There is no STL container, allocation, user value constructor or user value copy helper in this target. The complete header copy is inlined and its four load/store pairs are visible at offsets +0x62 through +0x86. No heap ownership, destructor or constructor unwind state applies to this body.

The complete primitive decodes are retained in `decoded.txt`; their checked inventories are `checked-reset.txt`, `checked-string.txt`, `checked-int.txt` and `checked-int64.txt` in the same scratch folder. Reset at 0x007E8AC0 reads the receiver's buffer at +0x10 and writes +0x18, +0x24 and +0x2C, then returns without stack cleanup. The two field writers use ECX as the receiver and `ret 8`, while the 64-bit writer uses `ret 0x0C`. The 64-bit writer formats `%I64d`, independently establishing the signed 64-bit serialization view. The callers pass the receiver without adjustment.

The complete underlying formatters are retained in `build/007f27c0-retry/decoded-type-helpers.txt`. At 0x007EC5C0 the value is a four-byte signed integer: the helper tests its sign, emits a minus sign when negative and converts its magnitude to decimal. At 0x007ECE60 the value is a nullable byte-string pointer: the helper reads successive bytes, terminates on zero and escapes special bytes. Every return and conditional branch was inspected. The executable code ends after 330 and 604 bytes respectively; the existing 355-byte and 629-byte rows also include their trailing 25-byte runtime-check descriptor data. Those descriptor bytes are not instructions or outgoing indirect calls. `checked-int-formatter.txt` and `checked-string-formatter.txt` check the complete executable extents without interpreting those data tails as code. No helper row is changed by this recovery.

The sprintf callee at 0x009F6DE2 is a six-byte indirect import jump through VA 0x0135948C. The existing import row identifies `sprintf`; the target calls it with cdecl cleanup and the standard promoted variadic values. The stack-cookie helper at 0x009F74F4 compares ECX with the cookie and either returns or tail-jumps to `_report_failure` at 0x009F74C3. The complete 49-byte failure reporter and its checked inventory are retained; its main path ends in the IAT call to `KERNEL32.dll!ExitProcess`. It introduces no additional target arguments or normal return path.

Current neighboring source declarations were inspected directly in `BfmeConv1378.cpp`, `BfmeConv1377.cpp`, `V2FeslTxnRequests.cpp` and `V2FeslResultCursors.cpp`. There is no canonical shared header for these address-derived views. Reset is called through its landed `Rva007E8AC0::run` declaration. The existing typed `Rva007E8810Message` string, integer and 64-bit declarations are retained without adding pins. The landed primitive bodies independently establish their stack widths and behavior. The Zero Hour GameNetwork tree contains no matching FESL transaction body or these indexed field formats, so no donor identity is claimed.

## Experiments and refutation

The new hypothesis was that the bank's scalar owner temporaries and retained stat pointer conceal two native operations: a complete header value copy and repeated loads through the user record after calls. The four header loads and repeated stat-pointer loads in the decoded retail body support this hypothesis. Failure to reproduce the complete copied header and the post-call pointer reloads, or failure to improve the measured compiler result, would refute it.

| Retained trial | Measured outcome |
|---|---|
| `00-saved.cpp` | 523/545 bytes; 328 non-relocation differences; 25 displaced relocation sites. |
| `01-header-copy.cpp` | 543/545 bytes; 350 non-relocation differences; 26 displaced relocation sites; enlarged frame and retained stat-pointer spill. |
| `02-reload-stat.cpp` | Exact 545-byte probe with the complete header copy and independently reloaded stat fields. |
| `03-canonical-stdcall.cpp` | Exact 545-byte probe with the explicit stdcall ABI and landed reset declaration. |
| `04-opaque-storage.cpp` | Exact 545-byte probe with the uninterpreted header word represented as four opaque bytes. |

All trials and unedited `*.probe.txt` outputs remain under `build/007f27c0-retry/`. Trial 01 alone does not support a recovery. Trials 02 through 04 demonstrate that the stat access lifetime resolves the register allocation and frame mismatch; merely reordering locals was unnecessary. The final source must also pass the ordinary byte gate, which validates call targets and string/global relocations. The external transaction pointer is still read directly at VA 0x0130A690; its original variable name is unknown.

A decoded caller requiring a live incoming receiver, a different argument order or a meaningful return value would refute the ABI view. A value helper showing different field interpretation or ownership would require revisiting the layout view. A mismatching relocation or byte in the ordinary scoped gate would refute the exact recovery.

## Working-tree validation

`build/007f27c0-retry/add-match.txt` records the verified ledger replacement, and `scoped-gate-bash.txt` records an independent successful source-scoped build. Both validate all 545 bytes, every callee relocation, all 11 string literals, the cookie data reference and the body boundary guard. `pin-consistency.txt`, `declared-unmatched.txt` and `class-gate.txt` record passing checks. No shared header or shim changed, so this recovery does not require a full gate.

The post-change `check_csv.py` command cannot complete before the coordinator stages this transaction. The read-only Git index still lists the deleted bank, so the checker raises FileNotFoundError while reading that path; the new source is also not yet tracked. Its unedited output is `build/007f27c0-retry/check-csv.txt`. The initial pre-change command passed. No index, baseline or tool was changed to suppress the failure. The coordinator must stage the new source, evidence, ledger replacement, tombstone, verdict and bank deletion together, then run the normal check with hooks active.

This checkout's `name_regression.py` CLI takes two Git revisions, despite the worker brief prescribing two file paths. The literal prescribed invocation fails with an invalid-object error, retained in `name-cli-check.txt`. The tool's `regressions` API was run directly against the preserved old bank and final source and returned no findings; `name-file-check.txt` retains that output. The coordinator's staged history check remains required.

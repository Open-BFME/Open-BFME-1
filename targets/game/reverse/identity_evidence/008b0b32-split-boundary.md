# Assigned suffix at 0x008B0B32

The assigned suffix is an interior block of the complete function at 0x008B0B00. It cannot be landed as a standalone C++ function at the assigned extent. The ledger and pins remain unchanged. This investigation used revision 20f64813a005b14e1c5326631287c2ea4bb1f878 and model gpt-6.1-sol.

## New hypothesis and refutation

The current ledger has C++ owners for all five direct callees. Reusing their declarations, allocation contracts and string lifetimes might therefore resolve the earlier missing-payload and layout reports. The boundary hypothesis would be refuted by an independent entry at 0x008B0B32 with a self-contained frame, or by a standalone clean C++ body whose decoded prologue and epilogue satisfy the assigned extent. Neither observation was obtained. Compiler experiments instead reproduced the containing function's prefix and emitted a new exception frame when the prefix was omitted.

## Complete extent and ABI evidence

`build/008B0B32-boundary/retail_parent.txt` decodes the complete function and its following padding. The exception registration begins at parent +0x0. The conditional branch at +0x1C enters +0x32 with that registration still active. The early return is at +0x31. The other return is at +0x1E2, after restoring `fs:[0]` and discarding the inherited sixteen-byte frame. Padding starts at +0x1E3. Every conditional branch and ordinary jump in the complete body targets an instruction within this extent. There is no outgoing tail jump in the main body.

`checked_parent.txt` and `checked_suffix.txt` retain the required checked-callee results. The suffix's first argument load at its +0x3 depends on the inherited frame. The complete body reads its second dword argument with a signed comparison before entering the suffix, returns a pointer in EAX and uses caller stack cleanup. No independently validated complete caller was retained, so the original callback identity and caller-side ABI remain unverified. No real owner identity is claimed.

## Current declarations and helper evidence

The inspected source owners are `game/Libraries/Source/EA/Apt/PayloadCtorRva008AD100.cpp`, `game/GameEngine/Source/Common/Rva008B0170Ctor.cpp`, `game/GameEngine/Source/Common/Rva008B0120Ctor.cpp`, `game/GameEngine/Source/Common/Rva008AD2C0Assign.cpp`, `game/GameEngine/Source/Common/BfmeConv1402.cpp`, `game/GameEngine/Source/Common/Bfme5FiftyFour.cpp` and `game/Libraries/Source/EA/Apt/Rva008C4650HeaderedAlloc.cpp`. The neighbouring landed record body is `game/Libraries/Source/EA/Apt/Rva008B09A0ApplyRecord.cpp`. Its field names were retained. No Zero Hour AptCharacter twin was located in the assigned reference tree.

The complete payload constructor was decoded through both `ret 0x34` exits. Its string pointer is at +0, and its scalar stores cover +4, +8, +0xC, +0x10, +0x14, +0x18 and +0x1C. It reads the first and ninth arguments as value pointers and retains thirteen dword arguments. This establishes accessed storage and argument widths, rather than proving that every field is an integer. The diagnostic decimal second argument encodes the observed dword bits of -1.0f while preserving the existing thirteen-int declaration. The owner and scalar type meanings remain opaque.

The complete result constructor returns its receiver and uses `ret 4`. It adjusts the member receiver by +0x20 before the complete record copy and assignment helpers. Those helpers access the string at +0 and every scalar through +0x1C; the assignment conditionally skips sentinel values at +0x14, +0x18 and +0x1C. Their raw disassemblies and checked-callee outputs are retained as `retail_copy.txt`, `retail_assign.txt`, `checked_copy.txt` and `checked_assign.txt`.

The ordinary allocator returns EAX with caller cleanup. The intrusive link helper accepts one pointer and writes the header at -8 and -4. The target leaves the allocator argument on the stack until after linking, then removes both arguments together. The string setter has two `ret 4` exits and writes its pointer plus all four short header fields. The indirect string-pool free calls are cdecl function pointers at pair offset +4, rather than virtual methods.

## Exception ownership

`eh_parent.txt` retains the four retail unwind states. State zero deletes the ordinary payload allocation through 0x00881EB0. State one passes the result pointer and object size 0x40 to the complete sized headered delete at 0x008AB870. That helper unlinks the pointer, subtracts the eight-byte header and adds eight to the freed size. States two and three destroy distinct four-byte string temporaries through the complete 22-byte EAStringC destructor at 0x00891B80. The payload and result constructors' own unwind maps are retained in `eh_payload.txt` and `eh_value_ctor.txt`. All helper extents used for these contracts have checked-callee logs.

The private StringBase forwarding trial introduced an additional constructor cleanup state and an out-of-line string constructor, as shown by `probe07_suffix.txt` and `object_cleanup.txt`. It was rejected for ownership as well as bytes. The retained standalone diagnostic uses the earlier direct string declaration. Its assignment still emits an unproven out-of-line helper, so it is not an exact source recovery and needs no new pin.

## Compiler measurements

The table below is generated from the unedited probe outputs. Positional relocation masking reports a lower bound when relocation operands drift. These counts and quality scores are diagnostic measurements, not byte equality, ABI proof or progress.

| Experiment | Emitted bytes | Retail bytes | Masked differences | First difference |
|---|---:|---:|---:|---|
| [01_parent](../../../../build/008B0B32-boundary/probe01_parent.txt) | 458 | 483 | 345 | +0x33 |
| [02_parent](../../../../build/008B0B32-boundary/probe02_parent.txt) | 458 | 483 | 335 | +0x33 |
| [03_parent](../../../../build/008B0B32-boundary/probe03_parent.txt) | 468 | 483 | 301 | +0x45 |
| [04_parent](../../../../build/008B0B32-boundary/probe04_parent.txt) | 460 | 483 | 250 | +0x96 |
| [05_parent](../../../../build/008B0B32-boundary/probe05_parent.txt) | 460 | 483 | 250 | +0x96 |
| [06_parent](../../../../build/008B0B32-boundary/probe06_parent.txt) | 468 | 483 | 255 | +0x96 |
| [07_suffix](../../../../build/008B0B32-boundary/probe07_suffix.txt) | 440 | 433 | 356 | +0x0 |
| [08_suffix](../../../../build/008B0B32-boundary/probe08_suffix.txt) | 432 | 433 | 353 | +0x0 |

The mechanical EH generator and bounded shape search retained raw probes and source snapshots under `build/008B0B32-boundary/eh_valid_*`, with the search receipts under `build/shape_search/`. Toggling /EHsc and marking the link helper nonthrowing did not change the first trial's measured output. The generator also misidentified a local declaration as a callee declaration; both resulting compiler failures remain in `eh_probe_02.txt` and `eh_probe_03.txt`, and that invalid choice was removed from the subsequent search. The pointer-copy family generator offered no applicable choice.

Moving the float-bit conversion into a union did not remove its materialization. Modeling the embedded range and using the decoded dword immediate improved the containing-body comparison. Giving the allocator an extra static inline donor layer produced unchanged bytes. The StringBase forwarding trial was rejected for the cleanup issue above. Omitting the prefix produced a separate C++ exception frame, rather than reproducing the assigned inherited-frame block.

## Preserved source and checks

The standalone diagnostic source is archived immutably at `targets/game/reverse/attempt_history/0x008b0b32/3cb353b8947cb090c1805d14e6f38dc672ed68d1b47ee0dfda59f1ab95a92e45.json` with measured positional quality 0.1801. It is not installed as an active finish bank because the assigned boundary is invalid. The better ownership model for the complete containing body remains at `build/008B0B32-boundary/trial04.cpp`; all other source snapshots and raw probes remain under the same task directory.

`check_csv_final.txt` and `pin_consistency.txt` pass. `gate_existing_dump_bash.txt` passes the unchanged assembly row's scoped gate, which proves no C++ conversion. `gate_candidate08.txt` fails the strict candidate byte check and reports the unproven out-of-line assignment symbol. It used a diagnostic row in memory; no ledger row, pin, baseline or hook was changed. The Windows build wrapper could not locate Python in this sandbox, so its failure is retained in `gate_existing_dump_retry.txt`; the allowed explicit Git Bash entry point completed the existing-row gate. No header or shim changed, so no full gate was required.

Reopening requires an assignment for the complete parent extent and a coordinated treatment of the two existing dump rows, followed by caller-side ABI validation, correct inline string ownership, byte verification and all normal landing checks. More standalone suffix register experiments cannot remove the inherited frame requirement.

The handoff check confirms exactly one appended verdict, unchanged preceding log bytes and an archive hash equal to the measured source. Default `git diff --check` flags the CRLF terminator that `re_log.py` appends. There are no trailing spaces or tabs, and the read-only check with `cr-at-eol` passes. Both outputs are retained in `handoff_checks.txt` and `handoff_checks_crlf.txt`.

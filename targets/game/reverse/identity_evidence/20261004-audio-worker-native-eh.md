# Audio worker 00694130: native production integration

This integrates the exact 2026-10-03 bank rather than a new source-shape search.
Its SHA256 is 0df115428a0c7858cc2dabfa27d215bc45177eaafcaa38176e5262440750e5f3;
its source and measured result remain in attempt_history/0x00694130. The
[reference ABI evidence](20261003-audio-worker-reference-abi.md) independently
proves the receiver, hidden result, filename const reference and field views.
The [default-constructor evidence](20261003-audio-handle-default-ctor.md) proves
the separate 9-byte canonical provider.

## Production binding and complete extent

The native Rva00694130AudioWorker.cpp production object reproduces all 203
bytes at 00694130 with production symbol resolution, masked=false and no
unresolved relocations. RET12 is at 006941F8 and INT3 starts at 006941FB.
The sole new typed helper pin is Rva00694710AudioWorker::rva00693B90 returning
Rva006910F0Handle and receiving (AsciiString const&, int), at 00693B90.
Retail ILT0003214B jumps there. The existing canonical constructor row supplies
006910E0 through ILT0002833F. No alternate owner or caller at 006B5A80 changes.

## Actual emitted exception graph

The parent prologue DIR32 relocation at +3 names its compiler-emitted handler.
Its retail pointer is 00C47291. That 10-byte handler points to FuncInfo00E36D68
and jumps to CxxFrameHandler009F6DD6. The 28-byte FuncInfo carries magic
19930520, maxState=2 and a pointer to unwind map00E36D58. The 16-byte map
has exactly these independently decoded retail and compiled transitions:

| State | Previous | Retail action | Actual production label | Extent |
| --- | --- | --- | --- | --- |
| 0 | -1 | 00C47270 | $L913 | 25 bytes |
| 1 | 0 | 00C47289 | $L916 | 8 bytes |

The first action tests the construction mask at EBP-10, takes the hidden
return slot at EBP+4, and calls the canonical handle destructor through
ILT000298E8 ->00691130. Its conditional RET is at00C47288, proving25 bytes.
The second takes the filename at EBP+8 and calls the canonical AsciiString
destructor through ILT0000D828 ->0005EE90. Both actions arise naturally from
the parent C++ lifetime; neither is separately implemented or naked assembly.

A strict relocation pass binds every DIR32 and REL32 in the parent, handler,
FuncInfo, unwind map and both actions to those independently proven retail
addresses. It compares all290 bytes, with no masked relocation slots.
The production parent object SHA256 before ledger-only action promotion is
9c2ed8dc22ddbbe0cdc02c08e244718b5916d5cb792a74e1920a758fcdea4488.
These labels must be rederived from the unwind states if later source/header
edits renumber them; byte-identical labels alone are not ownership proof.

## Accounting

The parent replaces203 bytes of generated assembly. Action00C47270 replaces
25 more bytes of assembly only after its natural emitted body is verified.
The9-byte constructor and8-byte action00C47289 were already generated C++;
re-homing them is identity/ownership repair and contributes zero newly
converted bytes. Total genuine dump-to-C++ gain for all four rows is228 bytes;
any authored-lane reclassification of the other17 bytes is reported separately.

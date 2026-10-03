# RVA 008B0EE0: complete property-dispatch reconstruction, unfinished

GPT-6, 2026-09-27. This is a bank, not a byte-match claim. The complete
native body emits 7,110 bytes against 7,162 retail bytes. The positional
comparison has 5,076 differing masked bytes and 52 missing bytes:
`1 - (5076 + 52) / 7162 = 0.28399888299357723`. Normalized instruction
shape is approximately 0.892; it is diagnostic only. The stack frame now
matches retail's `sub esp, 1Ch`. No production source, pin, baseline, or
function-ledger ownership was changed.

## Corrected cleanup alternative (2026-09-27)

**Historical note:** the preferred bank at the time had incorrect empty
deallocation stubs. Session4 (2026-10-03) supersedes it with the corrected
cleanup model and an improved guard shape; see
[the continuation evidence](008b0ee0-session4-guard-bank.md). The original
[corrected immutable alternative](../attempt_history/0x008b0ee0/ba16d5160f1e1d9a2f18d7b7974bd92af3f1cc28f73ccc53570f71a0c444b64b.json)
instead. Its identical score intentionally leaves the preferred pointer unchanged;
this is an exception-cleanup correction, not a native-coverage claim.

Fresh `tools/eh_info.py 0x008B0EE0` decodes 35 retail unwind states. Seven
allocation failures push size 16 and call 00891A80; 26 push size 36 and call
00897670. The remaining two actions release a string through 00891B80.
The source now declares `Rva008A9B00::operator delete(void *, unsigned)`
using its existing, independently witnessed 00891A80 pin. `BfmeA1029` inherits
the empty layout-only `Rva00897670HeaderedDelete` view and its existing sized
operator, already matched in `HeaderedDeleteOperators.cpp`. The unused empty
base delete was removed; no additional main-function cleanup is emitted.

Both before and corrected drafts were freshly compiled. The 7,110 main bytes
are identical, SHA-256
`e5e783c91968f961448a5fa9a6a17911a663b545238a9f350bc55d89b7e13157`.
All 476 relocation sites, kinds and targets agree after resolving renumbered
local compiler labels to their unchanged offsets. The original 5,076 masked
differences, 52-byte extent penalty and score `0.28399888299357723` remain.

The corrected compiler unwind map has all 35 predecessor entries equal to
retail. Each action is instruction-exact after resolving its single call or
jump: seven 15-byte sized-string deletes, 26 15-byte headered deletes and two
8-byte string-release actions. The visible 22-byte string release also equals
00891B80 after resolving the existing pool global to VA 01337A30. These
checks establish the cleanup contracts without asserting that the unfinished
main body or all its exception behavior is exact. No funclet, function,
coverage, pin or baseline claim was added.

The [state-by-state receipt](008b0ee0-cleanup-audit.json) preserves each
predecessor, cleanup RVA and resolved target. Reproduction scratch is
`build/apt7162-cleanup/`: `before.cpp`, `corrected.cpp`, their probe receipts,
`retail-eh.txt`, and `audit.py`.

## Boundary and identity evidence

Read-only Ghidra was run against the independently SHA-256-verified identical
retail executable (`c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9`).
The entry at VA 00CB0EE0 has a complete SEH prologue. Its final return is at
00CB292D. The instruction extent is 6,734 bytes; the following alignment and
three DWORD tables plus the byte-index remap extend the owned range through
00CB2AD9, immediately before INT3 alignment and the next function at 00CB2AE0.
The existing 7,162-byte extent is therefore correct. Linear disassembly of the
full range ends inside table data; that is not a truncated epilogue.

Fresh Ghidra identifies a real caller at VA 00CC3E5A. Independently decoded
RVA 008C3E50 pushes its second and first stack arguments, calls 008B0EE0,
cleans eight bytes and returns with `ret 8`. The target itself returns without
callee cleanup, and its returned EAX is a pointer to a script value. Its two
arguments are a value/owner pointer and a pointer to a narrow-string wrapper.
The older generated equality-operator name is not semantic evidence. The
reconstruction keeps an address-derived function and owner identity.

The two lookup callees read actual retail arrays of `{const char *, int}`:
VA 012D55E0, reached by 008ABF40, and VA 012D5E18, reached by 008D48F0.
Their contents independently identify text and display-property dispatch.
Examples in the first table are `autoSize=1`, `background=2`,
`backgroundColor=3`, `border=4`, `borderColor=5`, `length=7`, `text=12`,
`textHeight=14`, `textWidth=15`, `type=16`, `variable=17`, `wordWrap=18`,
`_height=19`, `_width=20`, and `mouseWheelEnabled=21`.
Examples in the second table are `_x=1`, `_y=2`, `_xscale=3`, `_yscale=4`,
`_currentframe=5`, `_totalframes=6`, `_alpha=7`, `_visible=8`, `_width=9`,
`_height=10`, `_rotation=11`, `_target=12`, `_framesloaded=13`, `_name=14`,
`_url=16`, `_xmouse=21`, and `_ymouse=22`. Unsupported table values follow
retail's default path; they have not been invented as missing cases.

## Callee and layout contracts

`tools/callees.py 0x008b0ee0 6734` covers the entire instruction extent.
The 26 lazy callback factories allocate 36 bytes with 00897640, initialize
with 00899FC0, change the packed flag field at +4, and call virtual slot zero.
The callback addresses and per-callback cache globals come directly from
aligned retail operands. The code retains opaque address names for both.
The local native constructor `BfmeA1029(int)` independently emits the exact
31-byte body at 00899FC0, with the same two relocation contracts as the
already-owned `BfmeA1029::bfmeGo1029A(int)` body. Its actual base initializer
00899F00 is passed `(9, 8)`, its callback is at +20h, and its final vtable
store uses the existing `bfmeVft1029A`. This helper is already owned and
would add zero coverage. No speculative constructor pin was added.

The 12-byte boolean, integer and float values use the existing native base
and derived constructor contracts, actual vtables, and registry at VA
01337810. Their free-list links overlap the +8 payload. String values are
16 bytes, use the out-of-line 008A9B00 constructor, and link through +0Ch.
Their reused payload is truncated through 0089EC50. String assignments
increment the source's 16-bit reference count, decrement/free the old buffer
through VA 01337A30, and then store the new pointer. The empty buffer is
VA 012D5298. The indirect allocator is VA 01337828.

The object uses packed flags at +4, a six-float transform at +10h, a parent
pointer at +4Ch, and a state pointer at +50h. State fields remain address
qualified: the name oracle has no witnessed layout for the opaque views.
Two transform paths call 008D2D10, and three bounds paths use 008AE2B0.
Retail reads AL from the 008AD050 predicate; the bank uses the existing
four-byte return declaration and explicitly observes its low byte.

## Compiler findings and remaining work

The first complete draft emitted 6,722 bytes. Explicitly inlining the native
value constructors and refcount operations restored all factory behavior.
Shared bounds/matrix scratch storage restored the 1Ch frame. A real native
constructor call, rather than an inline wrapper around a pointer-returning
method, removed extra copies after the 26 allocations. Reordering the second
switch by independently decoded targets reproduced the actual callback order
and EH-state numbering. The explicit nested `autoSize` case/default bodies
retain its retail jump table.

The unresolved mismatch is source control flow and allocation, beginning in
the entry guard: retail keeps both the kind and original flags and reloads the
string argument from its stack slot. The current compiler keeps that argument
in a saved register and specializes the fallback kind checks. Later pooled
return paths consequently use different registers and block sharing. Pointer
versus reference arguments, signed/enum kind locals, explicit fallback labels,
and equivalent guard spellings did not close the gap. All these experiments
remain scratch; the complete bank is the starting point for the next pass.

Local receipts are under `build/round4-apt7162/`: Ghidra output, full retail
disassembly, `word-tables.txt`, `case-order.txt`, `code-callees.txt`,
`bank-probe.txt`, `bank-audit.txt`, and the exact `ctor-probe.txt`.

# RVA 008B0EE0: complete property-dispatch reconstruction, unfinished

GPT-6, 2026-09-27. This is a bank, not a byte-match claim. The complete
native body emits 7,110 bytes against 7,162 retail bytes. The positional
comparison has 5,076 differing masked bytes and 52 missing bytes:
`1 - (5076 + 52) / 7162 = 0.28399888299357723`. Normalized instruction
shape is approximately 0.892; it is diagnostic only. The stack frame now
matches retail's `sub esp, 1Ch`. No production source, pin, baseline, or
function-ledger ownership was changed.

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

# RVA 008A7B00: keyboard property dispatch

GPT-6, 2026-09-27. Complete native C++ reconstruction of the 5,603-byte
retail body, including its compiler-generated switch tables. No inline
assembly, emitted instructions, or fabricated helper behavior is used.

## Boundary, ABI and identity

Fresh read-only Ghidra against the SHA-256-verified retail executable identifies
this body as the function pointer at VA 01136260. The surrounding table begins
at 01136240; this is its +20h dispatch entry. The body reads two stack arguments,
never reads incoming ECX, and every return removes eight argument bytes. The
address-derived free-function spelling therefore uses `__stdcall`. Its first
argument is a value pointer checked for null, low-six-bit kind 24, and active
bit 15. The second is a pointer to a narrow-string wrapper, whose buffer has
16-bit length at +2 and text at +8. It returns a value pointer in EAX.

The existing extent is complete: code ends at RET8 at VA 00CA9007 (through
00CA9009); padding at 00CA900A precedes the 27-entry DWORD dispatch table at
00CA900C and 107-byte remap table at 00CA9078. The latter ends at 00CA90E2,
so the complete extent is 00CA7B00..00CA90E2, exactly 5,603 bytes. INT3 follows.
Ghidra's 5,386 instruction bytes exclude the tables. The callee inventory is
complete when bounded to the code extent; the full-range linear-disassembly
warning is caused by data, not a missing epilogue.

Lookup 008A3790 is independently owned as `bfmeFind1229(const char*, unsigned)`.
Its aligned table load uses VA 012D52A8, an array of `{const char*, int}`. Reading
that retail table establishes all 26 property names without guessing a class:

| ID | Name | Result |
|---:|---|---|
| 1 | BACKSPACE | integer 8 |
| 2 | CAPSLOCK | integer 20 |
| 3 | CONTROL | integer 17 |
| 4 | DELETEKEY | integer 46 |
| 5 | DOWN | integer 40 |
| 6 | END | integer 35 |
| 7 | ENTER | integer 13 |
| 8 | ESCAPED | integer 27 |
| 9 | HOME | integer 36 |
| 10 | INSERT | integer 45 |
| 11 | LEFT | integer 37 |
| 12 | PGDN | integer 34 |
| 13 | PGUP | integer 33 |
| 14 | RIGHT | integer 39 |
| 15 | SHIFT | integer 16 |
| 16 | SPACE | integer 32 |
| 17 | TAB | integer 9 |
| 18 | UP | integer 38 |
| 100 | isDown | callback at RVA 008A5250 |
| 101 | isToggled | callback at RVA 008A52E0 |
| 102 | getCode | callback at RVA 008A52F0 |
| 103 | getController | callback at RVA 008A5360 |
| 104 | addListener | callback at RVA 008A5380 |
| 105 | removeListener | callback at RVA 008A53D0 |
| 106 | getAnalogStickInfo | callback at RVA 008A6CB0 |
| 107 | getAscii | callback at RVA 008A5330 |

Names describe the witnessed properties. The owner and callable identities
remain address-derived because the table does not prove their original C++ names.

## Native values and independently proved constructor dependency

Integer results use the existing native base/derived constructor contracts
at 00899560 and 008A1110, with vtables VA 01135D68 and 01136400, kind 7,
12-byte size, payload/free-list link at +8, free list VA 013387D0, registry
VA 01337810, and allocator function pointer VA 01337828. The typed inline pool
helper preserves the independently witnessed base/derived alias contexts.
All eighteen constant paths are normal C++ calls that the retail compiler inlines.

Each of the eight lazy callback branches allocates 36 bytes through 00897640,
then passes one callback address to constructor body 00899FC0 with the allocated
object in ECX. The constructor returns that object in EAX and removes four
argument bytes. The caller then changes packed flags at +4 and invokes slot zero.
The eight cache globals are independently aligned at VA 01337A7C, 01337A80,
01337A84, 01337A8C, 01337A90, 01337A94, 01337A98 and 01337A88.

The constructor contract was established independently before this caller was
written: the existing ledger body `BfmeA1029::bfmeGo1029A(int)` at 00899FC0 is
31 bytes and calls the existing base initializer 00899F00 with `(9, 8)`, stores
its argument at +20h, and installs the existing `bfmeVft1029A`. A separate native
C++ constructor experiment reproduces all 31 bytes with those same two
relocations. This proves an actual constructing call, rather than relying on
this caller's desired byte shape. Its return/callee cleanup is also witnessed
at all eight aligned call sites here and 26 independent sites in 008B0EE0.

The single new pin `??0Rva00899FC0@@QAE@H@Z` names that independently established
constructor ABI by address. It points to the actual body, not an ILT route.
The production TU contains only its declaration; the existing 31-byte ledger
body stays owned where it was, contributes zero new bytes, and retains its
existing resolver identity. This avoids inventing a semantic class or counting
a helper twice. Pin-consistency checks are run before and after the addition.

The retail unwind map has eight 15-byte cleanup actions at RVA 00C58160
through 00C581C9. Each pushes size 36 and the pending allocation, calls
00897670, and cleans eight bytes. The native class inherits the existing sized
operator delete through an empty allocation-policy view; its object size stays
36 bytes. This makes all eight compiler-generated cleanup actions byte-exact
with the actual existing `Rva00897670HeaderedDelete` call. A forwarding delete
wrapper was semantically correct but emitted an extra wrapper target; the
inherited operator removes that difference. The earlier empty-delete draft was
rejected before publication. These actions are independently verified and add
zero extra coverage to this claim.

## Verification

The complete body probes at 5,603/5,603 with zero differing bytes outside its
314 relocation sites. Strict resolution verifies all 17 direct calls with zero unresolved targets.
The 22 global identities are consistent, with zero new inconsistencies; the
body has no string-literal relocations. Normal scoped commit/push gates are
required for publication. The local receipts
are under `build/round4-apt5603/`; `final-probe.txt`, `strict.txt`,
`vtable-proof.txt`, `word-table.txt`, `eh-info.txt`, `cleanup-proof.txt`, and pin-check receipts accompany the
fresh Ghidra and full retail disassembly. The constructor's independent
31-byte experiment is in `build/round4-apt7162/ctor-probe.txt`.

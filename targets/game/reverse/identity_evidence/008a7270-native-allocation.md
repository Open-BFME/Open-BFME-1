# RVA 008A7270 and cleanup C5807F

2026-10-03, gpt-6-astra. Refines the existing 0.45 bank; no semantic owner name is claimed.

## Extent and ABI

Retail image base is 00400000. Both Ghidra search_byte_patterns and an independent
raw PE search find the direct body VA 00CA7270 in table cell VA 011362B0.
This proves a table entry, not an original C++ class or member spelling.
Incoming ECX is unused. The second stack parameter is a pointer to a string-buffer
pointer; text starts at buffer+8. All three returns pop eight argument bytes.
The last RET8 starts RVA008A73DD and ends008A73DF, exactly368 bytes from entry;
008A73E0 begins the next independent FS-registration prologue (there is no INT3
padding here). Ghidra creation/decompilation agrees with the complete368B extent.
The free stdcall entry therefore stays rva008A7270 with two stack arguments.

## Actual allocation lifetime and bindings

The former bank manually allocated and initialized storage, suppressing EH.
Retail allocates0x2C bytes via the private function pointer at VA01337828,
adds8 to the returned block, and calls bfmePush at RVA00897300. Independently,
that helper writes prev/next at payload-8/-4, proving the two-DWORD header.
The new-expression allocator expresses the same header using unsigned-int pointer
arithmetic. Both a two-word-header struct and unsigned-pointer form produce the
same exact body; the old char-pointer expression produced MOV+ADD instead of LEA.
This is source shaping with a witnessed header, not extra observable work.

The native object view has a32B base, containing vptr at0, flags at4 and24 opaque
bytes, plus one4B callback at20h. The actual calls target the existing
Rva00899F00Base constructor at899F00 with arguments9 and8. Its native definition
in Rva008B2EF0Constructors.cpp independently witnesses the same32B layout and
constructor ABI. The inline derived view stores the already named bfmeVft1029A
(table VA01136128), then the callback. It emits no new helper identity or table.

The two callbacks are the existing aptRegisterFlagged008A5440 and
aptUnregisterFlagged008A5490, not raw code-address integers. The cached globals
are the existing g_bfmeC1062/g_bfmeD1062 (VA01337A9C/01337AA0), declared with
exactly the canonical BfmeC1062 pointer type from BfmeConv1062.cpp. Virtual slot0
uses that existing declaration. The final table slots begin direct VAs00C991B0,
00C991E0,00C91810,00C99410; no semantic method name is newly asserted.

Intrinsic strcmp on actual addListener/removeListener literals supplies the
retail REPE CMPSB sequences of12 and15 bytes including terminators. The prior
bank's fixed-count memcmp used a different instruction shape. Private allocation
and deallocation pointers are not PE imports. All direct callee spellings and
external table/global identities pre-existed; no symbol pin is added.

## Cleanup ownership

Parent008A7270+8 pushes handler VA0105808E. The handler loads FuncInfo VA0124741C,
whose two-state map is VA0124740C. State0/-1 selects actionC58070; state1/-1
selects C5807F. The latter pushes36, loads the saved allocation at EBP+8, calls
canonical Rva00897670HeaderedDelete::operator delete at897670, adjusts ESP by8
and returns atC5808D, giving exactly15 bytes before the handler atC5808E.
That independently decoded34B delete unlinks the payload and calls private
free dispatch01337830 with payload-8 and size+8, matching the allocation header.
Native inherited sized delete supplies these real cleanup actions; it is not an
empty cleanup stub or a synthetic stand-alone lifetime wrapper.

Both native predecessor states and their corresponding COFF labels are checked
before promoting the action. The complete parent is tested with add_match's
strict byte, callee, string and data-reference verification, not just the masked
probe. The existing bank is retained as historical evidence.

## Source-move name-check pairing

The name checker pairs the removed bank-only BfmeA1029 declaration with
Rva00897670HeaderedDelete in the new source because of their class declaration
positions. This is not a rename: the latter is the already-matched allocation
policy at897670, whereas the former modeled the36B callback object initialized
by899FC0. Their independently decoded bodies perform different operations,
and the new source still has a separate36B object view. BfmeA1029 remains
unchanged in BfmeConv1029.cpp. The hash-scoped name_corrections entry records
only this false source-move pairing; it does not grant a semantic identity or
permit rewriting that existing class.

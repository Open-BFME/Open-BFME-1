# Ring removal at 0x008A09D0

The native member `BfmeRing008A0890::removeRva008A09D0` replaces the
291-byte generated dump. The original member spelling is unknown; the new
spelling retains its address. It uses the existing TU's ring and record types.

## Boundary and ABI

The complete body is `[0x008A09D0, 0x008A0AF3)`. All four exits use `ret 4`;
the last is at 0x008A0AF0, followed by INT3 padding. ECX is the receiver and
the sole stack argument is the value pointer. EBX, EBP, ESI and EDI are saved
and restored. The caller at 0x008BDFBA does not consume a return value.

The insert caller at 0x008D259C and removal caller at 0x008BDFBA both load
the unadjusted receiver from `[0x013377D8]`. The matched insert at 0x008A0890
independently establishes the same 20-byte records and receiver fields:
storage at +0, write pointer at +4, read pointer at +8, capacity at +0x12B0.
Insert writes zero at record +0 and the retained value pointer at +0x10;
removal tests exactly those fields. No new global or shared header is needed.

## Calls and behavior

The two direct calls, at 0x008A0A54 and 0x008A0AA6, target 0x009F6EC6.
That six-byte import jump uses IAT slot 0x0135945C, whose PE import is
`memmove`. The existing `_memmove` pin is consistent with that route.
The COFF REL32 operands are at offsets +0x85 and +0xD7.

The two virtual calls use slot +4 with the value pointer in ECX, no stack
arguments, and no consumed result. Independently matched ring clear at
0x008A07D0 traverses the same ring and, for a kind-zero record, loads its
+0x10 value pointer at 0x008A07E6 and calls that slot at 0x008A07FD.
The same EBX value passed to this removal also reaches matched 0x008A0BA0,
whose slot +4 call is at 0x008A0BD0. `void slot04()` describes this observed
unused-result call contract; it does not assert an original callback name
or identify every possible concrete runtime vtable.

Removal shifts the trailing segment left or the leading segment right and
adjusts the corresponding ring pointer with wraparound. The first-slot
branch advances the write pointer without calling slot +4, matching retail.

## Verification

The unchanged production-path gate passes all five functions in
`BfmeRing008A0890.cpp`: 30, 92, 106, 109 and 291 bytes. String, constant,
readonly-load, DIR32 and body-guard checks pass. Both new memmove relocations
resolve. The object defines exactly these five code sections, with no vtable,
exception-cleanup code or additional data definitions.

The plain `while` loop is exact when its cursor is initialized from
`m_write`; initializing it from the cached head instead moves the first
comparison and leaves five differing bytes. No assembly, volatile barrier,
forced register, new pin or baseline change is used. The complete conversion
is 291 bytes. Unchanged `progress.py` reports +290 in its headline C++ metric
because it excludes one embedded 0xCC byte; its exact-coverage breakdown
reports C++ +291 and ASM-only -291, with total exact coverage unchanged.
No linking gain is claimed.

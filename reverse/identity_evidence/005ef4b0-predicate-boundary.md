# RVA 0x005EF4B0 predicate and complete extent

The receiver has no proved semantic class identity. The new name retains its
address. ECX is the receiver and the single stack argument is a selector;
all return paths use RET 4. There are no direct calls.

Retail code at 0x005EF4B0 subtracts one from the selector and checks unsigned
range 0..5. Its indexed jump reads six absolute entries from 0x005EF534:
0x005EF4C1, 0x005EF4C1, 0x005EF52E, 0x005EF52E, 0x005EF4F6,
0x005EF4C1. Thus selectors 1/2/6 take the sum path, 5 the product path,
and all other selectors return true.

Both paths read index +0xAC and the occupied word at this+index*16+0x1C.
An occupied entry returns false at 0x005EF4F1. The sum reads floats in
order +0x9C, +0x98, +0x94 and compares less than the float at VA0x01075354.
TEST AH,5 / JNP rejects unordered comparisons. The product uses the same
order and compares greater than VA0x01113520 with TEST AH,0x41 / JNE.
The global name Rva00064680NegativeScale is an existing address binding;
its spelling is not used as evidence for meaning or sign.

The old 118-byte dump stops immediately before the shared MOV EAX,1 / RET4
at 0x005EF526. That 8-byte suffix and the separate MOV AL,1 / RET4 at
0x005EF52E were incorrectly claimed as standalone aliases. Both are internal
branch destinations of this function, not independent identity evidence for
W3DShadowGeometry::init or AddressPredicate0017C9D0. Retire these two alias
rows without editing their source files. A NOP at 0x005EF533 aligns the six
DWORD table at 0x005EF534..0x005EF54B. Complete emitted extent: 156 bytes.
The probe's linear disassembly warning at the end decodes this jump-table
data as instructions; the table bounds are established by its range check.

Probe of ?predicate@Rva005EF4B0PredicateClass@@QAE_NH@Z: 156/156 bytes,
exact modulo nine relocations (table and constants). The scoped build is
required to verify those relocations. Short-circuit conjunction reproduces
the shared EAX-zero return; explicit separate false returns had added a
four-byte AL-zero tail. All guards and unordered comparison behavior remain.

Accounting: 118 bytes were ASM-only; 13 bytes were already claimed C++
interior aliases; 25 bytes extend previously claimed exact coverage. Report
156 bytes implemented, 143 net new C++-claimed bytes, and 25 additional
boundary bytes separately; no evaluator change.

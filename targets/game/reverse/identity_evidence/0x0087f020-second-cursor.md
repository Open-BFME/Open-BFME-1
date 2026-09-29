# 0x0087F020 — bfmeFillBE, the second-cursor evidence

## Body

109 bytes, cdecl, four arguments, one pointer returned in EAX:

    BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
                           const BfmeElemBE &value, const BfmeFalseBE &);

It is the STLport `uninitialized_fill_n` for a 0x24-byte element: a counted
loop, a placement-new null guard per iteration, and the advanced `first`
returned.

## Identity (caller-backed, not guessed)

Two callers, both with ledger names:

- `?overflow@BfmeVecBE@@QAEXPAUBfmeElemBE@@ABU2@ABUBfmeFalseBE@I_N@Z`
  at 0x0087FBE0, matched in `Rva0087FBE0Overflow.cpp`. Its disassembly calls
  0x0087F020 once, pushing `(newFinish, fill, value, atEnd)`.
- `?_M_fill_insert@?$vector@URva0087FDC0Element@@...` at 0x0087FDC0, matched
  in `Rva0087FDC0VectorFillInsert.cpp`, which calls it as
  `uninitialized_fill_n`.

The `false_type` fourth argument is unused in retail (no read of `[esp+0x10]`),
which is why the mangled name keeps it. The name `bfmeFillBE` follows the
already-matched siblings `bfmeCopyAA` (0x0087EAA0) and `bfmeFillE9`
(0x0087E9B0).

## The one real obstacle: the second induction variable

Retail seeds a SECOND cursor and uses negative displacements through it:

    +0014  lea esi, [ebx + 0x18]     ; second cursor, NOT first+0x00
    ...
    +002b  mov [esi - 0x14], ecx     ; element +0x04
    +0031  mov [esi - 0x10], edx     ; element +0x08
    +0037  mov [esi - 0x0c], eax     ; element +0x0C
    +003d  mov [esi - 8],    ecx     ; element +0x10
    +0046  mov [esi - 4],    edx     ; element +0x14
    +0050  mov [esi],        eax     ; element +0x18
    +004d  lea ecx, [esi + 4]        ; element +0x1C, the tail ctor's this
    +005a  mov [esi + 8],    dl      ; element +0x20
    +0060  add esi, 0x24             ; advanced in lockstep with ebx

So `ebx` walks the element from +0x00 and `esi` walks a subobject whose base
is the element's +0x18, reaching the group's earlier fields backwards.

MSVC 7.1 emits this second cursor ONLY when the +0x10..+0x20 group is its own
aggregate member of `BfmeElemBE`. With the group flattened into the outer
struct, the compiler uses a single cursor and the body comes out 99 bytes
(`build/gen_H1.cpp`: `int m_00..m_0C; BfmeCoordBE m_10; BfmeTailBE m_1C;
char m_20`), or 117 with two `Coord` members (`build/gen_H2.cpp`).

Making the group an aggregate member also produces the other two retail
details for free, which is the confirmation that the nesting is the right
reading rather than a coincidence:

- the count guard becomes `jbe` (unsigned `<= 0`) at +0x0b, not `je`;
- the loop is a `while (count > 0)` counted form, so `ebx`/`ebp` land in the
  retail roles instead of being swapped.

## Nesting depth

Only ONE level of grouping is needed. Two levels (an outer wrapper holding
three ints plus the inner group) also matches (`build/gen_F1.cpp`,
`build/gen_H3.cpp`), as does a two-level spelling with named types
(`build/gen_F6.cpp`). The single-level form in the landed source was chosen
because it invents one type name instead of two and reads closest to the
matched siblings' `BfmeCoordXX m_10` view of the same three dwords.

Rejected by the byte gate, for the record:

- explicit memberwise copy constructor / inline copy (the banked 0.85 attempt
  and its successors): 100-124 bytes, 88-89 non-relocation differences.
- `copyFrom` member instead of a copy ctor (`build/gen_I2.cpp`): 127 bytes —
  it makes the struct trivially copyable and the compiler drops the
  out-of-line call entirely.
- `char m_pad[3]` spelled explicitly after `m_20` (`build/gen_I2.cpp`):
  127 bytes; retail copies only the flag byte, so the padding must be
  implicit.
- inner group at +0x0C or +0x14 instead of +0x10: anchors the cursor at
  +0x18 or +0x1C respectively, 11-15 differences.

## Callee

One call target, 0x00887B60, the `StringBase<char>` copy ctor already matched
in `game/Libraries/Source/string/StringBase.cpp`. Pinned for this shim as
`??0BfmeTailBE@@QAE@ABU0@@Z`; the class carries an `alternatename` to
`??0?$StringBase@D@@QAE@ABV0@@Z`, the same mechanism `BfmeObjZHSetZH.cpp`
uses.

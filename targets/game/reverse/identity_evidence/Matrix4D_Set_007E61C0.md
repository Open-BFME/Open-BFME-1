# Matrix4D::Set axis-angle overload at 0x007E61C0

## Identity, native types, and extent

`targets/game/reverse/exports.csv` ordinal 1311 gives export RVA
`0x0000BE51`, body RVA `0x007E61C0`, and the exact decorated identity
`?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z`. This is independent of the old
source comment. The existing `matrix4d.h` declares this overload returning
`Matrix4D &`, with `const Coord3D &` and `float` arguments and sixteen float
members. Existing `coord3d.h` supplies x/y/z at offsets 0/4/8 through
Coord3DBase. No type, member, or header was invented or changed.

Retail ends with `ret 8` at offsets +0xF4..+0xF6; its complete extent is
247 bytes, [0x007E61C0, 0x007E62B7). Nine INT3 padding bytes precede the next
aligned body at 0x007E62C0. EAX retains the receiver and the two stack
arguments are callee-popped, consistent with the declared reference return
and thiscall ABI. `tools/callees.py 0x007E61C0 247` reports no call targets.

## Mathematical recovery and bounded compiler exception

Eight Rodrigues rotation coefficients and the early homogeneous zero stores
are C++ expressions over the native Coord3D fields. The final diagonal is
`z*z + cosine*(1-z*z)`; homogeneous entries 11 through 14 are zero and entry
15 is one. The expression ordering is the already byte-verified native
constructor's ordering, retained to reproduce VC7.1's x87 evaluation.

Only two inline assembly blocks remain: four instructions at retail offsets
[+0x05,+0x12), 13 bytes, compute sine/cosine with `fsincos` into the two locals;
14 instructions at [+0xC4,+0xF1), 45 bytes, compute the final diagonal and
interleave the five homogeneous stores with that x87 evaluation. This is
58/247 bytes of proven compiler machinery; the other 189 bytes are emitted
from C++ and its ordinary frame/return. There is no naked function or byte
emission. The second block intentionally preserves the retail register and
local-slot schedule; the full scoped byte gate verifies this contract.

The existing constructor attempt history at RVA 0x007E7A30, especially the
`t=52min model=space-bunny-free` entry in `re_attempts.log`, independently
records 20 sin/cos source shapes (zero fsincos among 74 emitted functions),
180+ source shapes, all 120 tail-store permutations, and compiler flags.
Separate sin/cos loses the retail instruction; volatile locals permit store
interleaving but lose earlier common-subexpression evaluation. The supplied
bank documents that unresolved tail. These established codegen failures are
why this recovery uses the narrow x87 exception allowed by AGENTS.md, rather
than another whole-body assembly lift.

The four actual DIR32 operands are at +0x20/+0x32/+0x7C/+0xCD. The first
three name `__real@3f800000`; the last names existing TU-local `_bfmeOne`.
Every object addend is zero and every retail operand is VA 0x01075334.
Direct object and retail reads verify all four referenced values are bytes
`00 00 80 3F` (1.0f). `_bfmeOne` has no pin; the existing retail-address
label `?g_bfmeDefaultBU@@3MA` is consistent under read-only pin_consistency.
No new callee pin or guessed datum identity was introduced.

## Verification and honest accounting

Scratch probe: 247/247 bytes, four relocations, EXACT modulo relocation slots.
Normal `./build.sh game/Libraries/Source/WWVegas/WWMath/matrix4d.cpp`:
23/23 matched, ten float constants verified, one recorded DIR32 address
verified, no unverified string references. Both distinct retail identities
Set at 0x007E61C0 and constructor at 0x007E7A30 remain present.

The constructor source was not edited. Its retained source SHA256 is
`def56eeb6c4da9539803e50fd9fb6da3c376b90d0ff59aa739f6c12e39a9ada6`.
The old naked Set bytes were identical to that constructor's retail bytes,
so removing Set's spray also removes a false dump classification of the
already recovered constructor. This is one substantive 247-byte Set
recovery; the constructor classification correction is zero additional
new conversion bytes. No fresh whole-image closure gain is claimed.

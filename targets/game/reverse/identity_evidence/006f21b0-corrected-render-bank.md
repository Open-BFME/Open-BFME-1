# Display slot D4: corrected behavioral bank

2026-09-27, GPT-6. No native conversion, callee pin, or ownership change.

## Extent and slot

W3DDisplay table VA `0111EDD0`, slot `D4`, selects ILT `0002743A` and body
`006F21B0`. The newly exact skinny-border caller `0079BCA0` independently
proves the Image pointer, four float coordinates, color, and mode arguments.
The method retains its address-derived name.

The 1285-byte ledger extent ends after `ret 1C` at offset `502`. Alignment
`8D 49 00` occupies `505..507`; six switch entries occupy `508..51F`, followed
by INT3. The complete extent including inline data is therefore **1312 bytes**.
The partial record uses this complete boundary; the unmatched dump row is
not edited. The table is data, despite probe's linear-decoder warning.

The destinations for indices 0 through 5 are RVAs `006F2211`, `006F21F5`,
`006F2239`, `006F2203`, `006F221F`, and `006F222D`. These set renderer mode
0, 3, unchanged, 1, 4, and 6 respectively. Both the old preferred source and
its later archives assigned the five stores to the wrong indices.

## Behavioral repairs

The previous source omitted the rotated-image clipping branch. Retail has
both branches from the original EA W3DDisplay counterpart: clip all four
screen edges, then compute the appropriate ordinary or rotated UV rectangle
from the original extents. Sequentially modifying UV endpoints, as the old
bank did, is also not the same calculation.

Retail reads UV at Image+`14..20`, and status at `30`. The old scoped Image
had no vptr but padded only `10` bytes, placing every field four bytes early.
The new bank corrects the padding. It uses the original RectClass header,
including its explicit float copy constructor and assignment; the compiler
uses a substantially different frame and x87 sequence with implicit copies.
It uses the canonical texture header and the proven Render2D::Add_Tri and
Add_Quad declarations (including unsigned-long colors), replacing the old
opaque triangle helper declaration without adding pins.

## Handle ABI remains unresolved

The complete helper `006F18F0` reads the Image in ECX and a result pointer on
the stack. On both branches it writes only one retained TextureClass pointer
through that result, returns the result pointer in EAX, and ends with plain
`ret` at `+172`. The caller releases exactly that owned pointer after setting
the renderer texture. There is no evidence for the old archive's two-word
return structure or a second texture output.

However, the ordinary MSVC member return declaration in this bank assumes
callee cleanup for its hidden result, so it omits retail's `add esp,4`.
This declaration is explicitly an experiment and must not be pinned as a
verified ABI. A cdecl member pushes the receiver; a fastcall member changes
the result argument placement; a free thiscall declaration is rejected by
VC7.1. None resolves the witnessed contract. No assembly adapter is used.

## Measured result

The corrected bank emits 1396 bytes, including its table, against 1312.
Its code is 1369 bytes versus retail's 1285. Using probe.shape_compare only
on instructions through each complete return gives 343 matching normalized
instructions out of max(349 retail, 350 native): **0.98**. This is the bank's
recorded score, explicitly a structural score, not concrete byte agreement.
The full-span probe reports 1157 differing bytes with 14 misaligned relocation
sites; this is not a near-exact byte result. Its remaining frame is `88`
versus `58`; the helper cleanup, saved-register scheduling, and texture-state
store shape also differ. Table destination identity was checked separately.

Restoring clipping first produced 1488 bytes and normalized .786. Restoring
the explicit rectangle copy operations produced 1396 bytes and .945 under
the old code-only extent comparison, before excluding decoded table data.
Canonical TextureClass and Vector2 use did not change shape. /Ob1 also made
no change. A local pointer spelling of the texture-state store produced1388
bytes with worse alignment. No volatile or aliasing-assumption flags remain.

The new preferred source is compiled evidence only. The original preferred
and all previous attempts remain in immutable attempt_history archives.
No nonmatching reconstruction is placed under game/.

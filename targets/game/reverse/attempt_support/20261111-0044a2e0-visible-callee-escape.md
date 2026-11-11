# 0x0044A2E0 `Rva00449790Owner::rva0044a2e0`: EXACT in addDirect's home unit

Result: EXACT, 757/757 bytes, 32 relocations, clean C++ with no volatile, asm or pragmas.
Best candidate: `build/wf/0044a2e0/best_Rva00443910OwnerDirect.cpp`. It is the current
`game/GameEngine/Source/GameClient/Rva00443910OwnerDirect.cpp` with the target appended
after `addDirect` and `#include "ascii_string.h"` added. The unit's own `// cl:` line is
unchanged (stlp_nodealloc/asciistringsetoutofline/zhcanonascii shims, `/Igame/Libraries/Source/WWVegas/WWLib`).
The incoming bank (`targets/game/reverse/attempts/0x0044a2e0.cpp`) reproduced as logged:
757 B, 6 non-reloc diffs at +0x9B..+0xA0. It needs three `volatile` views.

## Root cause of the long-standing capture swap (measured)

Retail order: `L_x(edx) L_client(ecx) L_y(eax) S_x(edx) L_vptr(edx) S_y(eax) call`.
The scheduler can lift the vtable load above the `mousePosition.y` store only when MSVC
treats `mousePosition` as not escaping. Synthetic TUs (build/wf/0044a2e0/syn/s3..s11)
show that any address-taken local blocks the lift. Field address, array, union, ctor
views, inline by-ref/by-value wrappers, member calls and receiver class kinds all block it.
The lift does happen when the callee taking `&mousePosition` (`addDirect`, 0x00443910) has
its body **compiled earlier in the same TU**. MSVC 7.1 then knows the pointer is only
read (it is not captured), so the stores behave as home stores and sink past the vptr
load. This is consistent with retail: 0x00443910 and 0x0044A2E0 come from the same InGameUI
unit. A dummy non-inlined `addDirect` body made 5 different capture spellings EXACT
(`v/d_k1`, `d_g1`, `d_g5`, `d_m00`, `d_b1`). The real home unit is EXACT as well.

## Second fix: separate x87 divisions without volatile

`Real zStep = 0.99f / (Real)count;` is folded into `0.99f * (1/count)` (fmul, 71 diffs).
`Real zStep = 0.99f * zRise / (Real)count;` (zRise = 1.0f) gives retail's
`fld [0.99]; fdiv st(1); fstp; fstp st(0)`. `(zRise - 0.01f) / (Real)count` also works.
The constant still folds to `__real@3f7d70a4` (VA 0x01083BFC). Measured effect only: the
fold seems to happen after the reciprocal-CSE pass.

## Hypotheses tested and ruled out (this session)

- Numerator: plain 0.99f/count (71), divisions before scale (741 B), `countReal` local (71),
  `(1.0f-0.01f)` (71), `zStep /= count` (71), `(Real)(0.99/(double)count)` (741 B), in-loop `zRise -= 0.99f/count` (744 B).
- Capture without a visible callee: k1-k8, g1-g6 (inline by-value/ref getters), h1-h4, all
  12 load/store permutations m00-m11, out-param helpers c1-c4, empty/converting ctor views:
  all scored 12-18. The vptr load stays after the last store.
- Flags: /Ow inert. /Oa changes the frame (367+). Neither is justified by a sibling.
- Moving the include below addDirect does not keep `$L5021` (the label renumbers anyway).

## Landing notes (read-only checks; nothing landed)

a) `ilt_oracle.py check '?rva0044a2e0@Rva00449790Owner@@QAEXXZ' 0x0044A2E0` returns CONTRADICTED
   (slot 55983). This is expected for the address-derived placeholder, and earlier
   partial rows used the same name. symbols.csv has no pin at ILT 0x00045570, only
   `?b_0044a2e0@@YAXXZ` (gen-thunk body) at 0x0044A2E0. The ILT row is
   `?j_00045570@@YAXXZ` (thunks_033.cpp). Keep the Rva name. A real name needs independent evidence.
b) Bodies in this object with their own ledger rows were probed against retail. All are EXACT:
   addDirect 0x00443910 (522), Rva0043BBC0 ctor 0x0043BBC0 (39), `??0AsciiString@@QAE@ABV0@@Z`
   0x0005EE50, `??1?$StringBase@D@@AAE@XZ` 0x0005E490, `??1AsciiString@@QAE@XZ` 0x0005EE90,
   `??9_List_iterator_base@_STL@@QBE_NABU01@@Z` 0x0007F900, `?length@Coord2D@@QBEMXZ`
   0x000FB9E0, `?validate@?$StringBase@D@@ABEXXZ` 0x0005D790. AsciiStringBL ctor/dtor COMDATs
   are byte-identical to BfmeSinkSubmitBL.cpp's, whose declarations were copied verbatim.
   **EH label:** addDirect's funclet `$L5021` becomes `$L6336`. The landing must run
   `tools/eh_state_pins.py --fix` for `?dup_00C22DF0@@YAXXZ` (object-symbol). The funclet
   bytes are unchanged (same 21-byte MATCHES-PAST-SIZE result as HEAD).
c) Globals (all recorded in data_rows.csv): `?TheMouse@@3PAVMouse@@A` 0x012F4C5C,
   `?TheAnim2DCollection@@3PAVAnim2DCollection@@A` 0x012F4CA8,
   `?TheWritableGlobalData@@3PAVGlobalData@@A` 0x012ED5C8, `?TheInGameUI@@3PAVInGameUI@@A`
   0x012F148C and `?TheGameClient@@3PAVGameClient@@A` 0x012F1464. Constants:
   `__real@3f000000` 0x0107533C and `__real@3f7d70a4` 0x01083BFC are recorded in dir32.
   `__real@3f800000` reads VA 0x01075334, which dir32 records under other names (an
   earlier scoped gate passed the float-constant check for the same literal).
   Callees resolve to ledger names: StringBase copy ctor, bfmeSubmitBL, findTemplate,
   getValue, addDirect, Random_Float, releaseBuffer, `__node_alloc::_M_deallocate` and __ftol2.
d) Home TU: `game/GameEngine/Source/GameClient/Rva00443910OwnerDirect.cpp`. This is required,
   because only there is addDirect's body visible. `class_gate.py` passes. `find_declared_unmatched`
   lists only the new member, which the landing row covers. Row: `add_match --replace-rva 0x0044A2E0`,
   replacing `?d_0044a2e0@@YAXXZ` (gen_asm d_003fa5b0.asm).

Suggested shape_levers entry: "a store sinks past a vptr load only if the local's
address does not escape; a visible, non-capturing callee body earlier in the TU removes
the escape". Source: this candidate.

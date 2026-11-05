# 0x00454760 ParseObjectDataChunk (605 B): EXACT with clean C++ (2026-11-05, claude-opus-5-5)

Best candidate: `build/wf/00454760/best.cpp` (same as `v/M3.cpp`).
`probe.py ... 0x00454760 --size 605` prints `result EXACT (modulo relocation slots)`.
Flags are unchanged: `// cl: /DNDEBUG /MD /EHsc`, the same as the 2026-10-16 clean bank.
The candidate has no volatile, barrier, asm or pragma.

## Root cause

All residue across every bank came from one shared cause: **`loc` was address-exposed**.

- the template-branch Vector3 argument copy: retail loads y into EDX ahead of the x store;
- the waypoint store `(*m_waypoints)[name] = loc` (Lx Ly Sx Lz Sy Sz);
- the 4-byte scratch rotation at +0x20F/+0x222 in the volatile bank.

The only escape of `&loc` is `m_techPositions.push_back(loc)`. VC7.1 decides aliasing per
function, not per path. A diagnostic `escapeIt(&loc)` placed after `delete` still
serialised both copies. A local whose address reaches only visible, non-capturing callees
stays unaliased. This is the lever in docs/shape_levers.md, "Callees must share the TU for a
by-reference local to stay unaliased". In this case:

- The fix was to define STLport `list<T>::insert`, `push_back` and `_M_create_node` in the TU,
  in the same shape as the matched `game/Libraries/Source/WWVegas/WWLib/RvaListInsertWidths.cpp`.
  `_Construct(T1*, const T2&)` (retail 0x000B73B0) was also defined there, with placement new.
- `push_back` still compiles as an out-of-line call, matching retail 0x00452280.
- If `_Construct` is only declared, the result goes back to 43 diffs (`v/M2.cpp`). The whole
  chain has to be visible.
- The only change from the 2026-10-16 clean bank (43 diffs) is the `_STL` namespace block.
- The volatile `Vector3(const Coord3D&, int)` and `assignWaypoint` helpers in the
  0.9934 stash are no longer needed. Drop them.

## Trials (all with probe.py, size 605 unless noted)

| change | result |
| --- | --- |
| base = stash 0x00454760.cpp (volatile) | 4 diffs (reproduces the bank) |
| clean43 (attempt_history 20299ef3) | 43 |
| loc as Vector3 with default constructor; implicit Coord3D typedefs and no reinterpret_casts (A2, C1, C2) | 43 |
| float ctor in the template branch only, or in both branches; `__forceinline` WWMath ctors (B1, B3, B4) | 56 / 97 (fld/fstp) |
| `Vector3(const float[3])` (B5); copy-ctor init list (L3) | 43 |
| implicit copy, or an out-of-line `~Vector3` (L1, L2) | 597 B, 247 diffs (loses saved-ESP) |
| push_back on a copy of loc / a by-value inline helper (E1-E3, F1) | 629 B (extra slot) |
| const-ref, pointer or member-call escape spellings (F2-F4, G3, G4, J1 array) | 43 |
| scalar reads plus aggregate-initialised const loc (H1, H2) | 629 / 621 B |
| /Oa (I1); /Ow (I2) | 436 / 43 |
| DIAG: push_back of a non-loc object (D1) | 602 B; every copy exact |
| DIAG: escape at the end or start (G1, G2) | serialised again (flow-insensitive) |
| push_back plus non-inline `_Construct` visible (M1, M3) | **EXACT** |
| the same, `_Construct` only declared (M2) | 43 |

## Landing notes (not done here; sandboxed)

- The TU now emits COMDATs for the following. The ledger matches both functions, at
  0x00452280 and 0x000B73B0, to other sources:
  - `?push_back@?$list@URva00452280Element@@...` (also defined in RvaListInsertWidths.cpp);
  - `??$_Construct@URva00452280Element@@U1@@_STL@@YAXPAU1@ABU1@@Z`.

  Run `find_declared_unmatched.py` and use `present-unmatched` markers or a shared
  header as the gate requires. Retail instantiated these in MapUtil's TU.
- Replace the naked `__emit` row in
  `game/GameEngine/Source/GameLogic/World/ParseObjectDataChunk_Thunk.cpp` with
  `add_match --replace-existing`. That file's header comment names its TU.

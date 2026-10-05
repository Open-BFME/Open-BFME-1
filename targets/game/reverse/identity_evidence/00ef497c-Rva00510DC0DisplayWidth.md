# Scalar identity at VA 0x012F497C

Corrected: `?Rva00510DC0DisplayWidth@@3HA` owns the 4-byte `int` scalar at VA 0x012F497C (RVA 0x00EF497C).

Retail section: `.data`. Initial bytes: `00 00 00 00`. Initial value: `0`.

## Retail facts and contract

The tooltip setup at 0x00910DC0 passes this address and the adjacent height address to display-string vtable slot 0x3C, then uses this signed integer for horizontal tooltip extent with font-height padding. The tooltip positioning reader at 0x00910D10 converts it with fild and scales it by 0.5. The paired output and horizontal calculation establish width. Retail W3DDisplayString vtable VA 0x0111FEA8 slot 0x3C contains VA 0x004401A6 (E9 05 48 6B 00), which jumps to the matched getSize body at VA 0x00AF49B0. That member receives the display-string object in ECX, reads its width at +0x1F0, and writes it at VA 0x00AF49BE through the first pointer argument. The tooltip call supplies VA 0x012F497C as that first argument and the adjacent height address as the second. The reference getSize assigns m_size.x to width and m_size.y to height.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00910D67 | 0x00910D10 | read | `fild dword ptr [0x12f497c]` |
| 0x00910E8F | 0x00910DC0 | address supplied | `push 0x12f497c` |
| 0x00910EAD | 0x00910DC0 | read | `mov eax, dword ptr [0x12f497c]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?Rva00510DC0DisplayWidth@@3HA` | 1 (`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptGuiFX.cpp`) |
| `?g_bfmeCx1264@@3HA` | 1 (`game/GameEngine/Source/Common/BfmeConv1264.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptGuiFX.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The first output of display-string slot 0x3C must correspond to width in the reference getSize(Int *width, Int *height) contract, and the tooltip calculation must use this output horizontally. Reversed outputs or another extent address would refute the width name.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F497C.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F497C.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F497C.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
`build/rlink/scalars-1791167601/display-size-slot.log` contains the actual W3DDisplayString vtable slot and its E9 route, followed by the complete output writer. `build/rlink/scalars-1791167601/display-size-reference.log` records the reference width/height assignment; `build/rlink/scalars-1791167601/display-size-identities.log` records the existing identity and vtable spellings.

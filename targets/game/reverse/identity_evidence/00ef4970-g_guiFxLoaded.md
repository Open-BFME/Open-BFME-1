# Scalar identity at VA 0x012F4970

Corrected: `?g_guiFxLoaded@@3EA` owns the 1-byte `unsigned char` scalar at VA 0x012F4970 (RVA 0x00EF4970).

Retail section: `.data`. Initial bytes: `00`. Initial value: `0`.

## Retail facts and contract

The GuiFX loader/register routine at 0x00910FA0 clears this byte and binds AptGuiFX::OnInitialized. Its bound function pointer VA 0x004279DF is a five-byte E9 thunk to 0x00910DB0, whose entire body sets this byte to one. This proves the loaded-state role and byte store contract.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00910DB0 | 0x00910DB0 | write | `mov byte ptr [0x12f4970], 1` |
| 0x00910FDA | 0x00910FA0 | write | `mov byte ptr [0x12f4970], bl` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?g_Va012F4970@@3EA` | 1 (`game/GameEngine/Source/Common/SmallLeafBodies.cpp`) |
| `?g_guiFxLoaded@@3EA` | 1 (`game/GameEngine/Source/GameClient/GUI/AptGuiFXRegisterCallbacks.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngine/Source/GameClient/GUI/AptGuiFXRegisterCallbacks.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
The callback pointer at VA 0x0091104E must contain VA 0x004279DF, whose E9 displacement must land on the one-byte setter at VA 0x00910DB0. A different pointer, target, or stored address would refute the loaded-state name.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012F4970.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012F4970.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012F4970.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.
`build/rlink/scalars-1791167601/gui-callback-chain.log` verifies the bound callback pointer separately. `build/rlink/scalars-1791167601/add-data-012F4970-recheck.log` records the sizeof and initializer gate after correcting the include search path. `build/rlink/scalars-1791167601/build-rechecks.log` proves the function bytes after that mechanical correction.

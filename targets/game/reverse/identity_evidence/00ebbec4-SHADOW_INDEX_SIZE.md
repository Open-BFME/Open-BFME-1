# Scalar identity at VA 0x012BBEC4

Corrected: `?SHADOW_INDEX_SIZE@@3HA` owns the 4-byte `int` scalar at VA 0x012BBEC4 (RVA 0x00EBBEC4).

Retail section: `.data`. Initial bytes: `00 20 00 00`. Initial value: `8192`.

## Retail facts and contract

ZH W3DVolumetricShadow.cpp:121 defines int SHADOW_INDEX_SIZE=8192. Retail signed capacity comparisons in volume rendering and the resource constructor doubling it for WORD indices agree with the reference index-capacity uses.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00BB983D | 0x00BB9810 | read | `mov ecx, dword ptr [0x12bbec4]` |
| 0x00BBC3BE | 0x00BBC270 | read | `cmp ecx, dword ptr [0x12bbec4]` |
| 0x00BBC43D | 0x00BBC270 | read | `mov ecx, dword ptr [0x12bbec4]` |
| 0x00BBC4F8 | 0x00BBC270 | read | `mov edx, dword ptr [0x12bbec4]` |
| 0x00BBCC3C | 0x00BBC8B0 | read | `mov edx, dword ptr [0x12bbec4]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?BfmeShadowIndexCount@@3IA` | 1 (`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowHelperManagerReAcquireResources.cpp`) |
| `?SHADOW_INDEX_SIZE@@3HA` | 3 (`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp`, `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`, `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
A resource allocation that uses this value as a vertex count, or a rendering comparison against a vertex count, would refute the index-capacity name. Its reference definition and initial value must both remain int 8192.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012BBEC4.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012BBEC4.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012BBEC4.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.

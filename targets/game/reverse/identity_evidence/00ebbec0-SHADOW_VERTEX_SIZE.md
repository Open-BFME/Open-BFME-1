# Scalar identity at VA 0x012BBEC0

Corrected: `?SHADOW_VERTEX_SIZE@@3HA` owns the 4-byte `int` scalar at VA 0x012BBEC0 (RVA 0x00EBBEC0).

Retail section: `.data`. Initial bytes: `00 10 00 00`. Initial value: `4096`.

## Retail facts and contract

ZH W3DVolumetricShadow.cpp:120 defines int SHADOW_VERTEX_SIZE=4096. Retail signed capacity comparisons in volume rendering and the resource constructor multiplying it by 12 agree with the reference vertex-capacity uses.

This is free scalar storage with no receiver. The read, write, and output-address sites below describe its argument contract independently of a decompiler. Each instruction comes from retail bytes. Body addresses use the repository ledger extent when available and Ghidra boundary evidence otherwise.

| Instruction VA | Body VA | Access | Retail instruction |
|---|---|---|---|
| 0x00BB9870 | 0x00BB9810 | read | `mov eax, dword ptr [0x12bbec0]` |
| 0x00BBC312 | 0x00BBC270 | read | `mov eax, dword ptr [0x12bbec0]` |
| 0x00BBC38E | 0x00BBC270 | read | `mov ecx, dword ptr [0x12bbec0]` |
| 0x00BBCB7D | 0x00BBC8B0 | read | `mov eax, dword ptr [0x12bbec0]` |

The narrow scan of `data_rows.csv` finds no range overlapping this extent. The DIR32 scan finds no named start strictly inside it. All competing names begin at the same address; the raw probe records both tests. These candidate scalar ranges have no pointer initializer.

## Competing declarations

| DIR32 spelling | Game files declaring this spelling |
|---|---|
| `?BfmeShadowVertexCount@@3IA` | 1 (`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowHelperManagerReAcquireResources.cpp`) |
| `?SHADOW_VERTEX_SIZE@@3HA` | 3 (`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp`, `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`, `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp`) |

Counts are scoped to typed declarations and definitions, including headers. Similar words in comments or expressions do not count.

## Correction and refutation

The defining translation unit is `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`. The sanctioned `tools/add_data_match.py` measurement records its compiled symbol size and verifies its initializer against retail before adding a data row. All existing pins and competing DIR32 rows remain additive evidence; no pin is deleted or rewritten.
A resource allocation that uses this value as an index count, or a rendering comparison against an index count, would refute the vertex-capacity name. Its reference definition and initial value must both remain int 4096.

## Raw local evidence

`build/rlink/scalars-1791167601/retail-012BBEC0.log` contains byte values, section, overlap checks, pins, and disassembly at every direct occurrence of this VA. `build/rlink/scalars-1791167601/declarations-012BBEC0.log` contains the unedited game search output. `build/rlink/scalars-1791167601/context-012BBEC0.log` records EA string bytes and their instruction addresses. Full bodies are in `build/rlink/scalars-1791167601/body-*.log` and `build/rlink/scalars-1791167601/ledger-body-*.log`; the exact ledger identities and extents are in `build/rlink/scalars-1791167601/supplement.log`. `build/rlink/scalars-1791167601/ilt-chains.log` retains each measured five-byte E9 chain. Reference searches are `build/rlink/scalars-1791167601/reference-search.log` and `build/rlink/scalars-1791167601/reference-types-exact.log`. Gate results and LINKED measurements are indexed in `build/worker-final.md`.

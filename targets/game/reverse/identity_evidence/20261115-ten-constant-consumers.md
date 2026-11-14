# Ten further existing-data-provider consumer repairs

Baseline: faa6230837; BFME 1 retail 1.03 unpacked. This is a batch of ten
scoped consumer-unit repairs, not ten newly reconstructed functions.

## Measurement requested by the owner

The latest completed Daily link census is
[run 43590726489](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43590726489)
at input 1a248a7b476727c19e37a16744c71686fa8f3f5e, before faa6230837.
No completed or running post-faa6230837 census was listed at the session's
initial check. The previous batch's additional 515 bytes therefore remain
a local frozen-index prediction, unconfirmed by a new census.

| Task | Source and scope | Retained row RVAs | Bytes | Existing owner(s) |
|---|---|---|---:|---|
| 1 | Amount normalization: 1.0f: `game/GameEngine/Source/GameLogic/Rva002D7890.cpp` | `0x002D7890` | 59 | `g_bfmeDefaultBU` |
| 2 | F1240 numeric conversion: 1.0f: `game/GameEngine/Source/Common/BfmeConv1240.cpp` | `0x008C9F70` | 178 | `g_bfmeDefaultBU` |
| 3 | State comparison: 1.0f: `game/GameEngine/Source/Common/BfmeConv1969.cpp` | `0x002C51B0` | 105 | `g_bfmeDefaultBU` |
| 4 | Build-cost multiplier: 1.0f: `game/GameEngine/Source/Common/Thing/ThingTemplate_calcCostToBuild.cpp` | `0x0013E390` | 131 | `g_bfmeDefaultBU` |
| 5 | Terrain initialization flag: `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualRva00730590Init.cpp` | `0x00730590` | 684 | `g_aiTargetDispatchSuppressed` |
| 6 | Filter pre-render bool declaration: `game/GameEngine/Source/Common/Rva007D85C0FilterPreRender.cpp` | `0x007D74D0` | 190 | `g_bfmeDirtyCU` |
| 7 | Ground-path smoothing: 0.5f: `game/GameEngine/Source/GameLogic/AI/PathfinderBuildGroundPath.cpp` | `0x003E6B80`, `0x003E6AF0` | 733 | `g_rva0107533C` |
| 8 | Filter post-render half-texel: 0.5f: `game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007D85C0PostRender.cpp` | `0x007D7910` | 1,777 | `g_rva0107533C` |
| 9 | Snow-renderer C/C++ data linkage: `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnowManagerExtraAfterFmod.cpp` | `0x00725620` | 189 | `g_bfmeDefaultBU` |
| 10 | AI scatter zero test: `game/GameEngine/Source/GameLogic/AI/AIGroupScatter.cpp` | `0x00155490` | 525 | `g_rva01075350` |

## Target proof and verification

The eleven retained function rows cover 4,571 complete bytes. All
code bytes are preserved; only 18 global-reference fields change
their object symbol to the existing owner's. Each field's actual retail
DIR32 operand was decoded within its own complete body and equals the
owner's recorded VA. Equal numeric values alone were not used to bind
separate cells. The existing data records prove the sizes and initial
values of the 1.0f, 0.5f and zero constants and the two bool flags.

The filter pre-render unit previously declared the shared bool as unsigned
char, producing a different decorated global name. Its read and zero-store
compile identically with the provider's bool type. The snow unit previously
requested the C name _g_bfmeDefaultBU; the existing definition is the C++
name ?g_bfmeDefaultBU@@3MA. Correcting the declaration retains every load.

The whole-object comparison preserves the ordered non-debug sections'
bytes, sizes, characteristics and relocation graph. Compiler-local names
are compared by section number and offset, while defined external symbols
retain their section, value and type. This includes four .xdata sections.
Undefined external sets change only by the intended data-owner bindings.

The combined native gate passes 22/22 functions across fifteen sources:
eleven consumer rows and eleven provider rows. It also verifies seven
data rows, ten compiler-float references and ninety DIR32 references.
The declared-unmatched checks find no open function body. No header,
compiler flag, data row, pin, alias, private class identity or assembly
instruction is added by this batch.

Three initial source candidates only contained unused declarations and
were excluded before editing. The earlier post-render false reject was
about admitting a separate HighlightRendering bool; this batch leaves
that storage, declaration, initializer and all its references unchanged.
Only the independent, already owned half constant is repaired there.

## Reference review

The BFME 2 reference remains f6c3838e7b, checked on 2026-11-13 and within
the required 72-hour window. Its single-owner data-reference pattern and
typed-global repair mechanism were reviewed in the preceding batch and
reused while those inputs remain unchanged. In particular, its
`Code/Libraries/Source/partitionmanager/PartitionManagerImpl.cpp` has a
TU-static 1.0f spelling g_bfmeDefaultBU; that private definition/linkage
is not copied into BFME 1. The reviewed
`Code/GameEngineDevice/Source/W3DDevice/GameClient/ScreenHilightFilterPreRender.cpp`
uses the shared g_bfmeDirtyCU bool for read/clear operations at its own
different address. BFME 1's providers, field addresses, values, class
identities and call contracts are established from its own evidence.

## Linking boundary

Original sources were measured before any edits against the frozen census
index at 1a248a7b47 (2026-11-14 12:41 UTC). For these final ten selected
units, 0/10 link and the preview totals 0 bytes.
The initial baseline log also contains excluded candidates; only the
selected sources are counted. Replacement units have a separate original
baseline log. The repaired-object frozen-index preview also reports 0/10 units, 0 -> 0
bytes: other independent globals, helpers and selected COMDAT copies still
block each unit. The staged current-provider preview is UNKNOWN for all ten
sources after its 120-second deadline. No additional linked-unit or linked-byte
gain is claimed by this batch.

These are bounded linker predictions, not a new census, full-image link,
runtime, FPS, memory, leak or crash-fix result.

Private before objects, candidates, per-field retail-address proofs and
section-graph comparisons are retained under `build/codex-20261114-ten-next/`
and `W:/OpenBFME/diagnostics/continue-20261114-ten-next/`.

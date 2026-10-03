# Mouse tooltip parser: contradicted shared field layout

Severity: **WRONG**, pending coordinated layout repair.

Existing claims: INI::parseMouseDefinition, RVA `0x005A4690` / 25B, and
INI::parseMouseCursorDefinition, RVA `0x005A5FA0` / 185B, both in
`game/GameEngine/Source/GameClient/Input/Mouse.cpp`.

`docs/matching.md`, Relocations: “The build fills relocation slots, so those
bytes need not match, but it checks what they point at.” The current function
checks do not compare all referenced FieldParse initializers. A matching
pointer operand does not validate the offsets inside its table.

The Mouse parser's +0x0E operand independently anchors VA `0x0110D140`.
The cursor parser's +0x8B operand anchors VA `0x0110D070`, thirteen 16B
cursor records earlier. Retail contains 13 cursor keys followed immediately
by 21 Mouse keys and a 16B zero terminator at `0x0110D290`: 560B overall.
Ghidra MCP and the unpacked retail PE agree on all560B. The cursor-specific
first13 key/offset records agree; all21 subsequent Mouse offsets differ.
This is one shared-layout finding exposed through two parser windows.

All bounded key strings include their NUL terminators and match the compiled
object. All userdata words are zero. Callback addresses agree with current
resolver candidates; this is consistency, not a new callback identity proof.
The exact source offsets versus retail are:

| Key | Compiled offset | Retail offset |
|---|---:|---:|
| TooltipFontName | `0xd28` | `0x1070` |
| TooltipFontSize | `0xd2c` | `0x1074` |
| TooltipFontIsBold | `0xd30` | `0x1078` |
| TooltipAnimateBackground | `0xd31` | `0x1079` |
| TooltipFillTime | `0xd34` | `0x107c` |
| TooltipDelayTime | `0xd38` | `0x1080` |
| TooltipTextColor | `0xd44` | `0x1090` |
| TooltipHighlightColor | `0xd54` | `0x10a0` |
| TooltipShadowColor | `0xd64` | `0x10b0` |
| TooltipBackgroundColor | `0xd74` | `0x10c0` |
| TooltipBorderColor | `0xd84` | `0x10d0` |
| TooltipWidth | `0xd3c` | `0x1084` |
| CursorMode | `0xd94` | `0x10e0` |
| UseTooltipAltTextColor | `0xd98` | `0x10e4` |
| UseTooltipAltBackColor | `0xd99` | `0x10e5` |
| AdjustTooltipAltColor | `0xd9a` | `0x10e6` |
| OrthoCamera | `0xd9b` | `0x10e7` |
| OrthoZoom | `0xd9c` | `0x10e8` |
| DragTolerance | `0xda0` | `0x10ec` |
| DragTolerance3D | `0xda4` | `0x10f0` |
| DragToleranceMS | `0xda8` | `0x10f4` |

The current source has neither an explicit terminal record after the cursor
array nor one after the Mouse array. The source/object cursor window flows
into the Mouse records, but the generic scanner cannot prove an emitted
terminal record after the last Mouse entry. The offset contradictions above
do not depend on treating surrounding padding as a source terminator.

`callees.py` identifies both real initFromINI calls as RVA8520A0. Its table
lookup850880, independently decoded in the GameLOD audit, scans16B records
to a null key; these functions pass no independent table count. The Mouse
parser ends in RET at5A46A8 followed byCC5A46A9; the cursor parser ends in
RET at5A6058 followed byCC5A6059. Exact extents remain25B/185B.

Fresh origin/master has identical Mouse.cpp bytes and the same rows. A
bounded12-second pickaxe was attempted without asserting a historical
introduction commit. The fresh exact-input audit verifies all22 existing
claims in this TU plus current strings/constants/DIR32 references; its
initialized-data checker still reports57passes/21diagnostics/51unverified.
Those aggregate diagnostics are not21 additional independent findings.

Repair must reconcile the shared Mouse layout, construction/lifetimes and
all dependent code, including the canonical header/full gate when needed.
The existing mouselayout header already has a partially adapted cursor count
and padding before redraw mode; simply switching to it does not establish
the intervening tooltip field offsets. Do not insert isolated numeric offset
substitutions or infer new C++ member names from serialized keys. No source,
ledger, header, pin, baseline or claimed-byte change is made here.

Raw bounded evidence: `build/audit_v3/s6_mouse_proof.json`,
`s6_mouse_ghidra.json`, `s6_mouse_verify.py`; fresh input proof and complete
source audit: `s6_medium_t/compile_inputs.json`, `s6_medium_t/05.log`.

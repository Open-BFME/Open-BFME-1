# W3D render cluster: DX8Wrapper state

## Finding

Families 1 and 7 are callers of the WW3D DX8 state layer, not a second
implementation of `DX8Wrapper`.  `dump_families.py --show 1` found 47 bodies
(117,182 bytes), and `--show 7` found 26 bodies (96,271 bytes).  The overlap
is explained by the same device/state references and by the shared calls to
`DX8Wrapper::Apply_Render_State_Changes` (`0x00904890`), the WWLib
`StringClass` helpers (`0x009DB890` and `0x009DB7A0`), and the scorch-stage
state.  The callers are spread across the W3D device code: terrain and water
near `0x006Dxxxx`/`0x0090xxxx`, shader and screen effects near
`0x0071xxxx`, snow and shadows near `0x0072xxxx`/`0x007Bxxxx`, and texture
resource code near `0x0090xxxx`.

The smallest context packs identify the same cluster without assuming a
class name from adjacency.  In particular, `0x0090C840` is a vtable-slot
candidate but `vtable_lookup.py` does not prove its original method name;
`0x007171F0` has the shader-manager callers and the render-target/Clear
sequence; `0x006D4690` is the terrain texture helper; and `0x00905140` is the
water resource path.  `callees.py` confirms the expected DX8 ILTs, `__ftol2`,
`Find_POT`, `TextureClass::Release_Ref`, and `VertexMaterial::Get_Preset`.

## Shared include

The shared include is [DX8State.h](../inputs/reference/shims/dx8state/DX8State.h).
It adopts the canonical WW3D/WWLib declarations from
`game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h` and does not redeclare
`DX8Wrapper`, `StringClass`, `ShaderClass`, `VertexMaterial`, or their
methods.  The temporary access widening is limited to that include so a W3D
caller can name the existing protected state fields.  The StringClass call
sites therefore retain the normal MSVC 7.1 `__thiscall` ABI:

```text
?Get_String@StringClass@@AAEXH_N@Z  0x009DB890
??1Mem009DB7A0@@QAE@XZ             0x009DB7A0
```

The canonical `dx8wrapper.h` owns the DX8Wrapper static declarations and
`number_of_DX8_calls`; the shim repeats only the scalar BFME-side references
needed by the family callers as an ABI checklist.  It deliberately does not
invent a second six-argument/seven-argument `Clear` declaration.  The BFME
seven-argument body at `0x00904250` is already a separate, matched ledger
entry and must be reached through its existing symbol.

## Shared globals

These are the five globals shared by the two family reports.  "Proven" means
the name/type is present in the canonical source or an existing consistent
pin; "hypothesis" means the address is shared but its owner still needs a
caller/layout witness.

| retail data | name and type | status |
| --- | --- | --- |
| `0x01340534` | `DX8Wrapper::D3DDevice`, `IDirect3DDevice8 *` | Proven by `dx8wrapper.cpp/.h`, the canonical pin, and 15 DIR32 references. |
| `0x01340594` | `number_of_DX8_calls`, global `unsigned` | Proven by the canonical declaration/definition and the retail increment sites (203 callers, including `Get_Free_Texture_RAM`). |
| `0x01340568` | `BaseHeightMapScorchStageChanges`, `unsigned` | Proven by `BaseHeightMap.cpp`, the scorch-stage pin, and the matching increment/use pattern. |
| `0x0134ECC8` in the family dump | `g_bfmeCh1035`, single `TCHAR`/character storage | Proven: the retail operands use the VA `0x0134ECC8`; the symbols ledger stores its RVA `0x00F4ECC8` (`0x0134ECC8 - 0x00400000`). No pin change is required. |
| `0x012D9124` | `Rva012D9124`, type not yet established | Shared by both families, but no name-oracle witness or unique owner is available. Keep it opaque. |

The surrounding DX8Wrapper cache layout is also visible in the canonical
definition order:

```text
0x0134054C  DX8Wrapper::matrix_changes
0x0134055C  DX8Wrapper::light_changes          (order-based hypothesis)
0x01340560  DX8Wrapper::texture_changes
0x01340564  DX8Wrapper::render_state_changes   (order-based hypothesis)
0x01340568  DX8Wrapper::texture_stage_state_changes
0x01340578  DX8Wrapper::CurrentCaps
0x01340594  DX8Wrapper::number_of_DX8_calls
0x0133F49C  DX8Wrapper::render_state_changed
```

The `matrix_changes`/`texture_changes`/stage counters have direct retail or
landed-row evidence.  `light_changes` and `render_state_changes` are
definition-order hypotheses until an independent setter or witness is
found.  `name_oracle.py --class DX8Wrapper` currently has no layout witness,
so an anonymous data reference must not be promoted to a plausible member
name merely because it is adjacent to a known static.

## Zero Hour family map

The reference tree provides the useful source shapes and ownership, not a
permission to copy its addresses blindly:

| BFME family | Zero Hour twin |
| --- | --- |
| texture apply/resource bodies, including the `0x0090C840` shape | `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.cpp` (`TextureClass::Apply` and resource paths) |
| terrain texture and alpha-terrain paths around `0x006D4690` | `.../game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTex.cpp` |
| screen filter/render-to-texture path around `0x007171F0` | `.../game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp` |
| snow resource/render path around `0x00725710` | `.../game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp` |
| water resource and track paths around `0x00905140`/`0x0071BBC0` | `.../game/GameEngineDevice/Source/W3DDevice/Water/W3DWater.cpp` and `W3DWaterTracks.cpp` |
| volumetric-shadow path around `0x007B93E0` | `.../game/GameEngineDevice/Source/W3DDevice/Shadow/W3DVolumetricShadow.cpp` |
| device state implementation | `.../game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h` and `dx8wrapper.cpp` |

The ZH files establish the family mapping and declaration order.  They do
not prove a BFME identity where the BFME caller, vtable slot, unique literal,
or symbol evidence is absent.  For example, the `0x006D4690` terrain helper
has a nearby ILT and a `Rva006D4690Apply` candidate, but its original body
identity remains unresolved and must stay opaque until the caller evidence is
settled.

## Recipe for the mid lane

1. Run `tools/callees.py <rva> <size>` and read every target before writing
   the body; use the ZH file only for control-flow/layout hypotheses.
2. Include `../../../../../inputs/reference/shims/dx8state/DX8State.h` first from a
   `GameClient` TU, then the normal W3D/WW3D headers; never add TU-local
   `DX8Wrapper`, `StringClass`, shader, or material declarations.
3. Use the focused MSVC-compatible flags
   `/DNDEBUG /MD /EHsc` plus the repository include roots for
   `inputs/reference/shims`, `game/Libraries/{Include,Source}`, `WWVegas/WWLib`,
   `WWVegas/WW3D2`, `WWVegas/WWMath`, `WWVegas/WWDebug`, `WWSaveLoad`,
   `WWAudio`, `game/GameEngine/{Include,Source,Source/Common}`, and
   `game/GameEngineDevice/{Include,Source}`.
4. Add `_STLP_NO_EXCEPTIONS` for STLport/WWLib-heavy bodies whose retail
   frame has no C++ EH state; use `throw()` on the local StringClass/resource
   RAII declarations where that removes the unwanted unwind states.  Keep
   `/EHsc` for ordinary W3D callers and do not add a broad exception switch
   to hide a mismatch.
5. Prove any new symbol with `tools/pin_consistency.py --symbol` first, run
   the focused `add_match.py`/relocation check, then run
   `tools/pin_consistency.py --check`; use an address-derived opaque name
   (`RvaXXXXXXXX::method` or `?dup_XXXXXXXX`) when identity is not proven.

The remaining blocker for the large members is not the shared call list: it
is the unproven BFME-side owner/layout of the anonymous device-state globals
(`0x012D9124`, `0x012F7FE0`, `0x01075C74`, `0x01340EC4`).  The apparent
`0x0134ECC8` versus `0x00F4ECC8` discrepancy is only the VA/RVA notation
difference described above.  Until the remaining ABI is witnessed, larger
bodies can compile against the shim but still produce a plausible,
byte-wrong state access or an invented identity.

## Session W3D handoff (2026-09-16)

The focused family-1-through-12 sweep contains 61 unique dump bodies. Running
`tools/callees.py` over every member found zero unnamed direct callees for 59
members. Those 59 are listed in `targets/game/reverse/unlocked.txt` with the `w3d-render`
tag so the anonymous lane can serve them immediately. The two exceptions are
`0x00907960` and `0x0090AB60`; each still has one unnamed direct callee and
remains gated until that target is independently identified.

The strongest banked body is `0x007171F0` (`445/445` bytes, score `0.991`).
Its W3DShaderManager static thunk, render-target path, shader/material calls,
and clear sequence establish the source identity. The clean C++ body is not
byte-exact: only four non-relocation register selections remain in the filter-4
clear path (`+0x11C`, `+0x122`, `+0x128`, `+0x132`), with retail using EDX for
the water-data pointer and ECX for the temporary vector address. Pointer/local,
direct-field, helper, Release_Ref, barrier, and flag-shape probes did not move
that allocation. The body remains banked for a future TU/register-liveness
lever; it is not a landed match.

The repeatable swarm recipe is therefore: include `DX8State.h` first, use the
canonical `dx8wrapper.h` declarations and the eight address-backed DX8 static
members listed above, run the callee sweep before writing, and keep any
BFME-side state owner address-derived until a caller, slot, or layout witness
proves its identity. Do not promote `0x012F7FE0`, `0x012D9124`, `0x01075C74`,
or `0x01340EC4` to semantic names from adjacency alone. The focused compiler
flags and `_STLP_NO_EXCEPTIONS`/local `throw()` rule in the recipe above are
the known frame-stable defaults.

`0x006D4690` was also compiled against the receiver-class candidates. The
retail body is a 326-byte indirect-device state helper with no direct callees;
the candidate named `bfmeTwoBKE` reached `314/326` with a branch/layout drift,
and the existing callers do not prove that semantic name. It remains an
opaque, re-servable candidate rather than a new pin or a guessed identity.

# Address-derived singleton pointer provider

## Physical identity and native-header limits

This defines exactly one external `void *` cell, `g_Rva00F36E5C`, at retail VA `0x01336E5C` (RVA `0x00F36E5C`). The zero-initialized PE virtual `.data` span holds four zeros. A pointer cell is independently proven by matched `Debug::PreStaticInit` at RVA `0x00889500`: VA `0x00C8951B` loads this cell, `0x00C89554` stores the constructed-object pointer, and `0x00C89562` reloads it for return. That body allocates `0x9F5C` bytes and increments the object field at `+0x9C7C`. This is neither an import cell nor an index-buffer-specific datum.

The existing `g_BFMEIndexBufferDebug` identifier overstates an index-buffer-specific identity: the same cell is used by generic heap-abort and singleton initialization bodies. Seven incompatible candidate pointer mangles occur in DIR32 records: `BFMEDebugClass008FC660`, `BFMEDebugClass008FC710`, `BFMEDebugClass008FCF40`, `BFMEIndexBufferDebugClass`, `BfmeLogIBD`, `Rva00904BE0Debug`, and `TruckBoneDebugManager`. They are local ABI views of one observed cell, not seven independently proven objects. No candidate class type is defined or asserted as the actual singleton owner by this repair.

Native Zero Hour `Libraries/Source/debug/debug_debug.h:783` declares `static Debug Instance`, a by-value singleton; its `debug_debug.cpp:62` defines that object. BFME retail instead stores a dynamically constructed pointer in the selected four-byte cell. Native adoption of that by-value definition would change the physical type/extent. This provider therefore uses the built-in opaque pointer type, without redeclaring any native class or editing a shared header. Existing caller-local `BfmeLogIBD`/`BfmeMsgIBD` virtual ABI views remain unchanged; the new explicit casts make the limited view visible at actual uses. There is no global alias definition or new pin.

## Independently inspected callers

| RVA | Extent | Global DIR32 offsets |
|---|---:|---|
| `0x6d53a0` | 750 | `+0x2E`, `+0x3C`, `+0x83`, `+0x91`, `+0xFD`, `+0x10B`, `+0x2A9`, `+0x2B7` |
| `0x6d5750` | 766 | `+0x16B`, `+0x179`, `+0x1BE`, `+0x1CC`, `+0x251`, `+0x25F`, `+0x2B0`, `+0x2BE` |
| `0x6d5b10` | 864 | `+0x2D`, `+0x3B`, `+0x82`, `+0x90`, `+0xF8`, `+0x106`, `+0x31C`, `+0x32A` |

Every one of these24original retail operand fields equals VA `0x01336E5C`. The existing views dispatch via vtable offsets0x60 and0x6C; the returned message view dispatches via0x38,0x00,0x4C. All method public names, signatures, types, and byte extents remain unchanged. `callees.py` was run at each actual extent before source edits. Scoped strict verification retains all original direct-call operands and12string references.

All six TUs declaring `BfmeLogIBD *g_BFMEIndexBufferDebug` were checked: these three queue files, `AlphaEdgeTextureClassUpdate.cpp`, `W3DFloorBuffer_init.cpp`, and `Rva006C07D0IndexBufferDebugGuard.cpp`. None defines that candidate global. The remaining three caller views keep their existing unresolved candidate until separately repaired; this commit makes no claim that the whole alias cluster is closed.

## Verification and controls

- Official `add_data_match.py --model gpt-6`: sizeof4 and zero-filled4B retail equality pass. Its data row owns the new mangled name `?g_Rva00F36E5C@@3PAXA`; no address alias pin is added.
- Scoped `build.sh` over all four source files passes function3/3 at750/766/864B, data1/1,12string references,24DIR32 operands.
- Fresh objects from that official build are sliced to the three actual caller COMDATs and linked with the real provider object into a strict DLL, without `/FORCE`. All24linked load operands address the map-selected provider cell; that cell contains four zeros. All three linked caller bodies match retail outside original relocation fields.
- Missing-provider negative excludes only the new cell from labeled stubs: LNK2019 in each of the three callers, LNK1120, exit96.
- Old-source negative includes the real new provider but leaves the obsolete `BfmeLogIBD` global candidate undefined: LNK2019 on that old candidate in all three callers and LNK1120, exit96. This confirms the repair does not create a false compatibility alias.
- Positive DLL stubs unrelated function/literal dependencies, including D3DX functions, with explicitly recorded names. This is actual selected-data binding proof, not native import proof or runtime closure. All original callee matching is separately covered by the scoped byte gate.

The old queue projection is2380authored caller bytes in historical census `bb1f0edd39`. The current source metric independently remains2380B. This repair adds4verified data bytes and0authored function bytes. No fresh census/whole-image closure gain is asserted. Scratch receipts reside in `build/debug_pointer`: `before_operands.json`, `prestaticinit.txt`, `current_controls.json`, `old_negative.json`, linked maps/DLLs, and original/candidate objects.

## Exact source snapshots

| Path | Before SHA256 | After SHA256 |
|---|---|---|
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006D53A0Update.cpp` | `ddc42c02dff2b4a31f302f06434bdf32d51df84783554f0c84d1e76254263ebc` | `cbea99790d190fc625176376a614917d872b8ff191b8db0c3da05d0e713dd8e7` |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006D5750Update.cpp` | `005b19a2962197d002c6f465d8c7a565722126bbe365eb7e41c32de1aaa528b9` | `2dbaf3c94fbf0427c32637ac03c1c550dee3d34d3fe95699dec39fc4cd30a639` |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006D5B10Update.cpp` | `30664f702431536d50942fd7e38d5d0782c4906cc36afe58a5b29fc29e8fbb32` | `b764665ceafa9a0b1cdc393448f81cf0a56e861c44193a746bc01ed6508a3977` |

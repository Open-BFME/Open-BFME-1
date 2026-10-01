# Allocation and subtitle diagnostics bound to the owned pointer cell

## Existing physical owner

`game/Libraries/Source/debug/Rva00F36E5C.cpp` uniquely defines `void *g_Rva00F36E5C = 0`. Its existing data row owns four zero-initialized bytes at retail VA `0x01336E5C` (RVA `0x00F36E5C`). This repair reuses that definition and adds no datum, alias definition, pin, or class identity.

The independent storage evidence is `rva00f36e5c-pointer-provider.md`: matched `Debug::PreStaticInit` at RVA `0x00889500` loads the cell at VA `0x00C8951B`, stores the constructed-object pointer at `0x00C89554`, and reloads it at `0x00C89562`. The native Zero Hour `Debug::Instance` is a by-value object and does not describe this pointer storage. The allocated BFME singleton's original class remains unproven, so the existing built-in opaque pointer view is preserved.

## Actual callers

Two sources referred to the undefined `TheGen001336E5C` with a local `BfmeDebugManager` virtual ABI view. Their actual original DIR32 pointer operands are:

| Body RVA | Verified extent | Pointer operand offsets |
| --- | ---: | --- |
| `0x00433FC0` (`bfmeAlignVIL`) | 202 | `+0x2B`, `+0x39` |
| `0x0088EB30` (`DebugAllocMemory`) | 82 | `+0x1F`, `+0x2D` |
| `0x0088EB90` (`DebugReAllocMemory`) | 188 | `+0x60`, `+0x6E` |

Every field contains VA `0x01336E5C` in retail and compiled addend zero. Both sources now declare the existing `void *g_Rva00F36E5C` and cast at each existing virtual call. The undefined compatibility macro in `debug_internal.cpp` is removed. Original function signatures and local virtual ABI views are unchanged: diagnostic calls dispatch through singleton slots `+0x60` and `+0x6C`, then returned-report slots `+0x38` and `+0x4C`. These slot offsets establish emission and do not recover a native class name.

Same-TU siblings `DebugFreeMemory` at RVA `0x0088EAD0` (19 bytes) and `DebugInternalAssert` at RVA `0x0088EA70` (89 bytes) read no singleton pointer. They remain unchanged and are included in the scoped gate and linked-body control as regression coverage.

## Verification and scope

- Before and after scoped source gates both pass 5/5 existing functions; the after gate also verifies the existing owner data row, five literal references and 17 DIR32 operands.
- The strict current native fixture exits 0; deleting only the protected canonical provider exits 96; original alias callers alongside the actual canonical provider also exit 96. Neither pointer name is eligible for scaffolding.
- The positive MAP selects the canonical provider's actual four-byte zero cell. All six linked pointer operands target that selected address, and all five linked bodies match retail outside their original relocations.
- All five physical literal values are checked against retail. The fixture uses the native import libraries; its eight selected DLL/name import pairs are present in retail. A separate operand audit checks all eleven actual native IAT fields: each linked operand selects its MAP-owned `__imp_` cell and retains retail's DLL/import identity. The only two unrelated direct-callee stubs are explicitly labelled `_bfme_debugRecordCallsite` and `__ftol2`. The fixture establishes physical pointer binding, not their routes or runtime closure.
- Pin consistency and CSV checks pass. No shared header or baseline is edited.

These five bodies contain 580 existing authored source bytes. New function, headline, authored-card, retail-exact and verified data bytes are all zero. Current official `link_check` refuses the owner TU because the accepted `5d21e9aecc` census predates it; no saved-index or whole-graph gain is claimed. Frozen scratch receipts are in `build/debug_manager_binding` and `build/debug_manager_alias`.

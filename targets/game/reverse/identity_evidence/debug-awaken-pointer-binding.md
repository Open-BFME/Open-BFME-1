# Diagnostic callers bound to the owned singleton pointer

## Physical provider

The existing source `game/Libraries/Source/debug/Rva00F36E5C.cpp` defines `void *g_Rva00F36E5C = 0`. Its existing data row uniquely owns four zero-initialized bytes at retail VA `0x01336E5C` (RVA `0x00F36E5C`). This repair reuses that definition and adds no data extent, alias definition, pin, or native class identity.

The independent pointer-cell evidence remains `rva00f36e5c-pointer-provider.md`: matched `Debug::PreStaticInit` at RVA `0x00889500` loads the cell at VA `0x00C8951B`, stores the constructed-object pointer at `0x00C89554`, and reloads it at `0x00C89562`. The native Zero Hour `Debug::Instance` is a by-value object, so substituting that native declaration would misrepresent BFME's physical storage. The original dynamically allocated singleton class is unproven; the existing built-in opaque pointer view expresses exactly the known storage contract.

## Existing callers

Four sources previously referred to an undefined `TheBfmeAwakenDebug` pointer. Their five already matched bodies have these actual original DIR32 operand fields:

| Body RVA | Verified extent | Global operand offsets |
| --- | ---: | --- |
| `0x0088C500` | 60 | `+0x09`, `+0x17` |
| `0x0010B8A0` | 107 | `+0x1C`, `+0x2A` |
| `0x006B7E70` | 748 | `+0x180`, `+0x18E` |
| `0x00889300` | 30 | `+0x06` |
| `0x00889320` | 25 | `+0x06` |

Every field contains VA `0x01336E5C` in retail and has compiled addend zero. Each source now declares the existing `void *g_Rva00F36E5C` and casts it at the actual existing virtual call. All previous method signatures and local virtual ABI views are preserved. In particular, the returned-log slot `+0x4C` has differing unused return views in these callers; this change does not unify them or claim their original return type.

The first three bodies dispatch through debug offsets `+0x60` and `+0x6C`, then returned-log offsets `+0x38` and `+0x4C`. The two forwarders use `+0x80` and `+0x84` with three and two stack arguments. Actual slot numbers are emission evidence; the local class labels are not new native identities.

## Verification and scope

- Normal scoped gate over four callers and the existing data owner: 5/5 matched functions, 1/1 data row, three string references and 16 DIR32 operands.
- Fresh linked caller slices match retail outside their original relocations. All eight linked global load operands select the actual provider's four-byte zero cell.
- Strict link positive exits 0. Removing only the protected provider exits 96; preserving all old alias callers alongside the real provider also exits 96. Neither global name is eligible for scaffolding.
- Twelve unrelated direct callees are explicitly labelled stubs in the scratch fixture. Its nine native PE imports have the same DLL/name pairs as retail. The three physical literal operands retain retail values. This establishes the selected pointer binding, not the unrelated callee routes or runtime closure.
- Pin consistency and CSV checks pass; no shared header is edited.

These five bodies contain 970 existing authored source bytes. New function, headline, authored-card and verified data bytes added are all zero. The saved accepted `5d21e9aecc` census predates the provider TU and official `link_check` refuses to preview that new source; no current whole-graph or saved-index delta is claimed. Frozen scratch receipts reside in `build/debug_awaken_binding` and `build/debug_alias`.

# RVA 0x0026ED70: AI receiver setter, 13 bytes

Source: `retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses below are RVAs; the Ghidra image base is `0x00400000`.
Read-only Ghidra MCP disassembly, bytes, decompilation and xrefs were obtained
2026-10-04. The decompiler's inferred type is not name or byte-match proof.

## Complete body and ABI

```
0026ED70  8B 44 24 04        mov eax,[esp+4]
0026ED74  89 81 00 02 00 00  mov [ecx+200h],eax
0026ED7A  C2 04 00           ret 4
```

The 13-byte body is between CC padding: the preceding function ends with
`pop esi; ret` at `0x0026ED64..65`, and the next function begins at
`0x0026ED80`. The setter takes its receiver in ECX, one 32-bit stack argument,
and pops four argument bytes. It has no calls. ILT `0x00032CCC` is exactly
`E9 9F C0 23 00`, jumping to this body.

## Independent original callers

The Ghidra xrefs to the body contain that ILT only. Its two original callers
both obtain the receiver from an Object's `+0x204` AI slot:

- Matched `Team::updateState`, `0x000F4F30/1293B`: at `0x000F5017`,
  `mov ecx,[esi+204h]` loads a live team member Object's AI. After null/dead
  checks it pushes the saved integer returned by ILT `0x00035107` and calls
  ILT `0x00032CCC` at `0x000F5028` (`updateState+0xF8`). The matched C++ at
  `game/GameEngine/Source/Common/RTS/Team_updateState.cpp` already declares
  and calls `AIUpdateInterface::setRva0026ED70(Int)`. This named caller is
  independent of either rejected setter alias.
- `Object::updateObjValuesFromMapProperties`, `0x001D0610`: at
  `0x001D0C76`, `mov esi,[esi+204h]` loads the Object's AI; at `0x001D0C81`
  it calls the same ILT `0x00035107`, null-checks the AI, pushes EAX, sets
  ECX to that AI, and calls ILT `0x00032CCC` at `0x001D0C8D`.

ILT `0x00035107` jumps to the Lua helper at `0x002EBF60`. The Object layout
analysis (`targets/game/reverse/analysis/object_layout.md`) independently
records `m_ai` at `+0x204`, with 153 source observations. The typed matched
Team caller supplies the `Int` ABI view; neither the original member name
nor the original method name has been proved. Keep the address-derived
`setRva0026ED70` name and leave the `+0x200` storage address explicit.

## Rejected same-byte aliases

`RingRenderObjClass::Set_Flags(unsigned int)` and
`GameWindow::winSetLayout(WindowLayout *)` had each claimed this same 13-byte
body. A generic one-dword store matching bytes cannot make either receiver
identity correct. Both actual call sites use Object AI receivers, not ring
renderers or GUI windows. Retail did not use identical-COMDAT folding.

There is additional contrary evidence for the GUI alias: the matched
`GameWindow::winGetLayout` at `0x00478E20` reads `+0x210`, and original
`0x00478E10/13B` stores `+0x210`, not `+0x200`. That is a separate placement
lead, not a new setter claim in this change. Original `WindowLayout::addWindow`
at `0x00497B4C` calls this GUI setter through ILT `0x00031881` with its
window argument as receiver. A separate existing Int-return claim occupies
`0x00478E10`; the two matched WindowLayout source views disagree on void
versus Int, and that original caller immediately overwrites EAX. This change
does not settle that independent return-ABI dispute or replace its provider.

Retire and tombstone only the two false ledger rows at `0x0026ED70`.
Preserve their existing named implementations and every other source claim;
neither legitimate implementation's proper retail home is assigned here.
The new definition includes the existing owned AI layout header and adds
only a nonvirtual declaration there: no duplicate AI class, virtual slot,
base, member, or layout change.

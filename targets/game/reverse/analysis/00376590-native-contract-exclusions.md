# CastleBehavior::unpack: native-contract exclusions

2026-10-03, retail RVA `0x00376590`, size 1,104 bytes. This pass started at
`1d8499d9fa` and retained the preferred bank unchanged. Its SHA-256 is
`3a9d5de3399f5fa37fe35de680719b064b1b248ab5f43c038e583ea736327b4c`.
No production body, ledger row, pin, or shared header changed.

## Independent retail evidence

Ghidra 12.1.2 through the read-only pyghidra MCP decompiled VA `0x00776590`
and disassembled the second static-key block at VA `0x00776865`. The original
PE, decoded separately with `tools/dis_retail.py`, confirms:

- The matched `CastleBehavior::initiateUnpack` at RVA `0x00376B00` pushes `1`
  at `+0x26`, moves its retained owner from ESI to ECX, and calls ILT
  `0x000084D6` at `+0x2A`. That thunk jumps to `0x00376590`.
- The unpack body uses the low byte of its single stack argument, returns with
  `ret 4` at `+0x44D`, and is followed by INT3 at `+0x450`.
- The CRC format at VA `0x010E9D50` contains `Castle %s(%d) ::unpack()`.
- Both module lookups call ILT `0x0002AE23`, whose body is the matched
  `Object::findModule` at `0x001BEE60`: it reads `this+0x1F0`, compares the
  one stack key against virtual slot `+0x10`, returns the matching module
  pointer in EAX, and uses `ret 4`. The bank's receiver/key ABI agrees.
- The two keys are genuinely separate statics: guard bits 1 and 2 at VA
  `0x012F0868`, with key storage at `0x012F0864` and `0x012F0860`.
  A shared lookup helper with one static would not preserve that contract.

## Measured hypotheses

All probes used real MSVC 7.1 through the existing supported runner, the
unchanged retail 1.03 baseline, and the bank's compiler options. Each variant
was scratch-only. Differences below exclude relocation operands.

| Source context tested | Bytes | Differences | Result |
| --- | ---: | ---: | --- |
| Preferred bank, unchanged | 1,104 | 4 | Reproduced |
| Canonical `object.h`/`thing.h` instead of padded Object copy | 1,104 | 4 | Identical instruction/relocation result |
| Native `rts::hash`/`rts::equal_to` functors with integral ObjectID | 1,104 | 4 | Identical |
| Native ObjectID enum and its `rts::hash` specialization | 1,104 | 4 | Identical |
| Unsigned ObjectID | 1,104 | 4 | Identical |
| Enum/functors with both loop-two volatile expressions removed | 1,102 | 125 | Regressed |
| Non-volatile owner as Object reference | 1,102 | 125 | Regressed |
| Non-volatile owner as const Object reference | 1,102 | 125 | Regressed |
| Non-volatile owner as reference to the pointer member | 1,102 | 125 | Regressed |
| Typed inline Object module accessor around the existing lookup | 1,104 | 4 | Identical |
| Existing matched findModule algorithm visible, explicitly noinline | 1,104 | 4 | Identical |

Canonical Object adoption used the existing configurable members for Coord3D,
AsciiString and model-condition flags, plus TU-only method declarations.
The bank's object position becomes `m_cachedPos`; the write at `+0x258`
uses an address-derived accessor into the header's unmodelled storage.
No layout was added to the shared header. The enum and functor forms come from
GeneralsMD `Common/GameType.h` and `Common/STLTypedefs.h`; they are tested
source-context alternatives, not evidence that BFME's type identity is settled.
The visible findModule algorithm comes from the already-matched Object.cpp.

The four actual byte offsets remain `+0x310`, `+0x315`, `+0x322`, `+0x329`.
Their instruction starts are `+0x30F`, `+0x315`, `+0x321`, `+0x327`:
retail loads/pushes the second key through ECX, then loads/stores the castle
field through EDX; the bank exchanges those registers. Every normalized
instruction agrees. Removing the volatile owner load also changes downstream
status-mask construction and CRC register allocation, so the residue is not
confined to the two explicit field statements in a clean non-volatile spelling.

## Disposition

The canonical Object definition, ObjectID signedness/enum representation,
native hash functors, typed inline lookup accessor, and visibility of the
real lookup callee do not explain the register choice. This pass did not
repeat the historical rotation/pair, vector-bound, or inline-setCastle sweeps.
Stop here rather than force registers or bank a worse body.

The historical 528-byte consumer bank at `0x00377740` is no longer an open
pin blocker: commit `8569c3517d` already promoted it through verified ILT
adapters. Adding an unpack pin solely on that stale report would not unlock
new bytes. No such pin was added.

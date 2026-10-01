# DirtySock: canonical native GetCurrentThreadId import

## Identity and physical contract

Retail's actual PE import directory identifies VA `0x01358D7C` as
`KERNEL32.dll!GetCurrentThreadId`. This is independent of the existing canonical
`__imp__GetCurrentThreadId@0` DIR32 mapping. `callees.py` at the independently
matched full extents reports two calls in `_Rva007FEB00` (201 bytes) and one in
`_Rva007FEBD0` (214 bytes).

The existing pristine Gamespy C `windows.h` declares `DWORD __stdcall
GetCurrentThreadId(void)` (line 114). Actual VS2003 PlatformSDK `WinBase.h`,
lines 2164–2169, independently declares `WINBASEAPI DWORD WINAPI
GetCurrentThreadId(VOID)`. Native MSVC's DWORD is unsigned long, 32 bits; stdcall
has no arguments and returns its DWORD in EAX. The existing C shim was already
included by the published GetTickCount repair. No header, layout, pointer cast,
compiler flag, alias bridge or pin changes are needed.

Remove the old TU-local address-derived unsigned-int import declaration and
replace its three calls with the actual native header declaration. No other
Windows imports change. This is import linkage repair, not new C++ recovery.

## Scope and byte evidence

Owning clone: `build/link_y4_sleep_fresh_36h`, base `28b7995403`.
Scratch: `build/y4_threadid_import`.

Before gate 58889 and final after gate 20166 both exited 0: 40/40 matched bodies,
113 DIR32 references, zero string/float references. The complete COFF audit
compares all40 raw body bytes, relocation offsets and kinds. Exactly three
external relocation names change, from `__imp__Rva01358D7CCurrentId@0` to
`__imp__GetCurrentThreadId@0`:

| Body | Full extent | DIR32 operand offset | Retail FF15 instruction |
| --- | ---: | ---: | --- |
| `_Rva007FEB00` | 201 | +52 | `0x007FEB32` |
| `_Rva007FEB00` | 201 | +150 | `0x007FEB94` |
| `_Rva007FEBD0` | 214 | +122 | `0x007FEC48` |

Compiler-local symbol renumbering is accepted only when the COFF section, value,
type and storage remain identical. Every other external name remains unchanged.

## Actual native binding controls

Controls 54831 exited 0. Each control uses exactly the six actual compiled bytes
at each FF15 instruction, with its real DIR32 relocation. Extraction is checked
against both the original compiled bytes/relocations and retail bytes outside
the relocated operand. These are three edge controls, not full caller objects.
No non-import scaffolding is needed. Positive uses actual native import archives,
`/NODEFAULTLIB`, and no `/FORCE` or weak aliases.

- Native positive LINK exit 0. All three actual selected FF15 operands resolve to
  `0x10002000`. The selected PE's import directory identifies that exact cell as
  `KERNEL32.dll!GetCurrentThreadId`; selected MAP address and native directory
  slot agree under `selected_import_audit`.
- Original address-derived alias: LINK exit 96.
- Missing native Kernel32 import archive: LINK exit 96.
- Fake canonical IAT adversary: LINK exit 0, but binding audit refuses it because
  the selected cell is not a real native DLL/name import. Successful LINK alone
  is not identity proof.

Complete 201/214-byte callers are bytegreen separately. They still need other
real native imports; this packet does not claim they link completely or are
runtime closed. The positive edge controls do not fake those dependencies.

## Currency and gain

Fresh normal pull and check_csv preceded claims. Check_csv passes
171165 functions /89947 symbols /24 data rows; pin consistency passes.
Official link_check after (37881 exit0), using the immutable accepted census at
5d21e9aecc, reports TU `LINKED 0 -> 0` (6988 own bytes), with other unresolved
imports/data/callees explicitly listed. The published Sleep after receipt is
an independent before receipt: this package's before source SHA256 is exactly
`68b10650d73a8d3104c496dcf37d1721d1e5a483f0e56cb8bc6ad9a268fdbb20`.
No speculative source closure sum is reported: **0 new code, 0 data, 0 whole-TU
linked-byte gain**. It removes one wrong import identity at three actual edges.

No functions/data/symbol/pin ledger rows changed. Numerical controls, input
hashes, actual MAP/PE artifacts and all40 audit are in `controls.json` and its
adjacent scratch artifacts.

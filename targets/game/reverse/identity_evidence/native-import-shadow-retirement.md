# Retire three authored shadows of native import-library stubs

The canonical callable names remain owned by their native import libraries.
No new authored definition is introduced at any of the retired RVAs.

| Callable | Retail RVA / bytes | Retail IAT VA | Native import |
| --- | --- | --- | --- |
| `_Sleep@4` | `007E9BB0`, `FF25308F3501` | `01358F30` | KERNEL32.dll!Sleep |
| `_timeGetTime@0` | `007E4810`, `FF2544953501` | `01359544` | WINMM.dll!timeGetTime |
| `__mbslen` | `007AE2D0`, `FF250C933501` | `0135930C` | MSVCR71.dll!_mbslen |

Each extent is exactly the six-byte `jmp [IAT]` instruction. The PE import
directory independently identifies each slot. Native VS2003 import-library
short records define both the callable and its canonical `__imp_` name:
Vc7/lib/kernel32.lib, PlatformSDK/Lib/WinMM.Lib and Vc7/lib/msvcrt.lib.
The short records have no ordinary COFF `.text` body to claim as authored C++.

## Strict native link and old negative

The isolated reproduction at origin/master c145a9e459 uses two explicitly
labelled test TUs, one referencing the canonical callables and one using native
dllimport declarations. They are evidence harnesses, not retail-body claims.
`build/native_probe/check.py` links them against the project's actual retail
import libraries with link.exe, /NODEFAULTLIB, no /FORCE and no import stubs.
The native positive exits zero. Its selected MAP callables have six-byte FF25
bodies whose operands equal their canonical PE import-table entries:

- `_Sleep@4`: `1000104A` -> IAT `10002000`, KERNEL32.dll!Sleep.
- `_timeGetTime@0`: `10001050` -> IAT `10002010`, WINMM.dll!timeGetTime.
- `__mbslen`: `10001044` -> IAT `10002008`, MSVCR71.dll!_mbslen.

Adding the three unchanged authored wrapper objects makes the same strict link
exit 96. All three canonical callable names produce LNK2005 duplicates against
the native import libraries, and all three invented IAT names produce LNK2019:
`__imp__SleepIat@4`, `__imp__timeGetTimeIat@0`, `__imp__mbslenIat`.
The full native/negative receipts and MAP/PE outputs remain in the isolated
checkout's `build/native_probe/` directory.

## Existing actual caller samples

`build/native_probe/callers.py` independently gates and slices three unchanged
retail callers. The byte gate passes 3/3; literal/constant/DIR32 verification
passes. Their actual retail operands read the exact native import slots:

- `_msleep`, RVA00854370, 12B, operand+7 ->01358F30.
- `Rva00905B70`, RVA00905B70, 187B, operand+41 ->01359544.
- `Rva009F7262_mbslen`, RVA009F7262, 6B, operand+2 ->0135930C.

Each sliced actual caller also links strictly against the real native import
libraries. Sleep and _mbslen require no link-only stubs. The time sample labels
its unrelated functions/globals/literals as link-only stubs; no import name is
stubbed. Its selected native imports, including WINMM.dll!timeGetTime, agree
with retail's DLLs and names. The actual caller source files are unchanged.

## Scope and accounting

Only the three invented provider sources, their three six-byte matched rows,
and their independently unused invented DIR32 alias records are removed.
Repository search finds each invented alias only in its own wrapper and DIR32
record; there are no symbols.csv pins for these aliases to retire.
Tombstones in deleted_rows.csv make source-row retirement durable.

This retires **18 authored matched bytes and 18 headline bytes**. It proves
native import selection in scoped real links; it is not a C++ conversion or a
fresh full-census closure measurement. The census's stub-only /NODEFAULTLIB
model needs an explicitly supplied native-library binding context to measure
these imports. No shared header, guard, library model or resolver was relaxed.

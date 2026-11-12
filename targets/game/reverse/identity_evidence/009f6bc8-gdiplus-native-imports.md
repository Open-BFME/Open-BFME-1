# Native GDI+ import candidate (2026-11-12)

**ADMISSION-BLOCKED BANK ONLY.** Production source was restored unchanged;
no function was admitted and no source/closure gain is claimed.

## Target facts

The six complete native entries below each decode as one six-byte x86
`FF 25 disp32` indirect JMP. The operand is the exact GDIPLUS IAT slot in
`targets/game/reverse/imports.csv`, whose DLL/export/ordinal independently
establish the public function identity. No boundary is inferred from adjacency.
Five entries currently have generated `ji_` owners; GdipAlloc already has its
own native C public and is preserved unchanged.

| COFF public | RVA | IAT VA | Full native bytes |
|---|---|---|---|
| `_GdipDisposeImage@4` | `0x009F6BC8` | `0x013591E0` | `ff25e0913501` |
| `_GdipCreateBitmapFromFile@8` | `0x009F6BEC` | `0x013591D0` | `ff25d0913501` |
| `_GdipCreateBitmapFromFileICM@8` | `0x009F6BF2` | `0x013591D4` | `ff25d4913501` |
| `_GdiplusStartup@12` | `0x009F6C0A` | `0x01359208` | `ff2508923501` |
| `_GdipFree@4` | `0x009F6C16` | `0x013591E8` | `ff25e8913501` |
| `_GdipAlloc@4` | `0x009F6C28` | `0x013591C0` | `ff25c0913501` |

The original Platform SDK GdiPlusFlat.h/GdiPlusInit.h/GdiPlusMem.h declarations
supply the stdcall signatures: Status is the SDK enum, bitmap/image arguments
are SDK pointers, startup uses ULONG_PTR*/const GdiplusStartupInput*/output*,
GdipFree returns void and GdipAlloc returns void*. The source includes the
canonical tracked SDK headers, not a private class layout. The native imports
contain File/FileICM but NOT Stream/StreamICM; absent-from-retail emission-anchor
references to Stream APIs are deliberately not manufactured into providers.

## Source and scope

The banked candidate for `game/GameEngine/Source/Common/GdipAllocImportThunk.cpp`
extends its existing MSVC `__identifier` direct-IAT pattern to the five real imports.
The live production file does not contain these additions. Direct IAT
variables permit each public function to own its name without declaring that
same public function dllimport. Actual private compilation emits all six bodies
as FF25+zero-addend DIR32 to their own canonical `__imp__...` symbol. The compiler
stdcall decorations independently agree with the SDK parameter byte counts.
No inline asm/naked code, aliases, pins, generated-source edits, SDK archive feed,
shared-header/class changes, or verifier exceptions are added.

The original SDK import archive is inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Lib/GdiPlus.lib (SHA256
`fb23a7922c04431a52e72181eb555fe12f304ae3398a65eca2ceaf09464abc65`). It is ABI/identity reference,
not a new linked provider or replacement for the source-owned entries.

## Reference sweep and prior work

Approved BFME2 donor remains76f0baefa6f285d54bc1ca922397674312a5913f, read-only.
Its tools/link_cycle.py runtime_libraries supplies msvcrt/oldnames only; no
additional GDI+ provider repair was inherited. Existing BFME1 GdipAlloc is the
local implementation pattern. Attempt-log50755 records its successful full6B
native-IAT proof;57641 is a later rejected address-derived rebinding, not a reason
to repeat that refused identity path. This batch preserves `_GdipAlloc@4`.

The completed SAME99 baseline listed these five direct publics as diagnostic
stubs. Current c79 includes CRT/import setup, defaults and setargv fixes already;
those are not claimed as new repairs. This batch addresses only the remaining
five real GDI+ imports. The baseline also has unrelated CImage/ATL/class/Stream
anchor debt; no whole-program closure gain is claimed or census dispatched.

## Verification evidence

- Before source gate `build/integration/gdiplus-import/before.log`:1/1functions,
  1DIR32, zero body findings.
- Native callee scans and six exact claims:
  `build/integration/gdiplus-import/callees.log`, `gdiplus-import-claims.log`.
- Private source/object/command diagnostics:
  `build/integration/gdiplus-import/{compile.log,compile-command.json,thunks.obj}`.
- ADMISSION BLOCKED: normal add_match rejects gen-import as an unsupported
  scaffold. Its ordinary correct-identity path does not cover this category.
  No ledger change or two-base link control occurred; no image was executed.
- Parent declined any admission category expansion, archive-route repurposing,
  address-owned rename, or manual ledger workaround. Original GdipAlloc source
  restored unchanged; all six exact claims released after preserving the bank.
- Durable candidate, actual compile and both refusal logs:
  `targets/game/reverse/attempt_support/20261112-gdiplus-native-imports-bank/`.
  This is blocked evidence, not recovery or a partial-byte/closure success.

# DXErr9 physical-member retirement: blocked feasibility, 2026-11-13

Baseline `72cdedeab4bda93ec099f6454b92cc568a8e7b96`; runtime
`openai/gpt-6.1-sol:high`; about 10 minutes. No production source, ledger,
import pin, type, layout, alias or gate mutation. Source gain/loss: **0/0**.
The four lookup recoveries (162756 non-0xCC bytes) and five helpers (190)
are already baseline, not this experiment's work.

## Fresh native boundary

The existing source paths are `game/Libraries/Source/DirectX/`'s four
`dxerr{string,description}{a,w}.cpp` units and `strsafe.cpp`. Fresh private
MSVC 13.10.3077 compilation reproduced their native extents. The five helper
sections preserve raw bytes but change COFF selection from ANY (2) to NODUP (1).
The four lookup sections are NODUP in both the native member and source objects.
Full section/public/relocation inventories, including COMMON and directives,
were recorded; raw symbol-section indices are retained, so a raw relocation
record inequality is not itself a semantic edge mismatch.

Two identical link boundaries at image bases `0x10000000` and `0x20000000`
use real `_DXTraceA@20` and `_DXTraceW@20` roots, original dxerr9.lib and
shipped MSVC CRT/Kernel32/User32 libraries, `/NODEFAULTLIB /OPT:REF /OPT:NOICF`,
no driver, stubs, aliases, forced success, custom import definition or execution.
Original-only links return 0, but **are not valid retail closure fixtures**:
they import `MSVCR71.dll!_vsnwprintf`, absent from retail. Retail instead
imports `?vswprintf@@YAHPAGIPBGPAD@Z` at VA `0x01359228`.
Adding the five current source objects fails both links with nine LNK2005s:
four lookup roots and all five helpers. Physical native member extraction
cannot be dismissed because a body matches individually.

The archive still owns `_DXTraceA@20` (RVA `0x00AFD388`, 374 bytes),
`_DXTraceW@20` (`0x00AFD20F`, 377) and
`?StringVPrintfWorkerW@@YGJPAGIPBGPAD@Z` (`0x00AD5443`, 75): 826 extent
bytes, not measured recovered nonpadding bytes. Retiring only ANSI helpers
cannot retire the member. No Trace or inline-cohort compiler bank from another
machine was assumed present, reused or credited.

## Dependencies and ruled-out adaptations

Fresh `import_binding.py check` of
`game/GameEngine/Source/Common/System/UnicodeString.cpp` fails on the legacy
wrong-name `__imp___vsnwprintf` and invented `__imp__wcscspn`/`__imp__wcsspn`;
its link imports three names absent from retail. Thus repairing the wide route
requires existing-consumer reconciliation beyond this lane's approved scope.
No wrong-name pin, generated thunk metadata, import descriptor or consumer was
changed. No whole-census completeness or linked-byte estimate is asserted.

D3DX's public-name intersection is exactly two narrow helpers
(`StringCopyWorkerA`, `StringVPrintfWorkerA`) plus two unique literal symbols
(empty string and newline). None of the five baseline helper recoveries occurs
in that intersection. One resource member `obj\\i386\\d3dx.res` was explicitly
rejected by the existing strict COFF parser (truncated string table), retained
as an audit limitation, not silently treated as a parsed provider.

Pinned BFME2 donor revision `76f0baefa6f285d54bc1ca922397674312a5913f`:
`Code/Libraries/Source/DirectX/{strsafe,dxtracea,dxtracew}.cpp` and
`reverse/attempt_support/dxerr-lookups-20261018.md` reviewed. August2005
compiler/ABI/literal/control-flow contexts differ. Its strsafe synthetic
`strSafeEmissionTarget` retention scaffold is explicitly inapplicable; it is
not a natural provider-cohort proof and was not imported. Public previous
Trace/printfw bank notes were read; their unavailable private objects/logs were
not used as evidence here.

## Receipts and resume boundary

Reproducer: `physical_member_feasibility.py` in this directory, entered via the
experiment's external `integration.sh` launcher before project imports. It
writes only private `build/spike3/` artifacts and never executes linked images.
Fresh raw receipt: `build/spike3/dxerr-feasibility/report.json`; link logs/maps
in that directory; summary `build/spike3/concise-summary.log`; Unicode import
failure `build/spike3/unicode-import-before.log`. `check_csv.py` passes.
Initial diagnostic run stopped on the resource parse refusal; rerun records
that refusal explicitly. No acceptance masking or parser change was made.

Parent explicitly selected banking rather than broad Unicode/class/CRT work.
Resume only with a separately approved existing-consumer/import contract and
natural ANY helper emission proof. A current full closure delta remains NULL.

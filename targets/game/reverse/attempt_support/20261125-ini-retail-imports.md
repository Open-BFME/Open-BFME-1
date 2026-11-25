# WWLib INI retail CRT imports

Round baseline: `c5b6f6bc563565b1d73f8a41191e87dbddd04149`.
One logical whole-file linking repair; no new bodies, code, or static data.

## Actual imported APIs

The original BFME1 image imports `MSVCR71.dll!_mbsdup` at IAT VA
`0x01359308` and `MSVCR71.dll!_strcmpi` at `0x0135933C`. It does not
import `_strdup` or `_stricmp`. Complete original callers establish all
eight affected IAT operands:

| INIClass member | RVA / extent | Original operand offsets | API |
|---|---|---|---|
| Load(Straw&) | 009E4680 / 1744 B | +328, +486, +496 | _mbsdup |
| Get_Alloc_String | 009E3E70 / 72 B | +37 | _mbsdup |
| Get_List_Index | 009E3EC0 / 135 B | +41 | _strcmpi |
| Get_Int_Bitfield | 009E3F50 / 211 B | +3E, +76 | _mbsdup, _strcmpi |
| Get_Alloc_Int_Array | 009E4030 / 236 B | +39 | _mbsdup |

Use the genuine VC7 public `<mbstring.h>` declaration of `_mbsdup`,
`unsigned char* __cdecl(const unsigned char*)`, with explicit buffer-pointer
conversions, and the existing `<string.h>` declaration of `_strcmpi`.
Seven source duplication expressions produce the same six existing COFF
operands because the array method merges branches. Two comparisons produce
the remaining two operands. No helper, hand CRT prototype, macro, allocator,
object view, layout, flag, pin, alias, emitter, or game header changes.
The unrelated `nstrdup` calls remain unchanged.

Compiler arguments, compiler digest, retry directories, include-search roots,
and generated INCLUDE/LIB/PATH are unchanged. All 56 previous dependency
digests remain identical; the only added dependency is the actual SDK
`mbstring.h`. Full inherited host-environment equality is not claimed.

## Genuine changed EH prerequisite

Historical attempt 52486 passed the two comparison bodies but restored the
source when eight of 18 shifted cleanup labels were ambiguous under the old
unique-body rule. Its exact record exists in the log blob of `e77ee5f477^`,
so it demonstrably predates the existing native state-index twin-proof
upgrade `e77ee5f4776f450a90bac06b04d288b35a5ba6a2`. No verifier change is
part of this task.

Both the unchanged control and candidate prove the original parent FuncInfo,
toState, and action graph. The normal `eh_state_pins.py --fix` writer alone
updates 18 object-symbol notes: eight state-index-proven twins and ten unique
cleanups. No row name, parent, source, RVA, extent, or other ledger field
changes. All other ledger records and line terminators are byte-identical.
The fix command returns 1 from its pre-fix stale report despite writing all
18 verified repairs; a separate postcheck returns 0 with all 18 proven.

## Whole-file and actual object verification

Ordinary control/candidate/postfix builds pass 209/209 rows in the whole TU,
127 DIR32 references, 57 literals plus seven empty strings, and two float
constants, with zero baselined body findings. FDU finds no unrowed definition.
Four proven TU-static references and five local-table entries remain native
body-guard categories; they are not privately upgraded to global ownership.

An initial strict paired-object comparison correctly refuses additional
compiler-local renumbering. The preserved V1 diff identifies it explicitly.
The final comparison binds 70 concrete local names by 18 native original
EH-parent chains (FuncInfo, unwind map, and 29 actions) and five Get_Bool
in-body DIR32 operands independently checked against the original image.
Every binding preserves actual owner, section, offset, storage, type, target,
and raw payload; no arithmetic label-offset or textual wildcard is accepted.
After only those bindings and the eight PE-proven import-name changes, all
462 runtime/FPO/data/EH/COMDAT/CRT/SafeSEH/directive sections, weak edges,
definitions, and other relocations are exact. There are no new emissions.

Native import classification reports two wrong-name imports before and zero
after. The separate normal `import_binding.py check` byte gate passes, but
its isolated DLL harness still fails on `___DebugIncludeInLink1`, required
only by an identical existing /include directive. Its actual existing source
is `game/Libraries/Source/debug/debug_debug.cpp`. The harness failure is
preserved, not labelled PASS; no stub, directive, library, or allowance is
added. Original Load1744's native RetailTruth UNKNOWN remains UNKNOWN.

## Measured link preview and limits

Normal BEFORE: exit 1, 542.1 s, LINKED 0 -> 0; only `__imp__strdup` and
`__imp__stricmp` are missing. Normal AFTER: exit 0, 219.7 s, 1/1 LINKS,
LINKED 0 -> 14,133 bytes. Both are scoped previews using legacy census
`42237e2367` (2026-11-21 10:53), not a new full-image census or runtime test.
All function/data rows and exact/unique code coverage are retained, not new.

Read-only historical BFME2 donor `e2e99959950e6eebfe1ced5663aa05de320afc52`
has a distinct direct-strdup recipe and allocator/constructor settings.
Those declarations/macros/flags are not ported: BFME1's actual indirect IAT
operands and public SDK contract establish this adaptation independently.

The sibling JSON binds complete private original decodes, native reports,
actual normal objects, compiler/dependency receipts, refusals, and proof
scripts by hash. Claims cover all 208 actual code RVAs; the metadata-only
repins and prerequisite artifacts do not create extra task or body credit.

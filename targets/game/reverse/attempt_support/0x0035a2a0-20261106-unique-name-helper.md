# 0x0035A2A0 unique-name helper (350 B) — s559 handoff

Retail: file-static helper with a private convention (owner in ECX, `AsciiString *name`
on the stack, caller cleans). It returns at once when `rvaLookupReleased0035a220(owner,
name)` is true; otherwise it loops `candidate.format("%s %d", name->str(), ++suffix)`
until an inlined copy of the 0x0035A220 lookup returns true, then `name->set(candidate)`.
Twin: 0x0035A060 (same shape over the 0x00359FE0 table at owner+0x0C).

Best candidate: `targets/game/reverse/attempt_history/0x0035a2a0/6af400a1cbdea96a9adb214a35f277446c9435085f6a6de94fe40a95d68e75d0.json` (s559; re_log kept the older raw-pointer form as the preferred stash because it has fewer raw byte diffs) (probe symbol
`?rvaUniqueName0035a2a0@@YAXPAVRva0035A220Owner@@PAVAsciiString@@@Z`, 351/350 B,
shape 0.917, 14 structural diffs, 249 raw byte diffs because registers rotate).

What moved the shape (0.842 -> 0.917):
- The table at owner+0x2C is two real STLport vectors (`vector<int>` name indexes at
  +0x00, `vector<Record>` records at +0x0C), not raw begin/end/capacity ints. With
  real `<vector>` (`// stlport`, `_STLP_NO_EXCEPTIONS`) VC7.1 reproduces retail's
  in-place `add reg,0x2c` on the ECX owner, the rec*20 offset kept in EBP and the
  records base reloaded for the released read. Raw-pointer views CSE the record
  pointer instead (the old 0.84 bank shape).
- The inlined lookup must be a separate inline function (do/while on its result);
  the compare is the accessor form (getLength()/str(), TheNullChr fallback) with
  retail's that-first evaluation order.
- Keeping the owner live inside the loop (inline taking `void *owner`, released
  read through owner) flips the helper to a plain stack convention: avoid.

Remaining mismatch: retail keeps the table in EBX for the whole loop and spills the
record index to [esp+0x1C] (cmp [esp+0x1C],-1), zero lives in ESI, candidate data
in EDI. Ours keeps the record index in EBX and spills the table to [esp+0x18].

Inert this session (all 0.917/249 or worse): param order or `void *` owner, table as
a reference or declared before the candidate, `const`/no record-index local (worse),
two nested ifs, member-function inline lookup on the table, `__forceinline` lookup,
header `AsciiString::compare`, `*name = candidate`, flags /O1 /Ox /Ob2 /G6 /G7
/Oy-, `volatile` record index (worse), int-returning lookup (0.908).
Untried: compiling it beside the real 227 B caller 0x0035DF10 (an earlier session
reported the ECX convention there), and the 0x0035A060 twin with this form.

## Caller 0x0035DF10 is probe-EXACT with this helper (s559)

Bank `targets/game/reverse/attempts/0x0035df10.cpp`: `Rva0035DF10ScriptParser::parse(
DataChunkInput &, DataChunkInfo *)` (thiscall, RET 8) compiles 227/227 EXACT beside the
static helper above. Levers: a `table` local (`&m_owner->m_nameTable`) gives retail's
unfolded `add eax,0x2c; mov eax,[eax+0xc]`; read `node->m_extra` before the record, then
`m_references` before `m_nodes`; `if (count > skip) { n = count - skip; do ... while (--n); }`;
append with `m_list->insertAfter(m_list->getLast(), node)` (two-variable last walk) so the
empty branch reloads `m_head`. It must not land until the helper matches too (the caller's
call ABI depends on the helper's private convention; docs/shape_levers.md
"Compiler-private ABI"). Compiling the helper beside the real caller instead of a stub
did not change the helper (still 0.917 / 249).

Also inert (s559, later): visible bodies of `findNameIndex` and
`rvaLookupReleased0035a220` in the TU; owner-member inline lookup (0.900); suffix/table
declared before the early return (0.858/0.883); the whole tail inside `if (!lookup) {}`;
address-taken or out-parameter record index (optimised back to a register). The twin
0x0035A060 with the same form gives the identical 0.917 / 14 plateau.

## Caller 0x0035DD40 is probe-EXACT with the 0x0035A060 helper (s559)

Bank `targets/game/reverse/attempts/0x0035dd40.cpp`: `Rva0035DD40GroupParser::parse(
DataChunkInput &, DataChunkInfo *)` (363/363 EXACT) beside the static twin helper
`rvaUniqueName0035a060` (owner table at +0x0C). Same record walk and
`m_list->insertAfter(m_list->getLast(), node)` (head at +0x00 here), then the two
registration objects (`Rva00352AB0ParserRegistration`, `Rva00350F50ParserRegistration`,
args owner, `&group->m_list8`, file, `(AsciiString *)info`) with the base
`BfmeParserRegistrationVE` destructor inline (`_bfmeVftVE` store then
`Q1Forwardee0000871A::handle(m_parser)` on `m_table`), returning `file.parse(0)`.
Lever: the two `readByte() != 0` results go through named `bool` locals before the
stores; without them node/group swap EBX/EBP (0.967).

Helper progress after that lever: a named `unsigned int count = m_nameIndexes.size()`
gives 0.925 / 12 structural (still the table spill); named bool/int temps for the
lookup result, compare result and the first lookup call are inert on top of it.
So four bodies (0x35A060 350, 0x35A2A0 350, 0x35DD40 363, 0x35DF10 227 = 1290 B) land
together once the helper's EBX priority is solved.

## Later s559: named temps move the table into EBX (now 70 raw diffs, 6 structural)

New preferred stash `targets/game/reverse/attempts/0x0035a2a0.cpp`: inside the inlined lookup,
`unsigned int count = table->m_nameIndexes.size(); if (nameIndex < count)` (0.925 alone), and
in the loop a separate statement `const char *text = name->str();` before `++suffix` and the
format call. Together they reproduce retail's allocation (table in EBX, record index spilled
to [esp+0x1c], zero in ESI). Remaining: retail pushes `suffix` before it reads
`name->str()` (the text is an argument expression there), and the scratch registers after
findNameIndex are rotated (retail ECX=begin/EDX=size/ECX=rec, suffix in EAX across the loop).
Moving the str() back into the argument list (`text = name->str()` in the call, `++suffix`
in the call, `int number = ++suffix`, a `source` copy of name) restores the old 0.925
allocation; the count lever without the text statement is 0.892. The same two levers should
be tried on the 0x0035A060 twin.

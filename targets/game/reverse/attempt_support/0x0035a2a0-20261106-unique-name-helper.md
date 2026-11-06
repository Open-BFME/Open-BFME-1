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

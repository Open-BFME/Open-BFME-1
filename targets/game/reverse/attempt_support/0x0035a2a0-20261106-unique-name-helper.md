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

## 2026-11-07: BFME 2 donor shape (fixupScriptName), 68 raw diffs

The BFME 2 donor `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptFixupNames.cpp` (at revision dbde7dbe) spells this helper as WB's `fixupScriptName` (the twin is `fixupGroupName`):

    if (!lookup(list, name)) {
        AsciiString candidate; int suffix = 0;
        do { candidate.format("%s %d", name.str(), ++suffix); } while (!lookup(list, candidate));
        name = candidate;
    }

The donor's names are a hint only; BFME 1 keeps address-derived names. Scratch is under `build/h35a2a0/` (gen.py, gen2.py, gen3.py).

**Inert, across a 32-way factorial plus 8 more variants:**
- an early return versus an `if` block
- `AsciiString &` versus `*`
- a table local versus `&owner->m_nameTable` at the call
- the lookup rewritten as an index-returning `find()`, as a member or as a free inline, followed by `if (index != -1) return records[index].m_released`

**The donor's argument-form loop (`name.str(), ++suffix` in the call):**
- It reproduces retail's loop top exactly: `mov ecx,name; inc eax; mov [esp+18h],eax; push eax; str()`.
- But it flips the allocation: the table goes to ESI and is spilled/reloaded each pass, and the record index takes EBX.
- Scores: 353 B / 252 diffs with `count`, 351 B / 249 without.

**New best (stashed), 350 B / 68 raw diffs, shape 0.958/7:**

    ++suffix; const char *text = name.str(); candidate.format("%s %d", text, suffix);

What is left in it:
- Loop top: the suffix is in ECX (retail EAX), and the `push suffix` comes after `str()`.
- After `findNameIndex`, the begin/count registers are swapped, and the record offset is in EAX where retail uses EBP. That moves the compare temporaries to EDX/EBP (retail EAX/EDX).

**Also measured:**

| Variant | Size | Diffs |
|---|---|---|
| `int number = ++suffix` | 353 | 252 |
| `AsciiString *source = &name` | 353 | 252 |
| `suffix++` statement | 353 | 252 |
| `unsigned` suffix | 353 | 252 |
| a `const AsciiString &` alias | 353 | 252 |
| an outer `text` declaration assigned in the loop | 350 | 70 |
| a named `AsciiString fmt` | 395 | 250 |

Only a separate `text` statement keeps the table in EBX.

## 2026-11-07 (second pass): ten more hypotheses, still 68


Target symbol: `?rvaUniqueName0035a2a0@@YAXPAVRva0035A220Owner@@AAVAsciiString@@@Z`
(row `?d_0035a2a0@@YAXXZ`). Toolchain: VC7.1 `/O2` (build default) with
`/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS`,
`// stlport`. Scratch: `build/wf/0035a2a0/` (`gen.py`, `combo.py`, `v/`).

## Status

The bank still reproduces: `targets/game/reverse/attempts/0x0035a2a0.cpp`
(copied as `build/wf/0035a2a0/base.cpp`) compiles to 350/350 B with 68
non-relocation diffs and shape 0.958/7. No variant tested here beat it.

## Two allocation attractors (this session's main finding)

Every variant compiled to one of two register assignments. Which one it got
depended on how the loop top was spelled:

| loop top | owner/table | zero | record index | callee-saved for compare | result |
|---|---|---|---|---|---|
| retail | EBX | ESI | spilled `[esp+1c]` | EBP = rec*20 | n/a |
| `text` statement (`++suffix; const char *text = name.str(); format(text, suffix)`) | EBX | ESI | spilled | EBP = thatLen, offset in EAX | 350 B / 68 |
| arg form (`format("%s %d", name.str(), ++suffix)`) | ESI, spilled to `[esp+18]` around the compare | EDI | EBX | EBP = thatLen | 353 B / 252 |

- Retail's loop top (`mov ecx,name; inc eax; mov [esp+18],eax; push eax; mov eax,[ecx]...`) puts the suffix push in the same basic block as the start of `str()`. That only happens when `name.str()` is evaluated inside the `format` argument list. The arg form reproduces the loop top byte for byte.
- So retail is almost certainly the arg form, plus some feature that keeps the owner in EBX and the zero in ESI. That feature has not been found.
- When `str()` runs as a separate statement before the call, the good attractor follows, but the suffix is pushed after the text.

## Ruled out this session (each in both loop forms unless noted)

- **(a) Control flow:**
  - `for(;;)` with `break`, nested `if` and `continue` forms of the manually inlined lookup
  - an early return
  - `for (int suffix = 1;;)`
  - post-increment, `suffix + 1` with a later `++`, and starting at 1 with `suffix++`

  None changed the attractor.
- **(b) Lifetime:**
  - Declaration order of `candidate`, `suffix` and `table`: this changes only the slots (arg 257/258).
  - `table` declared inside the loop or before the first call (355/287).
  - Named locals for the released byte, the compare result, a record-name reference, a `done` bool, a `probe` pointer, a result reference, `name.set()`, and an `out` reference for `format`.
- **(c) Types and layout:** an `unsigned` record index, `vector<void*>` name indexes (the donor's type), `size_t`, an `int` name index with a cast, and a `const int &` record index (352/176 in the bank form, 353/252 in the arg form).
- **(c, compare spelling):**
  - 8 single-level and 12 two-level variants in the StringBase `compare(data,len)` style. The tail used if-return, a ternary or `if (result)`, with both min orders and with and without a named `n`. All stay in their attractor, and the `result = ...; if (result == 0) result = len diff` form is worse (356/193).
  - The header `AsciiString::compare` (`""` fallback) flips even the bank form to the bad attractor (353/253).
- **(d) Callee visibility:**
  - A visible static (auto-inline) lookup used at both sites inlines both (411 B).
  - Anonymous-namespace member: a normal thiscall with `ret 4`, not a private convention.
  - An extern (stack-convention) helper keeps the same attractor split (arg 355/275, bank 350/118).
  - Non-`noinline` static helper: identical.
  - A `getNameTable()` inline accessor and the qualified `StringBase<char>::str()`.
  - `findNameIndex(const StringBase<char>&)`, the donor's signature.
  - An inline `rvaMakeName` wrapper around `format`.
  - Explicit `AsciiString("%s %d")`.
- **(e) Flags:** `/O2 /Ob1` (Rva00359E40ClearActiveRecords.cpp sibling), `/G5`, `/G6 /Ob1`, `/GX`, `/Ogtyb2` and `/Oi-` are identical. `/Os` and `/Oy-` are far worse. Dropping `_STLP_NO_EXCEPTIONS` or `_STLP_USE_STATIC_LIB`, which the Scripts.cpp sibling does not pass, is identical.
- **(f) Evaluation order:**
  - Arg-form spellings `suffix += 1`, `suffix = suffix + 1` and `(++suffix, suffix)` are all 353/252.
  - Text-first (`text` statement then `++suffix` in the arg list) is 350/70.
  - `tools/rotation_sweep.py` on the bank: all 7 toggles are inert (68).
- **Factorial sampling** (`combo.py`): 14 toggles (count local, unsigned index, owner-param lookup, header compare, early return, pointer name, `const&` lookup, released local, `find()` split, suffix first, `for`-break, `void*` indexes, no table local, compare local).
  - 81 random arg-form samples, plus 40 more with the header compare: all in the bad attractor, with 249-261 diffs.
  - 61 text-form samples: none below 68.

## Remaining mismatch (bank, 68 bytes)

```
retail                                    | ours (bank)
0050 mov ecx,[esp+30]; inc eax; mov [esp+18],eax; push eax; mov eax,[ecx] ... (str after push)
                                          | 0050 mov edx,[esp+30]; mov eax,[edx]; inc ecx; ...; push ecx; push eax
0095 mov ecx,[ebx]; mov edx,[ebx+4]       | mov edx,[ebx]; mov ecx,[ebx+4]      (begin/end swapped)
00a7 mov ecx,[ecx+eax*4]; mov eax,[ebx+c]; lea ebp,[ecx+ecx*4] ... shl ebp,2
                                          | mov eax,[edx+eax*4]; ...; lea eax,[eax+eax*4]; shl eax,2
     compare: thisLen EAX, thatLen/result EDX, offset EBP
                                          | compare: thisLen EDX, thatLen/result EBP, offset EAX
0120 mov cl,[eax+ebp+c]                   | mov dl,[eax+ecx+c]
```

## Next steps worth trying

- Find the feature that keeps the owner in EBX while using the arg form. Measured so far: the lookup body, the compare spelling, flags and declaration order cannot flip it.
- Candidate (untested) hypothesis: the real source has another live value or call in the helper that changes the global (region) weights. Examples are a second use of `owner` after the loop that the compiler folds, or the twin helper and 0x0035A220 compiled in the same TU with this one.
- Tested late in this session (g26): making 0x0035A220 a visible `static __declspec(noinline)` with its StringBase compare is worse (arg 352/237, bank 352/223). The likely cause is a changed call convention to the lookup. Still untested: the full retail TU order 0x00359FE0, 0x0035A060, 0x0035A220, 0x0035A2A0 with the lookups kept external.
- The twin 0x0035A060 has the same retail shape, so a fix should apply to both.

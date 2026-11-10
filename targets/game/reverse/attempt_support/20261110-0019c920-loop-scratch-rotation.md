# 0x0019C920 `?validateSides@SidesList@@QAE_NXZ` (1810 B): handoff

> `build/wf/0019c920/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x0019c920.cpp`.

## Result

The best candidate is `build/wf/0019c920/best.cpp`. It compiles to 1810/1810 bytes
with **2 non-relocation bytes** different (+04d8 and +04dc). The 0.997 bank had 6.
Compiler flags are unchanged from the bank:
`/DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib`.
The starting point was `targets/game/reverse/attempts/0x0019c920.cpp`, and it still
reproduces exactly as logged: 6 bytes at +04d8, +04dc, +05c1, +0611, +069e and +06d4.

## What fixed the stack-slot residue (4 bytes)

The fix is a lexical scope. `Int index` and the `findTeam` lookup, together with its
`if (ti && index) {...} else { Dict d; ... }`, now sit in their own `{ }` block inside
the player loop, and the block closes before `allies` and `enemies` are declared. With
that change, MSVC 7.1 packs the last loop's `tname` into `index`'s slot (esp+0x20), as
retail does, and `d` keeps esp+0x1c alone.

- `/FAsc` before: `_tname$1050 = -56` shared with `_d$1020`, and `_index$1011 = -52`
  alone.
- After: `_d$1020 = -56`, and `_tname$1050 = -52` shared with `_index$1011`.

What it takes:

- **Only `index`'s scope matters.** Leaving `Int index` outside the block, with only
  `ti` and the if/else inside it (o4), keeps all 6 bytes.
- **The block has to end before `allies`.** Opening it earlier (just after
  `tname.concat`) gives the same result.
- **Why it works.** This is consistent with docs/shape_levers.md (~line 3591): for
  address-taken locals, the packer measures interference by lexical scope, not by
  dataflow. Declaring `index` at function scope or in other positions did not help,
  as earlier sessions found.

## Remaining mismatch (2 bytes, scratch register only, shape 1.000)

```
04d7 50            push eax
04d8 8d 44 24 3c   lea eax,[esp+0x3c]   | ours: 8d 4c 24 3c  lea ecx,[esp+0x3c]
04dc 50            push eax             | ours: 51           push ecx
04dd 8b ce         mov ecx,esi
04df e8 ..         call Dict::getAsciiString (via ILT 0x2FF6D)
```

This is the hidden-return address of `tname` in the first team loop (the `goto`
loop). The next temporary, `lea edx,[tname]` for the by-value copy passed to
`findSideInfo`, already matches. After that point the code is in sync again.

What the experiments show about this register choice:

- **It is a scratch-register rotation count from the player loop's tail.** It is not
  decided inside the goto loop.
- **Single removals move it by whole steps.** Each removal below takes out one LEA
  argument temporary and moves the choice by one place: ecx to eax, or ecx to edx.
  - removing `pdict->setAsciiString(TheKey_playerEnemies.key(), enemies)` gives eax;
  - default-constructing `enemies` gives eax;
  - removing the `validateAllyEnemyList(pname, enemies)` test gives edx;
  - removing the whole player loop gives eax.
- **Code before the player loop has no effect** (the `neutral`/`addPlayerByTemplate`
  block, loop-1 edits), and neither does deleting the last loop.
- **Ours appears to have one extra rotation step (mod 3), or retail one fewer.** The
  step sits somewhere between the enemies `setAsciiString` LEA (+0420, edx, which
  matches) and +04d8, and that code is otherwise byte-identical.

## Hypotheses tested this session (all keep 2 diffs unless noted)

**Rotation lever (`tools/rotation_sweep.py`)**

- 52 single toggles: none fixed it.
- `--pairs`, 1371 variants: nothing below 2 diffs.

**Goto-loop spelling (generated, 648 variants, all 2 diffs)**

- head forms: `for`, `while`, reused `i`, `m_nodes[0].m_next`, `t` outside the loop,
  `for(;;)` with `break`;
- `nodes`/`base`/unsigned offset forms; a cast or node-view `next`;
- cast, node or indexed `tdict`, in either order;
- copy-init or direct-init `tname`;
- `findSideInfo(tname)` written as plain, `!= 0`, or `, 0`;
- a named `SidesInfo*` result;
- inverted if/else and `else t = next`.

**Loop-2 tail and condition spellings (all neutral)**

- `m_numSides` in place of `getNumSides()`;
- `!(a.compare(b) == 0)`, a named bool, `!= false`, `== false`;
- an implicit `StaticNameKey::operator NameKeyType()` at the goto, enemies and allies
  sites;
- an inline `getDict()` view (`TeamsInfo` wrapper) at any of the 4 `ti` sites;
- inline helpers `sameStr`/`diffStr` for the comparisons;
- extra `{}` blocks around `allies`/`enemies`;
- a `SidesInfo *side` local.

**Destructor model (private header copies in `build/wf/0019c920/hdr1-3`)**

- `~StringBase` without `validate()`: neutral.
- a doubled `validate()`: neutral.
- `~AsciiString` removed (implicit destructor): neutral.

**Callee visibility**

- A by-value inline `SidesList::findTeamInfo(AsciiString key, Int*)` (0x19C520's
  shape, BFME2 donor `forward(Join(...), &index)`): neutral.
- A typed `Dict *lookup(AsciiString*, Int*)`: neutral.

**Earlier slot experiments (6-diff base), now superseded by the block**

- The weight probes `(void)index` x1 and x3 had no effect, and are not landable anyway.
- `Int index = 0` moves the slots but adds a store.

**Donors read**

- BFME 2 `Code/GameEngine/Source/GameLogic/Map/SidesList_validateSides.cpp` at
  2bac16a6. It has the same structure, with `renameTeam` and `removeTeam` out of line;
  no ABI difference explains the residue.
- Zero Hour `GeneralsMD/.../Map/SidesList.cpp` `validateSides`.

## Next ideas (not tried)

- Find the invisible extra rotation step between the enemies `setAsciiString` (+0420)
  and the goto-loop LEA. Candidates are the loop-2 increment and condition IL
  (`getSideInfo` strength reduction `tv982`, `i++`) and the four end-of-body
  destructors with their EH state stores.
- Measure single-step contributions there with `(void)`-free code changes, as above,
  using `regof.sh`.
- Look for an inline in the retail loop-2 tail that we write without a copy, for
  example `validateAllyEnemyList` taking its list through an inline wrapper.

## Landing notes (candidate is not exact; read-only checks only)

- **Callees.** Every call target uses the bank's existing ledger or pin names, which
  `tools/callees.py 0x19C920 1810` confirms: `Rva0019C520Member::lookup` (0x19B780),
  `Rva0019BC00Owner::prepare` (ILT 0x20D97) and `::finish` (ILT 0x26EE),
  `Rva0019BE80TeamRec::append` (0x19BA40), `Rva00195FC0JoinPath`,
  `SidesList::findSideInfo`, `::addPlayerByTemplate`, `::validateAllyEnemyList`, the
  `Dict` members, and `StaticNameKey::key`. The block change adds no callee and no
  global.
- **TU.** The target row currently points at the naked `__emit` lift in
  `game/GameEngine/Source/GameLogic/Map/SidesList.cpp`. The bank's self-contained view
  classes suggest a new sibling TU, like
  `SidesListValidateAllyEnemyList.cpp` / `SidesListAddPlayerByTemplate.cpp` (same cl
  line), with the naked lift deleted.

## Scratch artefacts

- `best.cpp`: the best candidate.
- `cand1.cpp`: the same candidate before re-indenting.
- `v/*.cpp` and `v/*.asm`: trial variants and their `/FAs` listings.
- `rot_pairs.txt`: rotation-sweep output.
- `mkv.py`, `tab.sh`, `regof.sh`: the variant, frame-table and goto-register helpers.

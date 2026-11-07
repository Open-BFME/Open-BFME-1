# 0x002C3E00 (382 B, RET12): EXACT via a by-value return with a copy-constructed position type

## Result

`build/wf/0x002c3e00/best.cpp` is EXACT at 382 bytes:
`python3 tools/probe.py build/wf/0x002c3e00/best.cpp '?rva002C3E00@Rva002C3FE0Owner@@QAE?AURva002C3E00Position@@PA_N_N@Z' 0x002C3E00 --size 382`
gives `result EXACT (modulo relocation slots)`, with 2 relocs: the helper call and the 0.5f literal.
`best_homeflags.cpp` is the same body built with the helper TU's flags and BFME 1's own
`Libraries/Include/Lib/Coord3D.h`. It is also EXACT.

- Flags (best.cpp): `/Igame /DNDEBUG /MD /EHsc /I<ZH>/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib`. These are the bank's flags.
- Flags (best_homeflags.cpp): `/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc` from the helper TU
  `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C3FE0HeightClearance.cpp`,
  plus `/Igame /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib`
  for object.h and matrix3d.h.

## What closed it

The BFME 2 donor `Rva0036C6AFState::rva0036C8A5` is the same routine. It is at open-bfme-2
dbde7dbe, `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00368C7A.cpp`, and is
matched there at 406 B. It cites "BF1 BfmeGiantBirdFollowThruStateOnEnter" as its guide. The
donor's shape:

- returns the position BY VALUE (a hidden return pointer), not through a `Coord3D *out` parameter;
- uses a Coord3D-derived position type with a user-written `__forceinline` copy constructor;
- copy-constructs `offset = direction; offset.scale(distance);` and `candidate = *pos; candidate.add(&offset);`;
- has an early `if (!ai) return best;`, `limit *= 2.0f` and `if (limit / 2.0f > reached)`.

Ported unchanged except for BFME 1 types (Object::m_cachedPos/m_transform/m_ai, Vector3 Get_X_Vector),
this was EXACT on the first compile. The /FAsc table gives retail's homes:
last -60, candidate -48, xv -36, direction -24, offset -12.

Evidence for the ABI from BFME 1 retail: EAX = the first stack argument at every exit
(+0x15E `mov eax,[esp+0x5c]` on both the null-AI and loop paths, kept through `ret 0xc`).
That is the hidden-return-pointer contract. The caller 0x002C3B90 (BfmeGiantBirdFollowThruState::onEnter)
pushes enabled, &result, &goal in that order, which works with either spelling. The caller
binds through `j_00033a87`, so the mangled name does not affect the caller's link.

## Ablations (all from the exact donor port)

| change | result |
|---|---|
| void + `Coord3D *out` param, `*out = best` (donor body otherwise) | 407 B, 347 diffs |
| return plain `Coord3D` by value (no copy ctor on the return type) | 411 B, 344 diffs |
| remove the user copy ctor from the position type | 402 B, 353 diffs |
| donor port as is | EXACT |

The copy constructor and the by-value return are both required. This is consistent with the
shape_levers entry "Retail returns a small object BY VALUE through a hidden pointer ... Give the
returned class a copy constructor".

## Earlier dead ends (from re_attempts.log, now explained)

All of these used the void/out-param ABI with POD Coord3D:

- The seven-difference bank: a loop position object and slot displacement.
- The 20-difference exact-instruction source: last and candidate homes swapped.
- About 60 declaration, scope, alias, set/field and aggregate spellings.
- A by-value `Coord3D` return without a copy constructor (384 B).

The swap was a weight and order artefact of that ABI and type. It was not a stack-slot quirk
that local spellings could fix.

## Landing notes (read-only checks; not landed)

a. `tools/ilt_oracle.py check` reports CONTRADICTED (p_false=3.9e-4, outside slots
   41498:25030-25035). It does the same for every placeholder spelling, including the old
   `QAEXPAUCoord3D@@PA_N_N@Z`, `?d_002c3e00@@YAXXZ` and a `?AUCoord3D@@` return. The real EA name
   sorts elsewhere and is unknown. The existing address-derived pin at the target's ILT is
   `?j_00033a87@@YAXXZ` (functions.csv, gen-thunk, target=FUN_006c3e00). The caller already
   binds through it. Land under an address-derived opaque name, for example the one in best.cpp:
   `?rva002C3E00@Rva002C3FE0Owner@@QAE?AURva002C3E00Position@@PA_N_N@Z`. Pick a different
   return-type name only if the evidence supports one; the donor's `FollowPosition` is an
   agent-inferred placeholder, not an EA name.
b. Inline COMDAT copies the TU emits, each probed against its retail row:
   - `??0Vector3@@QAE@MMM@Z` at 0x000693F0 (25 B): EXACT.
   - `?Get_X_Vector@Matrix3D@@QBE?AVVector3@@XZ` at 0x00131DC0 (23 B): EXACT.
   - `??AVector4@@QBEABMH@Z` at 0x000FBB80 (10 B): EXACT.
   - `??_H@YGXPAXIHP6EPAX0@Z@Z` at 0x0005C600 (48 B): EXACT.

   The `Rva002C3E00Position` ctor/set/scale/add COMDATs are TU-local inline members with no
   retail rows. The helper `?method@Rva002C3FE0Owner@@QAE_NPBUCoord3D@@M@Z` (0x002C3FE0) is
   declared only (UNDEF), not defined.
c. Globals by address: `fmul dword ptr [0x0107533C]` is the compiler literal `__real@3f000000` (0.5f).
   - data_rows.csv:1665 says 0x0107533C is `__real@3f000000`.
   - data_rows.csv:103 rows the same address as `?g_rva0107533C@@3MB`.
   - dir32_addresses.csv records several names at that address, including `?g_bfmeK1253@@3MB`,
     the name dis_retail prints.

   The body has no other absolute data references.
d. TU: `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C3FE0HeightClearance.cpp`.
   It already holds the helper and the `Rva002C3FE0Owner` class (this+0x1c context, ret-8
   `method`), and best_homeflags.cpp builds EXACT with its flags and its Coord3D.h. That TU needs:
   - `/Igame /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib`
     (or equivalent includes) for object.h and matrix3d.h;
   - the `rva002C3E00` declaration added to its `Rva002C3FE0Owner`.

   Verify the helper stays exact after the include change. Commit title prefix:
   `[BFME 2 donor]`. Record donor revision dbde7dbe and path in the evidence.

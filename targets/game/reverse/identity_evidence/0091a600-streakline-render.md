# RVA 0x0091A600 is StreakLineClass::Render(RenderInfoClass&)

All facts below were checked against the unpacked retail `lotrbfme.exe`
with pefile and capstone (image base 0x00400000). Ghidra's byte-pattern search
finds the body pointer at VA 0x0113AD58 and its created function reports
130 bytes, agreeing with `ret 4` at RVA 0x0091A67F and INT3 at 0x0091A682.

## Owner is proved by independently matched constructors

The matched `StreakLineClass` default constructor at RVA 0x0091A730 stores
VA **0x0113AD28** into `[esi]` at 0x0091A755, and its copy constructor at
0x00919F40 makes the same store at 0x00919F67. Both constructors are clean
C++ in `game/Libraries/Source/WWVegas/WW3D2/StreakLineCtor.cpp` and construct
the segment and streak renderers at +0x104 and +0x154. Their owner is not
inferred from this candidate or a deleting-destructor name.

The primary table's slot **12**, offset **+0x30**, VA **0x0113AD58**, points
directly to VA **0x00D1A600**. This library function has no ILT stub and no
direct call/jump references. It is not a slot of the neighbouring SimpleDynVec
vtable at 0x0113AD14 or the secondary-base table at 0x0113AD20.

The BFME RenderObjClass declaration's ordering identifies primary slot 12 as
Render; named Clone/Class_ID and base name-accessor slots before it agree
with that ordering. The owning StreakLine declaration in the canonical
GeneralsMD WW3D2 `streak.h` overrides `Render(RenderInfoClass&)` publicly.

## BFME body agrees with the named operation

- Its initial virtual call uses slot 96 (+0x180). The owner's table stores
  ILT VA 0x0040BF1E there, which jumps to RVA 0x006CF6D0, the matched
  `RenderObjClass::Is_Not_Hidden_At_All` returning an int.
- It tests WW3D's IsSortingEnabled byte at VA 0x012D6D74. If false it copies
  the shader word from +0x108 and calls the independently matched
  `ShaderClass::Guess_Sort_Level` at RVA 0x00910E90.
- It tests AreStaticSortListsEnabled at VA 0x0133F42D and, for a nonzero
  sort level, calls matched `WW3D::Add_To_Static_Sort_List` at 0x008FD4C0
  with this same owner and the level.
- Otherwise it calls the independently matched StreakLine methods
  `Render_Streak_Line` at 0x00919AC0 or `Render_Seg_Line` at 0x00919A70,
  forwarding the sole reference argument. The first branch requires the
  PointColors and PointWidths counts at +0xF0 and +0x100 to be nonzero.

The witnesses from `name_oracle.py --class StreakLineClass` place PointColors
at +0xE4, PointWidths at +0xF4 and LineRenderer at +0x104. Their count members
(+0x0C) and shader (+4) give exactly the three BFME operand offsets above.
The canonical GeneralsMD `streak.cpp` Render body has this same visibility,
sort-list and streak/segment sequence. Together with the independent owner
and virtual slot, this proves the name
`?Render@StreakLineClass@@UAEXAAVRenderInfoClass@@@Z`.

## Source and byte verification

The unchanged canonical Render body initially compiled to 130 bytes with
six non-relocation byte differences, all from four operand offsets: the
visibility call used +0x178, shader +0xD4, colors count +0xBC and widths count
+0xCC. Its control flow and register shape already matched.

The source uses the same BFME typed layout views already used by its matched
siblings for the containers and renderer. A TU-local address-qualified virtual
view dispatches the independently proved visibility slot +0x180 without
changing the shared RenderObjClass header. The adjusted body probes EXACT
130/130 bytes modulo six relocation slots; add_match verifies every callee,
global and relocation target before the row is accepted. No inline assembly or generated source changes are used for this conversion.

The full source gate initially rejected one unresolved call to
`Render_Streak_Line`. Although its existing matched row is backed by clean
C++, the ledger name is still `?d_00919ac0@@YAXXZ` with an object-symbol note,
which does not resolve this external name automatically. A single body pin
for the real method is included as the dependency repair. Independently of
the candidate's name, its 129-byte body at RVA 0x00919AC0 checks the same
constructor-proven three point containers at +0xD4/+0xE4/+0xF4, obtains the
bounding sphere via +0x108, then calls its streak renderer at this+0x154 with
those containers, the sphere, transform and sole RenderInfo reference.
Its `ret 4` at +0x7E proves the reference-argument thiscall. The existing
`StreakLineRender.cpp` reconstruction and canonical GeneralsMD
`Render_Streak_Line` agree exactly in these operations. Pin consistency is
checked before the addition (no previous pin) and after the repair.

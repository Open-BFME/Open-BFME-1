# 0x00245010 FormationBuild00245010::build (828 B)

Retail body in HordeContain.cpp: both GameLogicRandomValue calls push the
`F:\bfme\Code\gameengine\Source\GameLogic\Object\Contain\HordeContain\HordeContain.cpp`
literal with lines 0x4fb and 0x4fe. The real class and method names are not
proven, so the body keeps the address-qualified name `FormationBuild00245010::build`
that its earlier banked attempts used.

Callee and layout evidence (retail disassembly of 0x00245010):

- `+0x309` calls ILT 0x000178EB -> 0x00244E60 with ECX = this, unadjusted.
  0x00244E60 is landed as `Rva00244E60::add` (game/GameEngine/Source/GameLogic/AI/Rva00244E60.cpp)
  and pushes into `_STL::vector<BfmeRva44E60Record>` at this+0x12c. This body
  pushes 16-byte records into the same member through the ILTs that
  targets/game/reverse/symbols.csv already pins as
  `??0BfmeRva44E60Record@@QAE@XZ` (0x00033D39), `_Construct<BfmeRva44E60Record>`
  (0x0001476D) and `vector<BfmeRva44E60Record>::_M_insert_overflow` (0x0001DE3A).
  The earlier bank's `Record00245010::field000` is therefore the sibling's
  `BfmeRva44E60Record::m_value`, and its `FormationBuild00245010` members
  +0x04..+0x12c belong to the `Rva00244E60` view that the landed sibling declares.
- `+0x31f` calls ILT 0x00038604 -> 0x00244F00 with ECX = this and the module
  data as argument. 0x00244F00 is landed as
  `Rva00244F00Owner::rva00244f00(Rva0024SourceHolder *)`
  (game/GameEngine/Source/GameLogic/Object/Contain/Rva00244F00RecordBuild.cpp);
  the earlier bank's local wrapper name `extra` is that callee.
- `+0x23d/+0x262/+0x282` construct, copy and overflow-insert 28-byte elements
  into this+0x1d8 through ILTs 0x0001AACD, 0x000128DC and 0x0000C5D6, which
  symbols.csv pins as `Rva00244A80Element`'s constructor, `_Construct` and
  `_M_insert_overflow`; landed 0x002459D0
  (Rva002459D0HordeMemberAdd.cpp) declares the same member as
  `_STL::vector<Rva00244A80Element>`. The earlier bank's `Slot00245010` is that type.
- `+0x326` calls ILT 0x0001D9D0 -> 0x0023B9F0 (still a gen dump) as a
  no-argument thiscall on this. Earlier verdicts on 0x0023B9F0 in
  re_attempts.log call it `rva0023B9F0`; nothing proves the earlier bank's
  wrapper name `finish`, so the pin keeps the address token.
- `+0x67` and `+0x73` call ILTs 0x00042898 (-> 0x0023DD50) and 0x00034D24
  (-> 0x0023E120) with ECX = this+0x12c and this+0x1d8 and the summed position
  count: `reserve` on the two vectors above. Retail was linked without
  identical-COMDAT folding, so each ILT is exactly that instantiation. Both
  are pinned under the element types' `vector<T>::reserve` names.

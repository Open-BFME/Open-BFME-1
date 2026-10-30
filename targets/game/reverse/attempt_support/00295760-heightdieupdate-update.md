# 0x00295760 HeightDieUpdate::update (654 B) — session 495 bank

BFME 1 target evidence: ctor 0x00295550 installs vtable VA 0x010BF608 at
+0x10, slot 0 -> ILT 0x0002C926 -> this body; ilt_oracle CONFIRMS
`?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ`.
Semantic source: ZH HeightDieUpdate::update. Donor shape: open-bfme-2
20a0cb6173 Code/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp
(KindOf filter temporary + wide iterator). Filter declarations follow the
matched Rva002FA7C0ScriptAction.cpp (BitFlags<192> kInit ctor pinned at ILT
0x8D0F, Rva000C3DD0VptrZeroBlockObject, PartitionFilter vtable 0x01083B5C).
Iterator: ThePartitionManager as BfmeWideForwardC::bfmeForwardWideC (5 ints),
result dtor = BfmeThingCAD::bfmeGoCAD (0x000C5FC0), payload {start, finish,
eos, cursor} of 8-byte pairs.

Bank (attempts/0x00295760.cpp, variant h7b): 650/654 B, 241 masked diffs.
Everything matches (EH states, filter temporaries, cross-jumped
m_lastPosition tail) except the inlined iterator next() at +0x170:
retail `mov ecx,[iter]; mov eax,[ecx+4]; mov edx,[ecx+0xC]; cmp edx,eax;
je; mov eax,edx; mov edx,[eax]; add eax,8; test edx,edx; mov [ecx+0xC],eax`.
00295760-heightdie-h4a-loopshape.cpp.txt (243 diffs, 652 B) has retail's
load order (finish first, register compare) but every scratch register one
step rotated (payload EDX/finish ECX/cursor EAX), which also drops retail's
`mov eax,edx` copy (-2 B).
Levers that got here: pos hoisting is wrong (keep the contained branch's own
getPosition read); the cross-jumped tail only forms once the loop's
registers line up (h7b next() form).
Inert for the rotation: next() as a payload method, post/pre-increment
spellings, iterator copy locals, for(;;)/if-not loops, obj initialised,
declaration order of obj/thisHeight/tallestHeight, inline radius accessor,
&m_position. A self local for the range/position read breaks the frame.

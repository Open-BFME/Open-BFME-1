# Lone vftable re-seat destructors do not prove their owner class

Bodies of the shape `mov dword ptr [ecx],V / ret` (and `... / jmp ~Base`)
are destructors that re-seat vftable V. MSVC 7.1 drops a derived class's own
vftable store when the inlined base destructor re-stores the base vftable, so
such a body is ~V **or** the destructor of any trivially-destructible
descendant of V. Retail shows it: 511 lone-store destructors over only 119
vftables, one vftable stored by about 120 bodies, and 0x007FA670 is
byte-identical to the matched ~Rva00803890Base at 0x007FA650 (same vftable).

The six T2InlinedEmptyDtors.cpp names (`??1T2EmptyDtor_008018a0` etc.) were
given to unclaimed bodies at 0x00801420, 0x00802200, 0x00802280, 0x00802870,
0x00802E30 and 0x008062F0 only because each re-seats that class's vftable.
That is not proof, and that file marks those destructors absent from retail,
so the bodies return to address-derived `Rva<addr>VtableReseat` names. Only a
caller, or an EH unwind / ??_G that calls (not inlines) the body, can promote
one to ~Owner.

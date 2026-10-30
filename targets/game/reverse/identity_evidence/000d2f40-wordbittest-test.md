# 0x000D2F40 WordBitTest000D2F40::test (37 B)

Facts from BFME 1 retail:
- 0x000D2F40..0x000D2F65: `mov edx,[esp+4]; push esi; mov esi,ecx; ...; and;
  neg; sbb; neg; ret 4`. thiscall, one unsigned index, word `index>>5`, mask
  `1<<(index&31)`, normalized bool in EAX. INT3 padding follows.
- Every caller reaches it through ILT 0x0000666D (`jmp 0x000D2F40`):
  0x001ECB23, 0x00200592, 0x0020067D, 0x0024E011, 0x0024E0AB, 0x00279AE5,
  0x00279AF5, 0x0029B7FE, 0x002B1EC5, 0x003720CF, 0x004A42ED, 0x005A8DF0,
  0x0076CCFA. Matched callers in ReactionUpdate00200420.cpp,
  PhysicsBehaviorUpdate.cpp and Rva0076CB10RenderFlags.cpp already spell it
  `?test@WordBitTest000D2F40@@QBE_NI@Z` (symbols.csv pin 0x000D2F40), but no
  object defined that name (link queue #33, census 1d5131d3f1).

The previous row `?dup_000d2f40@@YAXXZ` was a gen-alias pointing at one of
many byte-equal STLport `bitset<116>::_Unchecked_test` COMDAT copies emitted by
AcademyStats.cpp; it named no specific identity for this address. The
address-derived name keeps the address and claims nothing beyond the bytes and
the call relationship. Its original EA spelling (likely a ModelConditionFlags
bit test instantiation) is unproven.

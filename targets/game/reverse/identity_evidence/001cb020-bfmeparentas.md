# 0x001CB020 BfmeObjAS::bfmeParentAS (119 B)

Facts from BFME 1 retail:
- 0x001CB020..0x001CB096 is instruction-for-instruction the body at
  0x001CB0C0 (`RvaC4390Second::resolve`, matched in RvaC4390Second_resolve.cpp):
  template final-override walk via ILT 0x000022BB, flag 0x1000 at +0xD4,
  +0x214 kind 0x6C test via ILT 0x0003251F, byte-tested argument enabling a
  TheGameLogic->findObjectByID (ILT 0x0001F253) of the id at +0x78. Only the
  rel32 operands differ (the two bodies sit 0xA0 apart).
- ILT 0x0000FAA6 jumps to 0x001CB020; symbols.csv pins
  `?bfmeParentAS@BfmeObjAS@@QAEPAV1@H@Z` there, and matched callers in
  AIUpdateConditionCooldown0027BF60.cpp, Rva00242B90.cpp,
  StealthUpdate_markAsDetected.cpp, RunReadyAction0027A7A0.cpp and
  BfmeConv1899.cpp already spell it; nothing defined it (link queue #49,
  census 1d5131d3f1).

The previous row `?dup_001cb020@@YAXXZ` was a gen-alias whose object symbol
(`RvaC4390Second::resolve`) the resolver binds to the other copy at
0x001CB0C0. The pinned placeholder name is kept; the owning class and the
original EA name of either copy are unproven.

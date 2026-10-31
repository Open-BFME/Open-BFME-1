# 0x0076E4F0 bfmeCallEMA: the ParticleSysBone parsing body (556 B)

- Boundary: ret at the end of 556 B; a cdecl free function (pops nothing,
  ignores ECX) taking three pointers, so the lift's name
  `?flashAsSelected@Drawable@@QAEXPBURGBColor@@@Z` (thiscall, one pointer) is
  wrong.
- Callers: the matched ParticleSysBone FieldParse callback 0x0076E7B0
  (ParseParticleSysBone.cpp, from the animation-state FieldParse table at
  0x012BB650) and its twin 0x0076E7D0 forward (ini, state block, state
  block + 0x50) here; symbols.csv already pins this address as
  `?bfmeCallEMA@@YAXPAXPAUBfmeThingEMA@@PAUBfmeSubEMA@@@Z`.
- Body: Zero Hour's parseParticleSysBone (bone name, toLower, particle system
  template, list push_back) plus BFME's FollowBone/HouseColor, FXTrigger,
  Persist and PersistID keywords. The owning name stays the existing
  placeholder pin.

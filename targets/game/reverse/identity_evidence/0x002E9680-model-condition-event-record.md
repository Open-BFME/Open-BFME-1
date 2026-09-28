# 0x002E9680: the pushed element is a model-condition event record

`LuaScriptEngine::rva002E9680ParseModelConditionEvent` (identity from the
matched dispatcher 0x002EA5D0, which calls it for the "ModelConditionEvent"
tag) builds a 0x54-byte local and appends it to the vector at engine+0x98.

What retail proves about that element (0x002E9680):

- +0x1A2: `lea ecx,[ebp-0xC8]; call ILT 0x00025E1E` -> 0x002DF780
  (`mov [ecx],0; mov eax,ecx; ret`): its constructor only zeroes the first
  dword.
- +0x1B6..+0x1D4: two 10-dword `rep movsd` copies from the two locally parsed
  304-bit condition sets into element+0x04 and element+0x2C.
- +0x1E9: `call ILT 0x00022BF6` -> 0x002DFA00, which stores
  `TheNameKeyGenerator->nameToKey(text)` into element+0x00, with the "Name"
  attribute's text.
- +0x200..+0x243: the duplicate search compares element+0x00 as one dword, then
  element+0x04 and element+0x2C as 10 words each.

So the element is {name key, required condition words, excluded condition words}:
a model-condition event record. The banked attempt spelled it
`WeaponTemplateSet` (typedef `Gen84`) only because the reallocating insert it
reaches (0x002E7AA0, via ILT 0x0001636F) carries that element name in the ledger;
nothing witnesses a WeaponTemplateSet layout there. The landing names the record
by address (`Rva002E9680ModelConditionEvent`) and pins its insert name at the
same ILT (pin_consistency: consistent extent).

The bank's `LuaScriptEngine` member names below +0x98 (`m_events` and its
neighbours) are not read by this body and have no layout witness; the landing
keeps that span as unnamed padding.

# RVA 0x002803F0: AttributeModifierAuraUpdate update interface

The former `??1AttributeModifierAuraUpdate@@UAE@XZ` lift name is contradicted
by independent constructor, vtable, destructor and body evidence.

- Matched factory `friend_newModuleInstance` at RVA 0x0011A8D0 names the
  AttributeModifierAuraUpdate constructor at 0x002800D0.
- That constructor installs VA 0x010BAFA0 at primary `this+0x10`
  (instruction VA 0x00680158). Its slot zero points to ILT RVA 0x00011036,
  which jumps to RVA 0x002803F0. This is the UpdateModuleInterface subobject:
  the base constructor installs UpdateModule's corresponding table there.
- The actual protected destructor `??1AttributeModifierAuraUpdate@@MAE@XZ`
  is already matched at RVA 0x0027FF70; its scalar deleting destructor is
  0x002802A0. The public-destructor lift is not an overload of that destructor.
- This body takes the adjusted secondary receiver: module data at `this-12`,
  object at `this-8`, upgrade interface at `this+16`. It returns 0x3FFFFFFF
  when inactive or a signed object-id modulo five plus the configured interval.
  It enumerates nearby objects and applies modifier expiry, FX, and named
  attribute modifiers. It does not destroy the receiver or its bases.
- The replacement is `?update@AttributeModifierAuraUpdate@@UAE?AW4UpdateSleepTime@@XZ`,
  following the same secondary-receiver update ABI as independently matched
  DelayedLuaEventUpdate. This TU models only that interface receiver.
- Retail begins at 0x006803F0 with the EH registration and 0xA4-byte local
  allocation, and ends in `ret` at 0x006809AE: exactly 1471 bytes.

Validation: full-body GhidraSQL draft was checked against retail disassembly;
MSVC 7.1 probe matched all 1471 bytes modulo relocations before landing.
The scoped build must also resolve every REL32 and verify strings/DIR32.

The only new pin is the address-retaining BfmeTaintManager::queryAt00880E60.
Both aligned call sites push Object+0x38 and load TheTaintManager from VA
0x012ED5C0. At 0x00880E60 the retail wrapper loads ECX from this+0xC and
jumps to 0x008814A0. Independently matched taintmanager_impl.cpp identifies
that destination as Gen_008812D0::bfmeValueAtWorld: point x/y lookup, int
result, one stack argument (ret4). No guessed method identity is claimed.

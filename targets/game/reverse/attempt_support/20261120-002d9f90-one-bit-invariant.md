# RVA0x002D9F90: a proved one-bit invariant closes the TEST encoding residue

Target:67 bytes through RET at+0x42. Existing direct/ILT callers are DynamicPortalBehaviour::removeUpgrade, AttributeModifierUpgrade::removeUpgrade, GeometryUpgrade::removeUpgrade and WeaponSetUpgrade::removeUpgrade. They establish the shared upgrade helper role; they do not establish its original lexical class name, so the source retains Rva002D9F90Behavior.

The body reads the module data pointer at+4, owner at+8 and signed condition at module-data+0x64, returns for null pointers or condition=-1, and clears the selected owner+0x110 dword bit before notifying Object. The partial pointer views do not claim complete class sizes. The existing Object::notifyModelConditionChanged ILT pin binds RVA 0x0002191D, which jumps to the rowed body at 0x001BE1C0. The source preserves that descriptive name and existing __thiscall/no-stack-argument binding; it adds no pin or address alias. An earlier private trial used an opaque alias of the same ILT; the normal descriptive spelling passes the ordinary relocation gate and is retained in production.

The preferred C++ bank was67 bytes with one non-relocation difference: TEST eax,edx rather than retail TEST edx,eax. On pinned MSVC7.1, placing __assume((mask & (mask-1u)) ==0) after mask=1u<<(condition&31) produces the target encoding and leaves every other instruction unchanged. Unsigned int is32 bits in this compiler; the shift count is0..31, so mask has exactly one bit set and the assumption is mathematically true for every input. It excludes no execution that this source can reach and emits no runtime check.

Six bounded controls were tested in private build/codex-body-recovery-20261120/bit-invariants outputs. Only the one-bit hint alone gives67/67 modulo relocations. Nonzero alone, shift-range, extraction-domain and adding nonzero to the one-bit hint retain the original one-byte residue; a structured nonzero branch grows to71 bytes. The existing bank is unchanged. This is a measured compiler-shape lever, not a claim about retail source or a general optimizer rule. The normal add_match, relocation, byte, identity, commit and publication gates remain required.

The semantic operation follows the Zero Hour UpgradeModule family; BFME1 addresses, offsets, callee binding and exact extent come from its own binary/callers. No donor address, class size or compiler setting is imported. No memory, crash, FPS, multicore or64-bit improvement is inferred.

Retiring the generated row removes its old symbol from normal resolution. Three
existing removeUpgrade consumers (AttributeModifierUpgrade, GeometryUpgrade and
WeaponSetUpgrade) therefore replace their old cdecl-symbol/member-pointer unions
with the reconstructed typed thiscall declaration at the same receiver offset.
The ordinary combined build verifies all four rows, preserving the consumers'
346 existing bytes. These consumer repairs are prerequisites of this one new
67-byte body, not three additional recovered bodies.

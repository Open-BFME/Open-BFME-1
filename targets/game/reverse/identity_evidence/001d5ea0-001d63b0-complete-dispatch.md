# Complete ObjectCreationList dispatch extents

The two old24-byte claims omit executable code. Independently decode the
unpacked1.03 image:001D5EA0 ends RET16 at001D5ECF beforeCC at001D5ED2
(total50B);001D63B0 has two complete RET12 tails, the last at001D63F2
beforeCC at001D63F5 (total69B). Ghidra-created functions independently
report50/69B. No padding or second function is swallowed.

## Contradicted fire-weapon signature

The former FireWeaponNugget::create declaration has five stack arguments
(three pointers, angle, lifetime), returns Object*, and emits XOR EAX,EAX;
retail pops only16bytes and has no return-zero instruction. RET16 positively
refutes that exact decorated identity. The50B entry remains fully opaque
as Rva001D5EA0::method with four stack arguments and no result contract.
Its receiver+4 is passed as the existing WeaponTemplate argument to
WeaponStore::createAndFireTempWeapon(WeaponTemplate const*,Object const*,
Coord3D const*), through001D5EC9 ->ILT00035E5E ->001EA9C0.
That existing103B native callee consumes three stack arguments and uses
the source/coordinate contract. The global is the same TheWeaponStore
used by its native caller; the scoped DIR32 check proves VA012EF738.
No new callee name or pin is introduced.

## Correct wrapper dispatch; retain its legacy name

Retail001D63B0 computes nullable position pointers at Object+38, then calls
slot+0C with primary object, primary position, secondary position and the
incoming third argument. The old source pushes an extra -100.0 angle and
uses slot+10. Its incomplete prefix concealed both differences.
Constructor001D5E80 installs tableVA0109F0DC. Table slot2 is
VA00431273 ->001D63B0; slot3 isVA00426161 ->001D5EA0. Thus the same actual
dispatch family independently supplies the corrected four-argument slot;
this is not a vtable alignment inferred from a guessed method name.

Unlike the five-argument fire entry, the wrapper's inherited three-argument
name/signature is not independently disproved solely by these bytes. Its
legacy ObjectCreationNugget::create row name is therefore retained under the
user's no-mass-renaming policy, with object-symbol selecting the explicit
Rva001D63B0::method ABI view. The view uses the proven void-consumed slot
contract and asserts no semantic slot name. A pointer-return interpretation
of the inherited name remains UNPROVEN, not newly established by this byte
repair. There are no new real identities here.

Both views include the existing Object/Weapon reference headers and native
Coord3D declarations. The full native source initially reproduces50/50 and
69/69 bytes modulo relocations; production acceptance additionally requires
normal strict add_match and source/callee gates.

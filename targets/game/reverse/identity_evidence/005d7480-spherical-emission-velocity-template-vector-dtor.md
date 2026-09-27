# Vector deleting destructor at 0x005D7480

The 84-byte body at 0x005D7480 was filed as
`??_ELogicalDecalClass@MultiFixedPoolDecalSystemClass@@QAEPAXI@Z` (decalsys.cpp).
It is `??_ESphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAEPAXI@Z`.

- It is virtual, not the `QAE` a LogicalDecalClass `??_E` would be. Its ILT
  0x00007C07 is slot 0 of vtable 0x01110B24, and the only functions carrying that
  vtable constant are the two matched SphericalEmissionVelocityModuleTemplate
  constructors, 0x005D72F0 and 0x005D73C0. Slot 3 of the same table is the
  matched `SphericalEmissionVelocityModuleTemplate::writeINI` (ILT 0x000160FE).
- It pushes element size 0x18 and destructor ILT 0x0003CC2C, which jumps to
  0x005D7380, the matched `??1SphericalEmissionVelocityModuleTemplate`. The
  matched `??_GSphericalEmissionVelocityModuleTemplate` at 0x005D7450, 0x30 bytes
  earlier, calls the same ILT. Every other FXParticleSystem class has the same
  `??_G` then `??_E` pair (Hemispherical at 0x005D75D0/0x005D7600,
  DefaultDrawModuleInfo at 0x005D56C0/0x005D56F0).

Retail reaches 0x005D7480 only through that vtable slot and the adjustor thunk
0x005DCFF0, which jumps to the same ILT.

The DIR32 gate flagged the old name. decalsys.cpp's row named ILT 0x0003CC2C
`??1LogicalDecalClass`, while two pins put that destructor at 0x0002A08B. Both pins
existed only for this row, and both are deleted. 0x0002A08B is Hemispherical's
destructor ILT; see 0002a08b-00019772-ilt-thunks.md.

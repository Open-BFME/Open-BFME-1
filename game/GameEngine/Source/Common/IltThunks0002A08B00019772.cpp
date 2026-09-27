// Two incremental-link thunks that were filed under functions they do not reach.
// 0x0002A08B jumps to 0x005D7520, the destructor HemisphericalEmissionVelocity-
// ModuleTemplate's deleting destructors call through it, not to
// MultiFixedPoolDecalSystemClass::LogicalDecalClass's destructor. 0x00019772
// jumps to 0x002284A0, the builder the "OpenContain" module-data factory passes
// to initFromINIMultiProc, not to ActiveBodyModuleData::buildFieldParse (that
// factory passes ILT 0x00012355). Claimed by address, as the ILT convention says.
// Under /O2 a tail call with no arguments is exactly `E9 rel32`.

void b_005d7520();
void b_002284a0();

void j_0002a08b() { b_005d7520(); }
void j_00019772() { b_002284a0(); }

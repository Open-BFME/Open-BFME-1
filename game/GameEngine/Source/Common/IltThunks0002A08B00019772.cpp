// Two incremental-link thunks that were filed under functions they do not reach.
// 0x0002A08B jumps to 0x005D7520, the destructor HemisphericalEmissionVelocity-
// ModuleTemplate's deleting destructors call through it, not to
// MultiFixedPoolDecalSystemClass::LogicalDecalClass's destructor. 0x00019772
// jumps to 0x002284A0, the builder the "OpenContain" module-data factory passes
// to initFromINIMultiProc, not to ActiveBodyModuleData::buildFieldParse (that
// factory passes ILT 0x00012355). Claimed by address, as the ILT convention says.
// Under /O2 a tail call with no arguments is exactly `E9 rel32`.

// Both targets take arguments (the destructor ECX, the builder a stack
// reference); naming their decorated symbols directly keeps the plain
// `E9 rel32` with ECX and the stack untouched.
extern "C" void __identifier("??1HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ")();

extern "C" void __identifier("?build@Rva002284A0FieldParseBuilder@@SAXAAVMultiIniFieldParse@@@Z")();

void j_0002a08b() { __identifier("??1HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ")(); }
void j_00019772() { __identifier("?build@Rva002284A0FieldParseBuilder@@SAXAAVMultiIniFieldParse@@@Z")(); }

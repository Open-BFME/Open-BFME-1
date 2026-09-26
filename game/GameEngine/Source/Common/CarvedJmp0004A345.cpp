// cl: /DNDEBUG /MD /O2
// Retail RVA 0x0004A345 is a five-byte jump thunk to the matched
// StructureCollapseUpdate constructor at RVA 0x002AE200.

extern void structureCollapseUpdateTarget(void);

#pragma comment(linker, "/alternatename:?structureCollapseUpdateTarget@@YAXXZ=??0StructureCollapseUpdate@@QAE@PAVThing@@PBVModuleData@@@Z")

// ?j_0004a345@@YAXXZ
void j_0004a345(void)
{
	structureCollapseUpdateTarget();
}

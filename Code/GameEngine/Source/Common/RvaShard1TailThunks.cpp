// cl: /O2 /MD
//
// Address-qualified incremental-link tail thunks.  Their independently
// matched destinations establish the jump routes; the no-argument forwarding
// declarations preserve the real receiver and arguments on the caller stack.

extern void rva0000EF5CTarget(void);
extern void rva000119E1Target(void);
extern void rva00022683Target(void);
extern void rva0002F095Target(void);
extern void rva000399A5Target(void);

#pragma comment(linker, "/alternatename:?rva0000EF5CTarget@@YAXXZ=??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z")
#pragma comment(linker, "/alternatename:?rva000119E1Target@@YAXXZ=?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z")
#pragma comment(linker, "/alternatename:?rva00022683Target@@YAXXZ=?readDict@DataChunkInput@@QAE?AVDict@@XZ")
#pragma comment(linker, "/alternatename:?rva0002F095Target@@YAXXZ=?copy@UnsignedPairTreeCopyShim@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$$CBGE@_STL@@@2@PAU32@0@Z")
#pragma comment(linker, "/alternatename:?rva000399A5Target@@YAXXZ=?setOrientation@Thing@@QAEXM@Z")

void j_0000EF5C(void)
{
	rva0000EF5CTarget();
}

void j_000119E1(void)
{
	rva000119E1Target();
}

void j_00022683(void)
{
	rva00022683Target();
}

void j_000399A5(void)
{
	rva000399A5Target();
}

void j_0002F095(void)
{
	rva0002F095Target();
}

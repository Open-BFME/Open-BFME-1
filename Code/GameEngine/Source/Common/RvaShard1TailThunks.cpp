// cl: /O2 /MD
//
// Address-qualified incremental-link tail thunks.  Their independently
// matched destinations establish the jump routes; the no-argument forwarding
// declarations preserve the real receiver and arguments on the caller stack.

extern void rva0000EF5CTarget(void);
extern void rva000070B3Target(void);
extern void rva000078E7Target(void);
extern void rva0000CC3ETarget(void);
extern void rva0000A47ATarget(void);
extern void rva0000DFBCTarget(void);
extern void rva0000E43ATarget(void);
extern void rva000119E1Target(void);
extern void rva00022683Target(void);
extern void rva0002F095Target(void);
extern void rva000399A5Target(void);

#pragma comment(linker, "/alternatename:?rva0000EF5CTarget@@YAXXZ=??0PropagandaTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z")
#pragma comment(linker, "/alternatename:?rva000070B3Target@@YAXXZ=?PopulateLobbyPlayerListbox@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000078E7Target@@YAXXZ=??$__copy@PBVProductionPrerequisite@@PAV1@H@_STL@@YAPAVProductionPrerequisite@@PBV1@0PAV1@ABUrandom_access_iterator_tag@0@PAH@Z")
#pragma comment(linker, "/alternatename:?rva0000CC3ETarget@@YAXXZ=??0FlightDeckBehaviorModuleData@@QAE@XZ")
#pragma comment(linker, "/alternatename:?rva0000A47ATarget@@YAXXZ=?_M_insert_overflow@?$vector@UFlightDeckInfo@FlightDeckBehavior@@V?$allocator@UFlightDeckInfo@FlightDeckBehavior@@@_STL@@@_STL@@IAEXPAUFlightDeckInfo@FlightDeckBehavior@@ABU34@ABU__false_type@2@I_N@Z")
#pragma comment(linker, "/alternatename:?rva0000DFBCTarget@@YAXXZ=??0StatusBitsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z")
#pragma comment(linker, "/alternatename:?rva0000E43ATarget@@YAXXZ=?messageCallback@BuddyThreadClass@@QAEXPAVGPConnection@@PAUGPRecvBuddyMessageArg@@@Z")
#pragma comment(linker, "/alternatename:?rva000119E1Target@@YAXXZ=?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z")
#pragma comment(linker, "/alternatename:?rva00022683Target@@YAXXZ=?readDict@DataChunkInput@@QAE?AVDict@@XZ")
#pragma comment(linker, "/alternatename:?rva0002F095Target@@YAXXZ=?copy@UnsignedPairTreeCopyShim@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$$CBGE@_STL@@@2@PAU32@0@Z")
#pragma comment(linker, "/alternatename:?rva000399A5Target@@YAXXZ=?setOrientation@Thing@@QAEXM@Z")

void j_0000EF5C(void)
{
	rva0000EF5CTarget();
}

void j_000070B3(void)
{
	rva000070B3Target();
}

void j_000078E7(void)
{
	rva000078E7Target();
}

void j_0000CC3E(void)
{
	rva0000CC3ETarget();
}

void j_0000A47A(void)
{
	rva0000A47ATarget();
}

void j_0000DFBC(void)
{
	rva0000DFBCTarget();
}

void j_0000E43A(void)
{
	rva0000E43ATarget();
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

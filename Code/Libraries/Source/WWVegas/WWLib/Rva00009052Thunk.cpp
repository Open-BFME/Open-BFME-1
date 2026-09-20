// cl: /O2 /MD
//
// Retail RVA 0x00009052 is a five-byte incremental-link tail jump to
// 0x002EB770.  That destination is already matched as the address-derived
// STLport vector<Gen002E9E10>::_M_insert_overflow body.  Keep the thunk itself
// address-qualified: the no-argument forwarding declaration deliberately
// leaves the real member-function arguments untouched on the caller's stack.

extern void rva00009052Target(void);
extern void rva0000903ETarget(void);

#pragma comment(linker, "/alternatename:?rva00009052Target@@YAXXZ=?_M_insert_overflow@?$vector@UGen002E9E10@@V?$allocator@UGen002E9E10@@@_STL@@@_STL@@IAEXPAUGen002E9E10@@ABU3@ABU__false_type@2@I_N@Z")
#pragma comment(linker, "/alternatename:?rva0000903ETarget@@YAXXZ=?_M_clear@?$vector@UParticleSysBoneInfo@@V?$allocator@UParticleSysBoneInfo@@@_STL@@@_STL@@IAEXXZ")

// Retail RVA 0x0000903E is the adjacent five-byte tail jump to the independently
// matched ParticleSysBoneInfo vector clear body at 0x000A8170.
void j_0000903E(void)
{
	rva0000903ETarget();
}

void j_00009052(void)
{
	rva00009052Target();
}

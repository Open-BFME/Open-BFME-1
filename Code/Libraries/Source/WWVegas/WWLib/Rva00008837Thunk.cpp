// cl: /O2 /MD
//
// Retail RVA 0x00008837 is a five-byte incremental-link tail jump to the
// independently matched vector<W3DAnimationInfo>::_M_clear body at 0x003B0E90.
// The no-argument forwarding declaration preserves the real member receiver
// and any caller state while retaining an address-qualified thunk identity.

extern void rva00008837Target(void);

#pragma comment(linker, "/alternatename:?rva00008837Target@@YAXXZ=?_M_clear@?$vector@VW3DAnimationInfo@@V?$allocator@VW3DAnimationInfo@@@_STL@@@_STL@@IAEXXZ")

void j_00008837(void)
{
	rva00008837Target();
}

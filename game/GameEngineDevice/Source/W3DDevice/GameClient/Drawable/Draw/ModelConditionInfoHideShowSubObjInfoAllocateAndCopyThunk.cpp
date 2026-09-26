// ?Rva00030D69HideShowSubObjInfoAllocateAndCopyThunk@@YAXXZ
// Retail 0x00030D69 is a five-byte tail jump to the matched STLport body at
// 0x003B4C80.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva00030d69Target(void);

#pragma comment(linker, "/alternatename:?rva00030d69Target@@YAXXZ=??$_M_allocate_and_copy@PBUHideShowSubObjInfo@ModelConditionInfo@@@?$vector@UHideShowSubObjInfo@ModelConditionInfo@@V?$allocator@UHideShowSubObjInfo@ModelConditionInfo@@@_STL@@@_STL@@IAEPAUHideShowSubObjInfo@ModelConditionInfo@@IPBU23@0@Z")

void Rva00030D69HideShowSubObjInfoAllocateAndCopyThunk(void)
{
	rva00030d69Target();
}

// ?Rva000032A6HideShowSubObjInfoUninitializedCopyThunk@@YAXXZ
// Retail RVA 0x000032A6 is a five-byte ILT tail jump to the matched
// HideShowSubObjInfo uninitialized-copy body at RVA 0x003AA480.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva000032a6Target(void);

#pragma comment(linker, "/alternatename:?rva000032a6Target@@YAXXZ=??$__uninitialized_copy@PBUHideShowSubObjInfo@ModelConditionInfo@@PAU12@@_STL@@YAPAUHideShowSubObjInfo@ModelConditionInfo@@PBU12@0PAU12@ABU__false_type@0@@Z")

void Rva000032A6HideShowSubObjInfoUninitializedCopyThunk(void)
{
	rva000032a6Target();
}

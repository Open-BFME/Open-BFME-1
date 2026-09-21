// Retail RVA 0x000251D0 is a five-byte tail jump to the matched
// HideShowSubObjInfo vector insertion body at RVA 0x006A3DB0.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva000251D0Target(void);

#pragma comment(linker, "/alternatename:?rva000251D0Target@@YAXXZ=?_M_insert_overflow@?$vector@UHideShowSubObjInfo@ModelConditionInfo@@V?$allocator@UHideShowSubObjInfo@ModelConditionInfo@@@_STL@@@_STL@@IAEXPAUHideShowSubObjInfo@ModelConditionInfo@@ABU34@ABU__false_type@2@I_N@Z")

void Rva000251D0HideShowSubObjInfoInsertOverflowThunk(void)
{
	rva000251D0Target();
}

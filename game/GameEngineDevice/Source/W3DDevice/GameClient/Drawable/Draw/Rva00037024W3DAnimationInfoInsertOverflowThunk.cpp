// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// Retail RVA 0x00037024 is a five-byte jump to the matched
// W3DAnimationInfo vector overflow body at 0x00788030.

extern void rva00037024Target(void);

#pragma comment(linker, "/alternatename:?rva00037024Target@@YAXXZ=?_M_insert_overflow@?$vector@VW3DAnimationInfo@@V?$allocator@VW3DAnimationInfo@@@_STL@@@_STL@@IAEXPAVW3DAnimationInfo@@ABV3@ABU__false_type@2@I_N@Z")

void Rva00037024W3DAnimationInfoInsertOverflowThunk(void)
{
    rva00037024Target();
}

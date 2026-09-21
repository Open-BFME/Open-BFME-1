// ?Rva000181A1ProductionPrerequisiteCopyThunk@@YAXXZ
// Retail 0x000181A1 is a five-byte ILT tail jump to the matched
// ProductionPrerequisite __copy body at 0x00753280.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva000181a1Target(void);

#pragma comment(linker, "/alternatename:?rva000181a1Target@@YAXXZ=??$__copy@PAVProductionPrerequisite@@PAV1@H@_STL@@YAPAVProductionPrerequisite@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z")

void Rva000181A1ProductionPrerequisiteCopyThunk(void)
{
	rva000181a1Target();
}

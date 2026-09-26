// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

// Retail 0x0001819C is the ModuleInfo::Nugget __uninitialized_copy ILT.
// Its five-byte tail jump reaches the matched 0x0076B010 body.
extern void rva0001819cTarget(void);

#pragma comment(linker, "/alternatename:?rva0001819cTarget@@YAXXZ=??$__uninitialized_copy@PBURva0013B8F0Element@@PAU1@@_STL@@YAPAURva0013B8F0Element@@PBU1@0PAU1@ABU__false_type@0@@Z")

void Rva0001819CModuleInfoNuggetUninitializedCopyThunk(void)
{
	rva0001819cTarget();
}

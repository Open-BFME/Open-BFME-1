// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Retail 0x0000F277 is a five-byte incremental-link tail jump to the matched
// PrereqUnitRec vector overflow body at 0x00584650.
extern void rva0000f277Target(void);

#pragma comment(linker, "/alternatename:?rva0000f277Target@@YAXXZ=?insert_overflow@ProductionPrerequisitePrereqUnitRecInsertOverflowShim@_STL@@QAEXPAUPrereqUnitRec@ProductionPrerequisite@@ABU34@ABU__false_type@2@I_N@Z")

void Rva0000F277ProductionPrereqUnitRecInsertOverflowThunk(void)
{
	rva0000f277Target();
}

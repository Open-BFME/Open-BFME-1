// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SlaughterHordeContainModuleData scalar-deleting destructor at
// retail RVA 0x0022B1F0 (30 bytes). The exact constructor at 0x0022B160 and
// complete destructor at 0x0022B220 agree on the derived module-data layout.
// This wrapper calls the destructor through ILT 0x0000EF75.

class SlaughterHordeContainModuleData
{
public:
	virtual ~SlaughterHordeContainModuleData();

private:
	// This inline helper only materializes the vtable. Keep its private
	// spelling distinct from the public constructor owned by CtorThunk.cpp.
	SlaughterHordeContainModuleData() {}
	friend void forceSlaughterHordeContainModuleDataDeletingDestructor();
};

void forceSlaughterHordeContainModuleDataDeletingDestructor()
{
	SlaughterHordeContainModuleData value;
}

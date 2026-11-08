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
	friend void forceSlaughterHordeContainModuleDataDeletingDestructor(const SlaughterHordeContainModuleData &that);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceSlaughterHordeContainModuleDataDeletingDestructor(const SlaughterHordeContainModuleData &that)
{
	SlaughterHordeContainModuleData value(that);
}

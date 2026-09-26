// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for AODCrushCollideModuleData.
// The exact constructor at 0x00215B90 installs dedicated vtable 0x010A9740;
// slot zero routes through ILT 0x0003F8F0 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0000FC31.

class AODCrushCollideModuleData
{
public:
	virtual ~AODCrushCollideModuleData();
};

void forceAODCrushCollideModuleDataDeletingDestructor()
{
	AODCrushCollideModuleData value;
}

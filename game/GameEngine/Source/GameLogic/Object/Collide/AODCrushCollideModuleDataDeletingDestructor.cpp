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

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceAODCrushCollideModuleDataDeletingDestructor(const AODCrushCollideModuleData &that)
{
	AODCrushCollideModuleData value(that);
}

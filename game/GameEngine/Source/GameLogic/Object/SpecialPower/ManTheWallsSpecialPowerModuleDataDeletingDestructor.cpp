// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// ManTheWallsSpecialPowerModuleData. The exact constructor at 0x00261260
// installs dedicated vtable 0x010B5EA0; slot zero routes through ILT
// 0x00032AFB to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00016220.

// The destructor is implicit: retail ~ManTheWallsSpecialPowerModuleData at 0x002612B0 (own ILT 0x00016220) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class __declspec(novtable) SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class ManTheWallsSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceManTheWallsSpecialPowerModuleDataDeletingDestructor(const ManTheWallsSpecialPowerModuleData &that)
{
	ManTheWallsSpecialPowerModuleData value(that);
}

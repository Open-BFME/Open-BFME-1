// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// RepairSpecialPowerModuleData. The exact constructor at 0x00264990 installs
// dedicated vtable 0x010B6B10; slot zero routes through ILT 0x0000BAAF to
// this 30-byte wrapper. The wrapper calls the complete destructor through
// ILT 0x00004AAC.

// The destructor is implicit: retail ~RepairSpecialPowerModuleData at 0x002649E0 (own ILT 0x00004AAC) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class RepairSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceRepairSpecialPowerModuleDataDeletingDestructor(const RepairSpecialPowerModuleData &that)
{
	RepairSpecialPowerModuleData value(that);
}

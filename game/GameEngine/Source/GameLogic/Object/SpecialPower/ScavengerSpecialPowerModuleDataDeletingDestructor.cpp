// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// ScavengerSpecialPowerModuleData. The exact constructor at 0x00265A80
// installs dedicated vtable 0x010B6FF8; slot zero routes through ILT
// 0x000314B7 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00025577.

// The destructor is implicit: retail ~ScavengerSpecialPowerModuleData at 0x00265AE0 (own ILT 0x00025577) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class ScavengerSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceScavengerSpecialPowerModuleDataDeletingDestructor(const ScavengerSpecialPowerModuleData &that)
{
	ScavengerSpecialPowerModuleData value(that);
}

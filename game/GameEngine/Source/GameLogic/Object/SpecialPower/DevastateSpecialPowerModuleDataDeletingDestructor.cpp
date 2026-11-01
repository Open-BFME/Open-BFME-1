// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// DevastateSpecialPowerModuleData. The exact constructor at 0x0025AC10
// installs dedicated vtable 0x010B47C8; slot zero routes through ILT
// 0x00034897 to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00032E25.

// The destructor is implicit: retail ~DevastateSpecialPowerModuleData at 0x0025AC80 (own ILT 0x00032E25) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class DevastateSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceDevastateSpecialPowerModuleDataDeletingDestructor(const DevastateSpecialPowerModuleData &that)
{
	DevastateSpecialPowerModuleData value(that);
}

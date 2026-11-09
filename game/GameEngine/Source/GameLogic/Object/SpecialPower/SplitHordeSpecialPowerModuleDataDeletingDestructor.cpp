// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// SplitHordeSpecialPowerModuleData. The exact constructor at 0x0026B1D0
// installs dedicated vtable 0x010B80E8; slot zero routes through ILT
// 0x0000C8AB to this 30-byte wrapper. The wrapper calls the complete
// destructor through ILT 0x00018AC0.

// The destructor is implicit: retail ~SplitHordeSpecialPowerModuleData at 0x0026B220 (own ILT 0x00018AC0) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class __declspec(novtable) SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class SplitHordeSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceSplitHordeSpecialPowerModuleDataDeletingDestructor(const SplitHordeSpecialPowerModuleData &that)
{
	SplitHordeSpecialPowerModuleData value(that);
}

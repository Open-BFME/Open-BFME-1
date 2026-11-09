// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// CombineHordeSpecialPowerModuleData. The exact constructor at 0x002598A0
// installs dedicated vtable 0x010B3EC8; slot zero routes through ILT
// 0x0002A072 to this 30-byte wrapper. The wrapper calls the derived complete
// destructor through ILT 0x0000B37F.

// The destructor is implicit: retail ~CombineHordeSpecialPowerModuleData at 0x00259900 (own ILT 0x0000B37F) is a
// bare tail jump to SpecialPowerModuleData::~SpecialPowerModuleData (ILT 0x0001D7B4) with no vptr reset, the
// shape VC7.1 gives an implicit virtual destructor; both ILTs are
// ilt_oracle CONFIRMED exact.

class __declspec(novtable) SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class CombineHordeSpecialPowerModuleData : public SpecialPowerModuleData
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceCombineHordeSpecialPowerModuleDataDeletingDestructor(const CombineHordeSpecialPowerModuleData &that)
{
	CombineHordeSpecialPowerModuleData value(that);
}

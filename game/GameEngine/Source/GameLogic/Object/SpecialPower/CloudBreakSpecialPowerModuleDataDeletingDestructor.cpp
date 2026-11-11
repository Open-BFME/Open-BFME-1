// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for CloudBreakSpecialPowerModuleData.
// The exact constructor at 0x002592A0 installs dedicated vtable 0x010B3CD8;
// slot zero routes through ILT 0x0003D861 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0001F76C.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva00259320 (0x00259320, defined in
// Q4PairSubobjectDtors.cpp) rather than a CloudBreakSpecialPowerModuleData
// complete destructor nothing defines. An explicit empty derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
class Rva00259320
{
public:
	~Rva00259320();
};

class CloudBreakSpecialPowerModuleData : public Rva00259320
{
public:
	virtual ~CloudBreakSpecialPowerModuleData();
};

// ??1CloudBreakSpecialPowerModuleData@@UAE@XZ present-unmatched
CloudBreakSpecialPowerModuleData::~CloudBreakSpecialPowerModuleData()
{
}

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceCloudBreakSpecialPowerModuleDataDeletingDestructor(const CloudBreakSpecialPowerModuleData &that)
{
	CloudBreakSpecialPowerModuleData value(that);
}

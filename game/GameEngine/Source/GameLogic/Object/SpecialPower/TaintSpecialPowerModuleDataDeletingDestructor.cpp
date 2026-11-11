// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// TaintSpecialPowerModuleData. The exact constructor at 0x0026B870 installs
// dedicated vtable 0x010B8550; slot zero routes through ILT 0x0002C025 to
// this 30-byte wrapper. The wrapper calls the complete destructor through
// ILT 0x0000A187.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva0026B8E0 (0x0026B8E0, defined in
// Q4PairSubobjectDtors.cpp) rather than a TaintSpecialPowerModuleData
// complete destructor nothing defines. An explicit empty derived destructor
// inlines into the generated ??_G wrapper, leaving the direct base call.
class Rva0026B8E0
{
public:
	~Rva0026B8E0();
};

class TaintSpecialPowerModuleData : public Rva0026B8E0
{
public:
	virtual ~TaintSpecialPowerModuleData();
};

// ??1TaintSpecialPowerModuleData@@UAE@XZ present-unmatched
TaintSpecialPowerModuleData::~TaintSpecialPowerModuleData()
{
}

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceTaintSpecialPowerModuleDataDeletingDestructor(const TaintSpecialPowerModuleData &that)
{
	TaintSpecialPowerModuleData value(that);
}

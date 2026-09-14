// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for
// TaintSpecialPowerModuleData. The exact constructor at 0x0026B870 installs
// dedicated vtable 0x010B8550; slot zero routes through ILT 0x0002C025 to
// this 30-byte wrapper. The wrapper calls the complete destructor through
// ILT 0x0000A187.

class TaintSpecialPowerModuleData
{
public:
	virtual ~TaintSpecialPowerModuleData();
};

void forceTaintSpecialPowerModuleDataDeletingDestructor()
{
	TaintSpecialPowerModuleData value;
}

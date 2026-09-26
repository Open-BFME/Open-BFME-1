// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for HeroDieModuleData.
// The exact constructor at 0x00255600 installs dedicated vtable 0x010B3010;
// slot zero routes through ILT 0x000253EC to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00026F67.

class HeroDieModuleData
{
public:
	virtual ~HeroDieModuleData();
};

void forceHeroDieModuleDataDeletingDestructor()
{
	HeroDieModuleData value;
}

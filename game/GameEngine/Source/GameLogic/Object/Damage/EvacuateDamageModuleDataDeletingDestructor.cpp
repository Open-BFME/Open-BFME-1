// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for EvacuateDamageModuleData.
// The exact constructor at 0x00250C20 installs dedicated vtable 0x010B2018;
// slot zero routes through ILT 0x000076A8 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x00004BD8.

class EvacuateDamageModuleData
{
public:
	virtual ~EvacuateDamageModuleData();
};

void forceEvacuateDamageModuleDataDeletingDestructor()
{
	EvacuateDamageModuleData value;
}

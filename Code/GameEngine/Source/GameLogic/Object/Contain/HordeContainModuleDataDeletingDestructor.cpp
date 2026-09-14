// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for HordeContainModuleData.
// The exact constructor at 0x00220530 installs dedicated vtable 0x010ABCF8;
// slot zero routes through ILT 0x0002131E to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x000100AF.

class HordeContainModuleData
{
public:
	virtual ~HordeContainModuleData();
};

void forceHordeContainModuleDataDeletingDestructor()
{
	HordeContainModuleData value;
}

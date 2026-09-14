// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CreateObjectDieModuleData scalar-deleting destructor at retail
// RVA 0x00254870 (30 bytes). The exact constructor at 0x002547E0, complete
// destructor at 0x002548A0, module-data factory, and field parser establish
// the class. The wrapper calls the destructor through ILT 0x00016031.

class CreateObjectDieModuleData
{
public:
	virtual ~CreateObjectDieModuleData();
};

void forceCreateObjectDieModuleDataDeletingDestructor()
{
	CreateObjectDieModuleData value;
}

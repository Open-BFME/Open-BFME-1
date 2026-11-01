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

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceCreateObjectDieModuleDataDeletingDestructor(const CreateObjectDieModuleData &that)
{
	CreateObjectDieModuleData value(that);
}

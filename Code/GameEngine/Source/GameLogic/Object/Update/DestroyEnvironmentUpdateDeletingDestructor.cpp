// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DestroyEnvironmentUpdate scalar-deleting destructor at retail
// RVA 0x0028D090 (30 bytes). Its exact constructor at 0x0028CD70, canonical
// complete destructor at 0x0028CFB0, factories, module name, and update method
// establish the class. The destructor ILT is 0x00007257.

class DestroyEnvironmentUpdate
{
public:
	virtual ~DestroyEnvironmentUpdate();
};

void forceDestroyEnvironmentUpdateDeletingDestructor()
{
	DestroyEnvironmentUpdate value;
}

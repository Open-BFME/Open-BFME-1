// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ObjectHelper scalar-deleting destructor at retail RVA 0x001C0E70
// (30 bytes). Its exact constructor at 0x001C0DB0 installs the primary,
// BehaviorModuleInterface, and UpdateModuleInterface vtables, and the recovered
// helper hierarchy corroborates the class. The wrapper calls the complete
// destructor through ILT 0x0002514E before conditionally invoking delete.

class ObjectHelper
{
public:
	virtual ~ObjectHelper();
};

void forceObjectHelperDeletingDestructor()
{
	ObjectHelper value;
}

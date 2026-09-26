// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LoadGameFadeWrapper scalar-deleting destructor at retail RVA
// 0x003BE940 (30 bytes). Vtable 0x010EDB7C slot zero reaches this wrapper
// through ILT 0x000180F7, while slot one and recovered timed-operation callers
// establish the concrete callback wrapper. Its complete destructor is reached
// through ILT 0x0001EE20.

class LoadGameFadeWrapper
{
public:
	virtual ~LoadGameFadeWrapper();
};

void forceLoadGameFadeWrapperDeletingDestructor()
{
	LoadGameFadeWrapper value;
}

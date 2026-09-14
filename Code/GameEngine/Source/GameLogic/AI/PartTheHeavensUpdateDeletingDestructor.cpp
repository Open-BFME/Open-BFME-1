// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: PartTheHeavensUpdate scalar-deleting destructor at retail RVA
// 0x00299A50 (30 bytes). Its exact constructor at 0x002999D0, complete
// destructor at 0x00299820, factories, and module name establish the class.
// The wrapper calls the destructor through ILT 0x0000806C.

class PartTheHeavensUpdate
{
public:
	virtual ~PartTheHeavensUpdate();
};

void forcePartTheHeavensUpdateDeletingDestructor()
{
	PartTheHeavensUpdate value;
}

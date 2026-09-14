// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: FoundationAIUpdate scalar-deleting destructor at retail RVA
// 0x002BA130 (30 bytes). Its exact constructor at 0x002BA040, complete
// destructor at 0x002B9D60, unique factories, module name, handler, and
// vtable 0x00CC734C establish the class. The destructor ILT is 0x0000E791.

class FoundationAIUpdate
{
public:
	virtual ~FoundationAIUpdate();
};

void forceFoundationAIUpdateDeletingDestructor()
{
	FoundationAIUpdate value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DozerAIUpdate scalar-deleting destructor at retail RVA
// 0x002B6B50 (30 bytes).  The exact instance constructor at 0x002B8680
// installs primary vtable 0x010C6A90, whose slot zero reaches this wrapper
// through ILT 0x00026BED.  The complete destructor at 0x002B6640 is reached
// through ILT 0x0001E092; the Dozer factory, pool glue, and recovered method
// family independently establish the class identity.

class DozerAIUpdate
{
public:
	virtual ~DozerAIUpdate();
};

void forceDozerAIUpdateDeletingDestructor()
{
	DozerAIUpdate value;
}

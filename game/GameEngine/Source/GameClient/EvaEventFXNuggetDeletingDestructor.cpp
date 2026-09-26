// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for EvaEventFXNugget.
// Vtable 0x00CF33C0 slots name this class (?doFXObj@EvaEventFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x0003EDDD to this 30-byte wrapper, whose complete destructor
// route ILT 0x000231C3 reaches cleanup body 0x00427390.

class EvaEventFXNugget
{
protected:
	virtual ~EvaEventFXNugget();
private:
	friend void forceEvaEventFXNuggetDeletingDestructor();
};

void forceEvaEventFXNuggetDeletingDestructor()
{
	EvaEventFXNugget value;
}

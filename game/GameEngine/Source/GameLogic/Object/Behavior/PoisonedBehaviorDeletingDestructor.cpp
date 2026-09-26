// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PoisonedBehavior.
// Vtable 0x00CA554C slots name this class (?getClassMemoryPool@PoisonedBehavior@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00025D51 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00009BEC reaches cleanup body 0x002028E0.

class PoisonedBehavior
{
protected:
	virtual ~PoisonedBehavior();
private:
	friend void forcePoisonedBehaviorDeletingDestructor();
};

void forcePoisonedBehaviorDeletingDestructor()
{
	PoisonedBehavior value;
}

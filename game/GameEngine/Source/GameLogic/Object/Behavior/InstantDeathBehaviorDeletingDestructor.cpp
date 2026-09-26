// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for InstantDeathBehavior.
// Vtable 0x00CA4EBC slots name this class (?getClassMemoryPool@InstantDeathBehavior@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00006447 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003401D reaches cleanup body 0x00200870.

class InstantDeathBehavior
{
protected:
	virtual ~InstantDeathBehavior();
private:
	friend void forceInstantDeathBehaviorDeletingDestructor();
};

void forceInstantDeathBehaviorDeletingDestructor()
{
	InstantDeathBehavior value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BridgeTowerBehavior.
// Vtable 0x00CA2B54 slots name this class (?getClassMemoryPool@BridgeTowerBehavior@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00012E68 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00012F44 reaches cleanup body 0x001F5F70.

class BridgeTowerBehavior
{
protected:
	virtual ~BridgeTowerBehavior();
private:
	friend void forceBridgeTowerBehaviorDeletingDestructor();
};

void forceBridgeTowerBehaviorDeletingDestructor()
{
	BridgeTowerBehavior value;
}

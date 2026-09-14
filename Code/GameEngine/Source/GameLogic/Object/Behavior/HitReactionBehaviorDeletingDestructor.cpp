// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HitReactionBehavior.
// Vtable 0x00CA4CB4 slots name this class (?getModuleNameKey@HitReactionBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0003046D to this 30-byte wrapper, whose complete destructor
// route ILT 0x00041704 reaches cleanup body 0x00200160.

class HitReactionBehavior
{
protected:
	virtual ~HitReactionBehavior();
private:
	friend void forceHitReactionBehaviorDeletingDestructor();
};

void forceHitReactionBehaviorDeletingDestructor()
{
	HitReactionBehavior value;
}

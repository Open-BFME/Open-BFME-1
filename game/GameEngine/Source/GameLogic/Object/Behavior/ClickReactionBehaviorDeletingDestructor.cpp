// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ClickReactionBehavior.
// Vtable 0x00CA33CC slots name this class (?getModuleNameKey@ClickReactionBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x000125DF to this 30-byte wrapper, whose complete destructor
// route ILT 0x00013B6F reaches cleanup body 0x001F7790.

class ClickReactionBehavior
{
protected:
	virtual ~ClickReactionBehavior();
private:
	friend void forceClickReactionBehaviorDeletingDestructor();
};

void forceClickReactionBehaviorDeletingDestructor()
{
	ClickReactionBehavior value;
}

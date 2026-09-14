// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIHarvestPrepareSiteState.
// Vtable 0x00C96770 slots name this class (?update@AIHarvestPrepareSiteState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00003E6D to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002DECF reaches cleanup body 0x000A1B30.

class AIHarvestPrepareSiteState
{
protected:
	virtual ~AIHarvestPrepareSiteState();
private:
	friend void forceAIHarvestPrepareSiteStateDeletingDestructor();
};

void forceAIHarvestPrepareSiteStateDeletingDestructor()
{
	AIHarvestPrepareSiteState value;
}

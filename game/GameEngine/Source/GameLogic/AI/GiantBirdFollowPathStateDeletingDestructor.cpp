// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for GiantBirdFollowPathState.
// Vtable 0x00CC7778 slots name this class (?onEnter@GiantBirdFollowPathState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0000BDF7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002824A reaches cleanup body 0x00172430.

class GiantBirdFollowPathState
{
protected:
	virtual ~GiantBirdFollowPathState();
private:
	friend void forceGiantBirdFollowPathStateDeletingDestructor();
};

void forceGiantBirdFollowPathStateDeletingDestructor()
{
	GiantBirdFollowPathState value;
}

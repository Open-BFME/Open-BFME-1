// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DozerActionPickActionPosState.
// Vtable 0x00CC6D28 slots name this class (?update@DozerActionPickActionPosState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x000359B8 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00010AB4 reaches cleanup body 0x000A1B30.

class DozerActionPickActionPosState
{
protected:
	virtual ~DozerActionPickActionPosState();
private:
	friend void forceDozerActionPickActionPosStateDeletingDestructor();
};

void forceDozerActionPickActionPosStateDeletingDestructor()
{
	DozerActionPickActionPosState value;
}

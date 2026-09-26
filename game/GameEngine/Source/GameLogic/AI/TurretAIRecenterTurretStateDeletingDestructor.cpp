// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TurretAIRecenterTurretState.
// Vtable 0x00C9BDC0 slots name this class (?update@TurretAIRecenterTurretState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00030F9E to this 30-byte wrapper, whose complete destructor
// route ILT 0x000319C1 reaches cleanup body 0x000A1B30.

class TurretAIRecenterTurretState
{
protected:
	virtual ~TurretAIRecenterTurretState();
private:
	friend void forceTurretAIRecenterTurretStateDeletingDestructor();
};

void forceTurretAIRecenterTurretStateDeletingDestructor()
{
	TurretAIRecenterTurretState value;
}

// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIAttackMeleeHordeWaitPathState.
// Vtable 0x00C97BE0 slots name this class (?update@AIAttackMeleeHordeWaitPathState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x0002A3CE to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002200C reaches cleanup body 0x000A1B30.

class AIAttackMeleeHordeWaitPathState
{
protected:
	virtual ~AIAttackMeleeHordeWaitPathState();
private:
	friend void forceAIAttackMeleeHordeWaitPathStateDeletingDestructor();
};

void forceAIAttackMeleeHordeWaitPathStateDeletingDestructor()
{
	AIAttackMeleeHordeWaitPathState value;
}

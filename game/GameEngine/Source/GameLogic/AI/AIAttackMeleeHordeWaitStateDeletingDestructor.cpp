// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIAttackMeleeHordeWaitState.
// Vtable 0x00C97B68 slots name this class (?onEnter@AIAttackMeleeHordeWaitState@@UAE?AW4StateReturnType@@XZ); its slot zero routes
// through ILT 0x00012B1B to this 30-byte wrapper, whose complete destructor
// route ILT 0x00041C68 reaches cleanup body 0x000A1B30.

class AIAttackMeleeHordeWaitState
{
protected:
	virtual ~AIAttackMeleeHordeWaitState();
private:
	friend void forceAIAttackMeleeHordeWaitStateDeletingDestructor();
};

void forceAIAttackMeleeHordeWaitStateDeletingDestructor()
{
	AIAttackMeleeHordeWaitState value;
}

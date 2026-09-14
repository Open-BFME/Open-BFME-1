// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ScoreScaleUpTransition.
// Vtable 0x00D0CB30 slots name this class (?init@ScoreScaleUpTransition@@UAEXPAVGameWindow@@@Z and ?draw@ScoreScaleUpTransition@@UAEXXZ); its slot zero routes
// through ILT 0x00035A85 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00023C2C reaches cleanup body 0x0059F340.

class ScoreScaleUpTransition
{
protected:
	virtual ~ScoreScaleUpTransition();
private:
	friend void forceScoreScaleUpTransitionDeletingDestructor();
};

void forceScoreScaleUpTransitionDeletingDestructor()
{
	ScoreScaleUpTransition value;
}

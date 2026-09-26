// cl: /DNDEBUG /MD /EHsc
// ScoreKeeper::loadPostProcess, retail 0x000E9B00: slot 1 of ScoreKeeper's
// vftable 0x01084DF0, BFME's Snapshot loadPostProcess slot. Zero Hour's body
// is empty; ScoreKeeper.h declares it protected.
class ScoreKeeper
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@ScoreKeeper@@MAEXXZ
void ScoreKeeper::loadPostProcess(void)
{
}  // end loadPostProcess

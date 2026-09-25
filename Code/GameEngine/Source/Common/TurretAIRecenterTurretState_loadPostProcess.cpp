// cl: /DNDEBUG /MD /EHsc
// TurretAIRecenterTurretState::loadPostProcess, retail 0x0018DAC0: slot 1 of TurretAIRecenterTurretState's vftable
// 0x0109bdc0, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class TurretAIRecenterTurretState
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@TurretAIRecenterTurretState@@MAEXXZ
void TurretAIRecenterTurretState::loadPostProcess(void)
{
}  // end loadPostProcess

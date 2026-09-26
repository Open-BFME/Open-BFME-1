// cl: /DNDEBUG /MD /EHsc
// FailureState::loadPostProcess, retail 0x00170E70: slot 1 of FailureState's vftable
// 0x01097950, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class FailureState
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@FailureState@@MAEXXZ
void FailureState::loadPostProcess(void)
{
}  // end loadPostProcess

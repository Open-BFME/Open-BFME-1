// cl: /DNDEBUG /MD /EHsc
// AIDockWaitForClearanceState::loadPostProcess, retail 0x0014F470: slot 1 of AIDockWaitForClearanceState's vftable
// 0x01095bf0, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class AIDockWaitForClearanceState
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@AIDockWaitForClearanceState@@MAEXXZ
void AIDockWaitForClearanceState::loadPostProcess(void)
{
}  // end loadPostProcess

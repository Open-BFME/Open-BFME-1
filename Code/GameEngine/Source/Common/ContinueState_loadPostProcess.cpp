// cl: /DNDEBUG /MD /EHsc
// ContinueState::loadPostProcess, retail 0x00170F00: slot 1 of ContinueState's vftable
// 0x010979b8, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class ContinueState
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@ContinueState@@MAEXXZ
void ContinueState::loadPostProcess(void)
{
}  // end loadPostProcess

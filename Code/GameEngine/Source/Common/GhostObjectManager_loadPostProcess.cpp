// cl: /DNDEBUG /MD /EHsc
// GhostObjectManager::loadPostProcess, retail 0x001B3AD0: slot 1 of GhostObjectManager's vftable
// 0x0109ce28, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class GhostObjectManager
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@GhostObjectManager@@MAEXXZ
void GhostObjectManager::loadPostProcess(void)
{
}  // end loadPostProcess

// cl: /DNDEBUG /MD /EHsc
// W3DGhostObjectManager::loadPostProcess, retail 0x006BCA60: slot 1 of W3DGhostObjectManager's vftable
// 0x0111cfe0, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class W3DGhostObjectManager
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@W3DGhostObjectManager@@MAEXXZ
void W3DGhostObjectManager::loadPostProcess(void)
{
}  // end loadPostProcess

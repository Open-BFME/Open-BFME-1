// cl: /DNDEBUG /MD /EHsc
// ResourceGatheringManager::loadPostProcess, retail 0x000E6120: slot 1 of ResourceGatheringManager's vftable
// 0x01084c40, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class ResourceGatheringManager
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@ResourceGatheringManager@@MAEXXZ
void ResourceGatheringManager::loadPostProcess(void)
{
}  // end loadPostProcess

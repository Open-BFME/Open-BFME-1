// cl: /DNDEBUG /MD /EHsc
// GhostObject::loadPostProcess, retail 0x001B3DD0: slot 1 of GhostObject's vftable
// 0x0109ce94, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class GhostObject
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@GhostObject@@MAEXXZ
void GhostObject::loadPostProcess(void)
{
}  // end loadPostProcess

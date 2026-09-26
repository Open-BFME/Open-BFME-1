// cl: /DNDEBUG /MD /EHsc
// W3DTerrainVisualBase::loadPostProcess, retail 0x00602D00: slot 1 of W3DTerrainVisualBase's vftable
// 0x011150b8, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class W3DTerrainVisualBase
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@W3DTerrainVisualBase@@MAEXXZ
void W3DTerrainVisualBase::loadPostProcess(void)
{
}  // end loadPostProcess

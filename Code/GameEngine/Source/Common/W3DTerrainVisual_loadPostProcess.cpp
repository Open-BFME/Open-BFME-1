// cl: /DNDEBUG /MD /EHsc
// W3DTerrainVisual::loadPostProcess, retail 0x00731010: slot 1 of W3DTerrainVisual's vftable
// 0x011212f0, BFME's Snapshot loadPostProcess slot. The retail body is a lone
// ret; Zero Hour declares the method protected.
class W3DTerrainVisual
{
protected:
	virtual void loadPostProcess(void);
};

// ?loadPostProcess@W3DTerrainVisual@@MAEXXZ
void W3DTerrainVisual::loadPostProcess(void)
{
}  // end loadPostProcess

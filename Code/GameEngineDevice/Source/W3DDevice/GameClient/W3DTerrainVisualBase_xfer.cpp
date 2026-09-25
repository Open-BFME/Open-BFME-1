// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
// W3DTerrainVisualBase::xfer, retail 0x00602C40 (27 bytes). The only vftable
// holding it is W3DTerrainVisualBase's 0x011150B8, in slot 3 (BFME's Snapshot
// xfer slot), and W3DTerrainVisual::xfer (0x007318A0) calls it first as its
// base-class xfer. It is Zero Hour's TerrainVisual::xfer: version 1 and
// nothing else.
#include "xfer.h"

class W3DTerrainVisualBase
{
protected:
	virtual void xfer(Xfer *xfer);
};

// ?xfer@W3DTerrainVisualBase@@MAEXPAVXfer@@@Z
void W3DTerrainVisualBase::xfer(Xfer *xfer)
{
	// version
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	*xfer == version;
}

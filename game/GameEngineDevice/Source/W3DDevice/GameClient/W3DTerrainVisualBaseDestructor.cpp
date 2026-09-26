// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// BFME's TerrainVisual base is Snapshot + SubsystemInterface followed by the
// filename string.  The empty body is the Generals/Zero Hour source shape;
// the implicit destruction order produces the filename release, secondary
// base destruction, and final Snapshot vtable restoration seen in retail.
class Xfer;

#include "ascii_string.h"

class BfmeSnapshotBase
{
public:
	~BfmeSnapshotBase() {}

protected:
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;

private:
	AsciiString m_name;
};

class W3DTerrainVisualBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	virtual ~W3DTerrainVisualBase();

private:
	AsciiString m_filenameString;
};

// ??1W3DTerrainVisualBase@@UAE@XZ
W3DTerrainVisualBase::~W3DTerrainVisualBase()
{
}

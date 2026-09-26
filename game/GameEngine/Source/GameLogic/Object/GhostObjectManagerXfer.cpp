#include "../../Common/System/xfer.h"

class __declspec(novtable) GhostObjectManager
{
public:
	virtual ~GhostObjectManager();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
	int m_localPlayer;
};

void GhostObjectManager::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 1;
	*xfer == version;
	xfer->xferInt(&m_localPlayer);
}

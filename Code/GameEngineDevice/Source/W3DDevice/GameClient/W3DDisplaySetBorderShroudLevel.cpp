// cl: /DNDEBUG /MD /EHsc

class BaseHeightMapResetShroud
{
public:
	void notifyShroudChanged30B8();
	void notifyShroudChanged30BC();
	void setBorderShroudLevel30B8(unsigned char level);
	void setBorderShroudLevel30BC(unsigned char level);
	void setShroudLevel30B8(int x, int y, unsigned char level, bool immediate);
	void setShroudLevel30BC(int x, int y, unsigned char level, bool immediate);
};

class BaseHeightMapRenderObjClass
{
private:
	unsigned char m_unmodelled_00[0x30b8];
	BaseHeightMapResetShroud *m_shroud;
	BaseHeightMapResetShroud *m_shroud30BC;

public:
	BaseHeightMapResetShroud *getShroud() const
	{
		return m_shroud;
	}

	BaseHeightMapResetShroud *getShroud30BC() const
	{
		return m_shroud30BC;
	}

	__declspec(noinline) void notifyShroudChanged006e();
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class GlobalData
{
private:
	unsigned char m_unmodelled_00[0xc84];

public:
	unsigned char m_clearAlpha;
	unsigned char m_fogAlpha;
	unsigned char m_shroudAlpha;
};

extern GlobalData *TheWritableGlobalData;

class BfmeTaintManager
{
public:
	unsigned char getTaintLevelByte006e(int x, int y);
};

extern BfmeTaintManager *TheTaintManager;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class W3DDisplay
{
public:
	virtual void setBorderShroudLevel(unsigned char level);
	virtual void setBorderShroudLevel30BC(unsigned char level);
	virtual void setShroudLevel(int x, int y, CellShroudStatus setting);
	virtual void setShroudLevel30BC(int x, int y, int level);
};

// ?notifyShroudChanged006e@BaseHeightMapRenderObjClass@@QAEXXZ
__declspec(noinline) void BaseHeightMapRenderObjClass::notifyShroudChanged006e()
{
	BaseHeightMapResetShroud *shroud30BC =
		*(BaseHeightMapResetShroud **)((unsigned char *)this + 0x309c);
	if (shroud30BC) {
		shroud30BC->notifyShroudChanged30BC();
	}
	BaseHeightMapResetShroud *shroud30B8 =
		*(BaseHeightMapResetShroud **)((unsigned char *)this + 0x3098);
	if (shroud30B8) {
		shroud30B8->notifyShroudChanged30B8();
	}
}

// ?setBorderShroudLevel@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud()) {
		TheTerrainRenderObject->getShroud()->setBorderShroudLevel30B8(level);
	}
}

// ?setBorderShroudLevel30BC@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel30BC(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud30BC()) {
		TheTerrainRenderObject->getShroud30BC()->setBorderShroudLevel30BC(level);
	}
}

// ?setShroudLevel30BC@W3DDisplay@@UAEXHHH@Z
void W3DDisplay::setShroudLevel30BC(int x, int y, int level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud30BC()) {
		TheTerrainRenderObject->getShroud30BC()->setShroudLevel30BC(
			x, y, static_cast<unsigned char>(level), false);
	}
}

// ?setShroudLevel@W3DDisplay@@UAEXHHW4CellShroudStatus@@@Z
void W3DDisplay::setShroudLevel(int x, int y, CellShroudStatus setting)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud()) {
		if (setting == CELLSHROUD_SHROUDED) {
			TheTerrainRenderObject->getShroud()->setShroudLevel30B8(
				x, y, TheWritableGlobalData->m_shroudAlpha, false);
		} else if (setting == CELLSHROUD_FOGGED) {
			TheTerrainRenderObject->getShroud()->setShroudLevel30B8(
				x, y, TheWritableGlobalData->m_fogAlpha, false);
		} else {
			TheTerrainRenderObject->getShroud()->setShroudLevel30B8(
				x, y, TheWritableGlobalData->m_clearAlpha, false);
		}

		TheTerrainRenderObject->notifyShroudChanged006e();
		BaseHeightMapResetShroud *shroud30BC = TheTerrainRenderObject->getShroud30BC();
		if (shroud30BC && TheTaintManager) {
			shroud30BC->setShroudLevel30BC(
				x, y, TheTaintManager->getTaintLevelByte006e(x, y), true);
		}
	}
}

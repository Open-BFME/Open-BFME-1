// cl: /DNDEBUG /MD /EHsc
// readable body of ?setBorderShroudLevel@W3DDisplay@@UAEXE@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?setShroudLevel@W3DDisplay@@UAEXHHW4CellShroudStatus@@@Z: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

class W3DShroud
{
public:
	void setBorderShroudLevel(unsigned char level);
	void setShroudLevel(int x, int y, unsigned char level, bool textureOnly);
};

class TaintBuffer
{
public:
	void setBorderShroudLevel(unsigned char level);
	void setShroudLevel(int x, int y, unsigned char level, bool textureOnly);
};

class W3DPropBuffer
{
public:
	void notifyShroudChanged();
};

class W3DShrubBuffer
{
public:
	void stampShroudVisible();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
private:
	unsigned char m_unmodelled_00[0x30b8];
	W3DShroud *m_shroud;
	TaintBuffer *m_taintBuffer;

public:
	W3DShroud *getShroud() const
	{
		return m_shroud;
	}

	TaintBuffer *getTaintBuffer() const
	{
		return m_taintBuffer;
	}

	__declspec(noinline) void notifyShroudChanged();
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	virtual void setBorderShroudLevel(unsigned char level);
	virtual void setBorderShroudLevel30BC(unsigned char level);
	virtual void setShroudLevel(int x, int y, CellShroudStatus setting);
	virtual void setShroudLevel30BC(int x, int y, int level);
};

// ?notifyShroudChanged@BaseHeightMapRenderObjClass@@QAEXXZ
__declspec(noinline) void BaseHeightMapRenderObjClass::notifyShroudChanged()
{
	W3DPropBuffer *propBuffer =
		*(W3DPropBuffer **)((unsigned char *)this + 0x309c);
	if (propBuffer) {
		propBuffer->notifyShroudChanged();
	}
	W3DShrubBuffer *shrubBuffer =
		*(W3DShrubBuffer **)((unsigned char *)this + 0x3098);
	if (shrubBuffer) {
		shrubBuffer->stampShroudVisible();
	}
}

// ?setBorderShroudLevel@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud()) {
		TheTerrainRenderObject->getShroud()->setBorderShroudLevel(level);
	}
}

// ?setBorderShroudLevel30BC@W3DDisplay@@UAEXE@Z
void W3DDisplay::setBorderShroudLevel30BC(unsigned char level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getTaintBuffer()) {
		TheTerrainRenderObject->getTaintBuffer()->setBorderShroudLevel(level);
	}
}

// ?setShroudLevel30BC@W3DDisplay@@UAEXHHH@Z
void W3DDisplay::setShroudLevel30BC(int x, int y, int level)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getTaintBuffer()) {
		TheTerrainRenderObject->getTaintBuffer()->setShroudLevel(
			x, y, static_cast<unsigned char>(level), false);
	}
}

// ?setShroudLevel@W3DDisplay@@UAEXHHW4CellShroudStatus@@@Z
void W3DDisplay::setShroudLevel(int x, int y, CellShroudStatus setting)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getShroud()) {
		if (setting == CELLSHROUD_SHROUDED) {
			TheTerrainRenderObject->getShroud()->setShroudLevel(
				x, y, TheWritableGlobalData->m_shroudAlpha, false);
		} else if (setting == CELLSHROUD_FOGGED) {
			TheTerrainRenderObject->getShroud()->setShroudLevel(
				x, y, TheWritableGlobalData->m_fogAlpha, false);
		} else {
			TheTerrainRenderObject->getShroud()->setShroudLevel(
				x, y, TheWritableGlobalData->m_clearAlpha, false);
		}

		TheTerrainRenderObject->notifyShroudChanged();
		TaintBuffer *taintBuffer = TheTerrainRenderObject->getTaintBuffer();
		if (taintBuffer && TheTaintManager) {
			taintBuffer->setShroudLevel(
				x, y, TheTaintManager->getTaintLevelByte006e(x, y), true);
		}
	}
}

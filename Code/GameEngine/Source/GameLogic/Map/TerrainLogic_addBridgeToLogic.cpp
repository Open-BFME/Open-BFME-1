// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?addBridgeToLogic@TerrainLogic@@UAEXPAVBridgeInfo@@PAVDict@@VAsciiString@@@Z
// Retail RVA 0x001AA780, TerrainLogic vtable slot 43.

#include <new>

#include "../../../../../reference/shims/stringinline/StringInline.h"

class BridgeInfo
{
	char m_data[0x6c];
};

class Dict;

enum PathfindLayerEnum
{
};

class Bridge
{
public:
	Bridge(BridgeInfo &info, Dict *props, AsciiString name, int unused);

	void setNext(Bridge *next)
	{
		m_next = next;
	}

	void setLayer(PathfindLayerEnum layer)
	{
		m_layer = layer;
	}

private:
	void *m_vtable;
	Bridge *m_next;
	char m_data[0x80];
	PathfindLayerEnum m_layer;
	char m_tail[4];
};

// Bridge's retail constructor takes a fourth stack word although its public
// declaration exposes only three source arguments.
#pragma comment(linker, "/alternatename:??0Bridge@@QAE@AAVBridgeInfo@@PAVDict@@VAsciiString@@H@Z=_bfme_Bridge_ctor_1A98A0")

class Pathfinder
{
public:
	PathfindLayerEnum addBridge(Bridge *bridge);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return *(Pathfinder **)((const char *)this + 0x0c);
	}
};

extern AI *TheAI;

class TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void addBridgeToLogic(BridgeInfo *info, Dict *props, AsciiString name);

private:
	char m_data[0x30];
	Bridge *m_bridgeListHead;
};

void TerrainLogic::addBridgeToLogic(BridgeInfo *info, Dict *props,
	AsciiString name)
{
	Bridge *bridge = new Bridge(*info, props, name, 0);
	bridge->setNext(m_bridgeListHead);
	m_bridgeListHead = bridge;
	PathfindLayerEnum layer = TheAI->pathfinder()->addBridge(bridge);
	bridge->setLayer(layer);
}

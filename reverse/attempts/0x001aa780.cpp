// ?addBridgeToLogic@TerrainLogic@@UAEXPAVBridgeInfo@@PAVDict@@VAsciiString@@@Z
// partial score=0.98 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME: TerrainLogic::addBridgeToLogic, retail 0x001AA780.
// Authentic one-pointer AsciiString and MemoryPoolObject inheritance compile
// to 174/176 bytes. Retail reserves one extra zero word for the Bridge ctor;
// its 0x001A98A0 body ends in ret 0x10 despite the three-argument declaration.

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

class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject() { }
};

class Bridge : public MemoryPoolObject
{
public:
	Bridge(BridgeInfo &info, Dict *props, AsciiString name);

	void setNext(Bridge *next)
	{
		m_next = next;
	}

	void setLayer(PathfindLayerEnum layer)
	{
		m_layer = layer;
	}

private:
	Bridge *m_next;
	char m_data[0x80];
	PathfindLayerEnum m_layer;
	char m_tail[4];
};

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
	Bridge *bridge = new Bridge(*info, props, name);
	bridge->setNext(m_bridgeListHead);
	m_bridgeListHead = bridge;
	PathfindLayerEnum layer = TheAI->pathfinder()->addBridge(bridge);
	bridge->setLayer(layer);
}

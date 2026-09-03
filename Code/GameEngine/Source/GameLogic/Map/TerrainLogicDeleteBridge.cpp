// cl: /DNDEBUG /DWIN32 /MD /EHsc
// TerrainLogic::deleteBridge, retail 0x001AAF00.

typedef bool Bool;
typedef int ObjectID;

enum PathfindLayerEnum
{
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AsciiString
{
	void *m_data;
};

struct BridgeInfo
{
	BridgeInfo();

	Coord3D from;
	Coord3D to;
	float bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
	int bridgeIndex;
	int curDamageState;
	ObjectID bridgeObjectID;
	ObjectID towerObjectID[4];
	Bool damageStateChanged;
};

class Bridge
{
public:
	virtual ~Bridge();

	Bridge *getNext(void) { return m_next; }
	void setNext(Bridge *next) { m_next = next; }
	void getBridgeInfo(BridgeInfo *info) { *info = m_bridgeInfo; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }
	void deleteInstance(void) { delete this; }

private:
	Bridge *m_next;
	AsciiString m_templateName;
	BridgeInfo m_bridgeInfo;
	char m_bounds[0x10];
	PathfindLayerEnum m_layer;
};

class Pathfinder
{
public:
	void changeBridgeState(PathfindLayerEnum layer, Bool open);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return *(Pathfinder **)((char *)this + 0x0c);
	}
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);
};

// The singleton declarations use the retail global symbols from the BFME map
// logic and object lookup implementations.
extern AI *TheAI;
extern GameLogic *TheGameLogic;

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
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual Bridge *getFirstBridge(void) const;
	virtual void deleteBridge(Bridge *bridge);

private:
	char m_unreconstructed_04[0x30];
	Bridge *m_bridgeListHead;
};

// ?deleteBridge@TerrainLogic@@UAEXPAVBridge@@@Z
void TerrainLogic::deleteBridge(Bridge *bridge)
{
	if (bridge == 0)
		return;

	if (m_bridgeListHead == bridge)
	{
		m_bridgeListHead = bridge->getNext();
	}
	else
	{
		for (Bridge *otherBridge = getFirstBridge(); otherBridge;
			otherBridge = otherBridge->getNext())
		{
			if (otherBridge->getNext() == bridge)
			{
				otherBridge->setNext(bridge->getNext());
				break;
			}
		}
	}

	BridgeInfo bridgeInfo;
	bridge->getBridgeInfo(&bridgeInfo);
	TheAI->pathfinder()->changeBridgeState(bridge->getLayer(), false);

	GameLogic *gameLogic = TheGameLogic;
	Object *bridgeObject = gameLogic->findObjectByID(bridgeInfo.bridgeObjectID);
	if (bridgeObject)
		gameLogic->destroyObject(bridgeObject);

	bridge->deleteInstance();
}

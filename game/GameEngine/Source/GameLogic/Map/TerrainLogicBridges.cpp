// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?deleteBridge@TerrainLogic@@UAEXPAVBridge@@@Z: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?deleteBridges@TerrainLogic@@IAEXXZ: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?updateBridgeDamageStates@TerrainLogic@@UAEXXZ: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?pickBridge@TerrainLogic@@UAE_NABVVector3@@0PAV2@@Z: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

// The four TerrainLogic bodies that walk the bridge list:
//
//   deleteBridge             0x001AAF00  vtable slot 45  unlink one and destroy it
//   deleteBridges            0x001AB150  protected       drop every orphaned bridge
//   updateBridgeDamageStates 0x001AAD70  vtable slot 46  re-poll each bridge's damage
//   pickBridge               0x001AADA0  vtable slot 42  first bridge a ray hits
//
// Slots read off retail's TerrainLogic vtable at 0x0109C428, which the
// destructor at 0x001ADD90 installs.  deleteBridges is not in that table; it is
// reached by name and calls deleteBridge through slot 45 (+0xB4), which is what
// identifies it.
//
// The four used to live one to a file with four accounts of Bridge, and the
// accounts contradicted each other: two spelled the object id as a member at
// +0x60 over a 0x58-byte pad, one reached the same field as
// m_bridgeInfo.bridgeObjectID and one modelled only m_next.  Retail settles it
// -- deleteBridge copies 27 dwords from bridge+0x0c, so BridgeInfo is at +0x0c
// and its bridgeObjectID at +0x54, which is the +0x60 the other two read.  One
// Bridge below says both at once.
//
// TerrainLogic drifted the same way: one file put m_bridgeListHead at +0x34 and
// knew nothing of the damage flag, another put m_bridgeDamageStatesChanged at
// +0x38 and knew nothing of the list head.  They are neighbours, and both are
// named here.  Worse, each file invented its own slot for the body it owned --
// deleteBridge at 38, updateBridgeDamageStates at 38, pickBridge at 38 -- where
// only slot 37 (getFirstBridge) and slot 45 (deleteBridge, reached virtually by
// deleteBridges) were ever load-bearing.  The numbering above is retail's.
//
// Kept out of TerrainLogic.cpp because pinning these offsets inline renumbers
// that compiland's $L labels and breaks its EH funclet row uw_00c08460 -- the
// same thing that moved Shell::isAnimReversed and
// BattlePlanUpdate::recenterTurret into their own TUs.

typedef bool Bool;
typedef int ObjectID;

class Object;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

enum PathfindLayerEnum
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

// Only its size is visible from these four bodies; it is here so Bridge's
// members land where retail's do.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
struct BridgeInfo
{
	BridgeInfo();						///< ILT 0x00419E9D

	Coord3D from;
	Coord3D to;
	float bridgeWidth;
	Coord3D fromLeft;
	Coord3D fromRight;
	Coord3D toLeft;
	Coord3D toRight;
	int bridgeIndex;
	int curDamageState;
	ObjectID bridgeObjectID;				///< +0x54, so Bridge+0x60
	ObjectID towerObjectID[4];
	Bool damageStateChanged;
	// 108 bytes: the 27 dwords deleteBridge copies out of bridge+0x0c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	virtual ~Bridge();

	void updateDamageState(void);				///< ILT 0x004232D6
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);

	Bridge *getNext(void) { return m_next; }
	void setNext(Bridge *next) { m_next = next; }
	void getBridgeInfo(BridgeInfo *info) { *info = m_bridgeInfo; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }
	void deleteInstance(void) { delete this; }

	ObjectID getBridgeObjectID(void) const { return m_bridgeInfo.bridgeObjectID; }

private:
	Bridge *m_next;						///< retail this+0x04
	AsciiString m_templateName;				///< retail this+0x08
	BridgeInfo m_bridgeInfo;				///< retail this+0x0c
	char m_bounds[0x10];
	PathfindLayerEnum m_layer;				///< retail this+0x88
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	// Retail has one findObjectByID.  deleteBridge calls it out of line through
	// ILT 0x0041F253; the other two bodies carry MSVC's inline expansion of the
	// same function, which is why both spellings are declared here.
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);			///< ILT 0x0041D0DE

	__forceinline Object *lookupObjectInHash(ObjectID id)
	{
		ObjectPtrHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	Object *findObjectByIDInline(ObjectID id)
	{
		if (id == 0)
			return 0;
		return lookupObjectInHash(id);
	}

private:
	char m_pad[0xB0];
	ObjectPtrHash m_objectHash;				///< retail this+0xB0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing/Object.h
class Drawable;

class Object
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual Drawable *getDrawable();			///< retail vtable slot 10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void changeBridgeState(PathfindLayerEnum layer, Bool open);	///< ILT 0x0042847F
	Bool bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
};

#pragma comment(linker, "/alternatename:?bfmePickBridge@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z=?d_003d8c40@@YAXXZ")

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return *(Pathfinder **)((char *)this + 0x0c);
	}
};

// The singleton declarations use the retail global symbols from the BFME map
// logic and object lookup implementations.
extern AI *TheAI;						///< retail 0x012EF214
extern GameLogic *TheGameLogic;					///< retail 0x012F0898

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// Vtable slice of retail's 0x0109C428, forty-eight slots wide; only the three
// virtuals this TU defines are given, and the rest stay pure so no vftable is
// emitted.  Slot 37 is named because all four bodies call it.
class TerrainLogic
{
public:
	virtual void _tl_00(void) = 0;
	virtual void _tl_01(void) = 0;
	virtual void _tl_02(void) = 0;
	virtual void _tl_03(void) = 0;
	virtual void _tl_04(void) = 0;
	virtual void _tl_05(void) = 0;
	virtual void _tl_06(void) = 0;
	virtual void _tl_07(void) = 0;
	virtual void _tl_08(void) = 0;
	virtual void _tl_09(void) = 0;
	virtual void _tl_10(void) = 0;
	virtual void _tl_11(void) = 0;
	virtual void _tl_12(void) = 0;
	virtual void _tl_13(void) = 0;
	virtual void _tl_14(void) = 0;
	virtual void _tl_15(void) = 0;
	virtual void _tl_16(void) = 0;
	virtual void _tl_17(void) = 0;
	virtual void _tl_18(void) = 0;
	virtual void _tl_19(void) = 0;
	virtual void _tl_20(void) = 0;
	virtual void _tl_21(void) = 0;
	virtual void _tl_22(void) = 0;
	virtual void _tl_23(void) = 0;
	virtual void _tl_24(void) = 0;
	virtual void _tl_25(void) = 0;
	virtual void _tl_26(void) = 0;
	virtual void _tl_27(void) = 0;
	virtual void _tl_28(void) = 0;
	virtual void _tl_29(void) = 0;
	virtual void _tl_30(void) = 0;
	virtual void _tl_31(void) = 0;
	virtual void _tl_32(void) = 0;
	virtual void _tl_33(void) = 0;
	virtual void _tl_34(void) = 0;
	virtual void _tl_35(void) = 0;
	virtual void _tl_36(void) = 0;
	virtual Bridge *getFirstBridge(void) = 0;
	virtual void _tl_38(void) = 0;
	virtual void _tl_39(void) = 0;
	virtual void _tl_40(void) = 0;
	virtual void _tl_41(void) = 0;
	virtual Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	virtual void _tl_43(void) = 0;
	virtual void _tl_44(void) = 0;
	virtual void deleteBridge(Bridge *bridge);
	virtual void updateBridgeDamageStates(void);

protected:
	void deleteBridges(void);

private:
	char m_unreconstructed_04[0x30];
	Bridge *m_bridgeListHead;				///< retail this+0x34
	bool m_bridgeDamageStatesChanged;			///< retail this+0x38
};

// TerrainLogic::deleteBridge, retail 0x001AAF00.
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

// TerrainLogic::deleteBridges, retail 0x001AB150.
//
// The zero check is the caller's here rather than inside the lookup, which is
// why this reaches lookupObjectInHash and pickBridge below reaches the guarded
// spelling: retail tests the id once in each body.
void TerrainLogic::deleteBridges(void)
{
	Bridge *bridge = getFirstBridge();
	if (bridge == 0)
		return;
	GameLogic *gameLogic = TheGameLogic;
	Bridge *next;
	do
	{
		next = bridge->getNext();
		if (bridge->getBridgeObjectID() == 0
			|| gameLogic->lookupObjectInHash(bridge->getBridgeObjectID()) == 0)
		{
			deleteBridge(bridge);
			gameLogic = TheGameLogic;
		}
		bridge = next;
	}
	while (bridge);
}

// TerrainLogic::updateBridgeDamageStates, retail 0x001AAD70.
void TerrainLogic::updateBridgeDamageStates(void)
{
	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		pBridge->updateDamageState();
		pBridge = pBridge->getNext();
	}
	m_bridgeDamageStatesChanged = true;
}

// TerrainLogic::pickBridge, retail 0x001AADA0.
Bool TerrainLogic::pickBridge(const Vector3 &from, const Vector3 &to,
	Vector3 *pos)
{
	Drawable *curDraw = 0;
	Vector3 curPos;
	curPos.X = 0;
	curPos.Y = 0;
	curPos.Z = 0;

	Bridge *pBridge = getFirstBridge();
	while (pBridge) {
		Vector3 thisPos;
		Bool thisDraw = pBridge->pickBridge(from, to, &thisPos);
		if (thisDraw) {
			Object *bridgeObject = TheGameLogic->findObjectByIDInline(
				pBridge->getBridgeObjectID());
			Drawable *draw;
			if (bridgeObject) {
				draw = bridgeObject->getDrawable();
			} else {
				draw = 0;
			}
			if (!curDraw) {
				curDraw = draw;
				curPos = thisPos;
			}
		}
		pBridge = pBridge->getNext();
	}
	if (curDraw) {
		pos->X = curPos.X;
		pos->Y = curPos.Y;
		pos->Z = curPos.Z;
		return true;
	}
	Pathfinder *pathfinder = TheAI->pathfinder();
	return pathfinder->bfmePickBridge(from, to, pos);
}

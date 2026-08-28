// cl: /DNDEBUG /MD /EHsc
// readable body of ?addLandmarkBridgeToLogic@TerrainLogic@@UAEXPAVObject@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// Open-BFME5: TerrainLogic::addLandmarkBridgeToLogic, retail 0x001AA860,
// zh_sweep packet 001aa860.
//
// The Zero Hour body unchanged. Compiled inside TerrainLogic.cpp it reproduced
// everything but two numbers:
//
//  - retail allocates 0x90 bytes for a Bridge where the vendored class is 0x8C,
//    so BFME's is four bytes wider;
//  - m_bridgeListHead is at [this+0x34], not the vendored +0x2C.
//
// Bridge's own offsets are already right and stay named: setNext writes +0x04
// and setLayer writes +0x88, both inlined. TheAI is at 0x012EF214 and its
// pathfinder at +0x0C.
//
// Its own TU because TerrainLogic.cpp carries EH funclet rows keyed on $L
// labels, and both of the above are class-wide changes that would move every
// other row in the file.

typedef int Int;

class Object;

enum PathfindLayerEnum { LAYER_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	Bridge( Object *bridgeObj );							///< ILT 0x00047C0D -> 0x001A9CE0

	void setNext( Bridge *next ) { m_next = next; }
	void setLayer( PathfindLayerEnum layer ) { m_layer = layer; }

private:
	void *m_unreconstructed_00;								///< +0x00
	Bridge *m_next;											///< +0x04
	unsigned char m_unreconstructed_08[0x88 - 0x08];
	PathfindLayerEnum m_layer;								///< +0x88
	unsigned char m_unreconstructed_8C[0x90 - 0x8C];		///< out to sizeof 0x90
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	PathfindLayerEnum addBridge( Bridge *bridge );			///< ILT 0x0003C966 -> 0x003D5850
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder( void ) { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;								///< +0x0C
};

extern AI *TheAI;											///< retail 0x012EF214

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void addLandmarkBridgeToLogic( Object *bridgeObj );

private:
	unsigned char m_unreconstructed_04[0x34 - 4];			///< vptr at +0x00
	Bridge *m_bridgeListHead;								///< +0x34
};

//-------------------------------------------------------------------------------------------------
// ?addLandmarkBridgeToLogic@TerrainLogic@@UAEXPAVObject@@@Z
void TerrainLogic::addLandmarkBridgeToLogic(Object *bridgeObj)
{

	Bridge *pBridge = ::new Bridge(bridgeObj);
	pBridge->setNext(m_bridgeListHead);
	m_bridgeListHead = pBridge;
	PathfindLayerEnum layer = TheAI->pathfinder()->addBridge(pBridge);
	pBridge->setLayer(layer);

}

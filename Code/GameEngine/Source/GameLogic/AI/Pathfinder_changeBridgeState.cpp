// cl: /DNDEBUG /MD /EHsc
// readable body of ?changeBridgeState@Pathfinder@@QAEXW4PathfindLayerEnum@@_N@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Open-BFME: Pathfinder::changeBridgeState, retail 0x003D58C0, 70 bytes.
//
// The reference's body with two BFME differences. The layer test runs the
// other way round -- retail goes on when the call returns true, where the
// reference bails out when its isUnused does -- so the predicate is named for
// what the bytes do rather than for the reference's spelling. And
// markZonesDirty takes two arguments here, both constants, with the repaired
// flag reaching only setDestroyed.
//
// The layer array is at this+0x85C with a stride of 0x44, and the zone manager
// at +0xC9C.

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool isUsed(void);					// ILT 0x0003D4E2
	Bool setDestroyed(Bool destroyed);			// ILT 0x00005510

private:
	char m_bfme_body[0x44];					// the layer stride
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	void markZonesDirty(Bool insert, Bool bfmeSecond);	// ILT 0x00015307
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void changeBridgeState(PathfindLayerEnum layer, Bool repaired);

private:
	char m_slice_padA[0x85C];				// retail this+0x00 .. +0x85B, untouched
	PathfindLayer m_layers[1];				// this+0x85C
	char m_slice_padB[0xC9C - 0x8A0];			// this+0x8A0 .. +0xC9B, untouched
	PathfindZoneManager m_zoneManager;			// this+0xC9C
};

void Pathfinder::changeBridgeState( PathfindLayerEnum layer, Bool repaired)
{
	if (m_layers[layer].isUsed()) {
		if (m_layers[layer].setDestroyed(!repaired)) {
			m_zoneManager.markZonesDirty( false, true );
		}
	}
}

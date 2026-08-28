// cl: /DNDEBUG /MD /EHsc
// readable body of ?addBridge@Pathfinder@@QAE?AW4PathfindLayerEnum@@PAVBridge@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// Open-BFME: Pathfinder::addBridge, retail 0x003D5850, 87 bytes.
//
// The reference's body once its two debug lines are gone: scan the bridge
// layers for the first free one, initialise it, and hand back its index --
// falling back to LAYER_GROUND both when the initialisation fails and when
// every layer is taken.
//
// The predicate is the same one changeBridgeState uses, named for what the
// bytes do: the loop steps on while it returns true and stops on the first
// layer it returns false for, which is the reference's isUnused inverted.
//
// The scan walks a pointer by the 0x44 stride from this+0x8E4 -- the array at
// +0x85C plus the two layers the loop starts past -- while the initialisation
// recomputes the address from the index.

typedef int Int;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_WALL = 15, LAYER_LAST = 15 };

class Bridge;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool isUsed(void);					// ILT 0x0003D4E2
	Bool init(Bridge *theBridge, PathfindLayerEnum layer);	// ILT 0x0004B0AB

private:
	char m_bfme_body[0x44];					// the layer stride
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	PathfindLayerEnum addBridge(Bridge *theBridge);

private:
	char m_slice_pad[0x85C];				// retail this+0x00 .. +0x85B, untouched
	PathfindLayer m_layers[LAYER_LAST + 1];			// this+0x85C
};

PathfindLayerEnum Pathfinder::addBridge(Bridge *theBridge)
{
	Int layer = LAYER_GROUND+1;
	while (layer<=LAYER_WALL) {
		if (!m_layers[layer].isUsed()) {
			if (m_layers[layer].init(theBridge, (PathfindLayerEnum)layer) ) {
				return (PathfindLayerEnum)layer;
			}
			return LAYER_GROUND; // failed to init, usually cause off of the map.  jba.
		}
		layer++;
	}
	return LAYER_GROUND;
}

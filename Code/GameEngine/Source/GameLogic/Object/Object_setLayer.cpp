// cl: /DNDEBUG /MD /EHsc
// readable body of ?setLayer@Object@@QAEXW4PathfindLayerEnum@@@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp
// Open-BFME: Object::setLayer, retail 0x001BEBB0, 85 bytes.
//
// The reference's body plus the block it keeps under an #ifdef. Retail runs
// the bridge-layer query for real whenever the object is leaving a layer other
// than LAYER_GROUND, and throws the answer away -- there is no test of eax
// after the call -- which is what the reference's debug-only check looks like
// once the assertion around it is gone.
//
// The rest is the reference unchanged: drop the object out of the pathfinder,
// store the new layer, put it back at its position.
//
// m_layer is at this+0x314 and the position at this+0x38, the offset the whole
// tree already reads for getPosition. TheAI's pathfinder is its +0x0C, loaded
// again for the second call rather than kept, and objectInteractsWithBridgeLayer
// is TerrainLogic vtable+0xA0 (slot 40), reached with the reference's three
// arguments including the defaulted considerBridgeHealth.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_WALL = 15, LAYER_LAST = 15 };

struct Coord3D { Real x, y, z; };

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removePos(Object *obj);					// ILT 0x0001D9DA
	void updatePos(Object *obj, const Coord3D *pos);			// ILT 0x00013647
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	char m_slice_pad[0x0C];						// retail this+0x00 .. +0x0B, untouched
	Pathfinder *m_pathfinder;					// this+0x0C
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00() = 0;	virtual void slot01() = 0;	virtual void slot02() = 0;
	virtual void slot03() = 0;	virtual void slot04() = 0;	virtual void slot05() = 0;
	virtual void slot06() = 0;	virtual void slot07() = 0;	virtual void slot08() = 0;
	virtual void slot09() = 0;	virtual void slot10() = 0;	virtual void slot11() = 0;
	virtual void slot12() = 0;	virtual void slot13() = 0;	virtual void slot14() = 0;
	virtual void slot15() = 0;	virtual void slot16() = 0;	virtual void slot17() = 0;
	virtual void slot18() = 0;	virtual void slot19() = 0;	virtual void slot20() = 0;
	virtual void slot21() = 0;	virtual void slot22() = 0;	virtual void slot23() = 0;
	virtual void slot24() = 0;	virtual void slot25() = 0;	virtual void slot26() = 0;
	virtual void slot27() = 0;	virtual void slot28() = 0;	virtual void slot29() = 0;
	virtual void slot30() = 0;	virtual void slot31() = 0;	virtual void slot32() = 0;
	virtual void slot33() = 0;	virtual void slot34() = 0;	virtual void slot35() = 0;
	virtual void slot36() = 0;	virtual void slot37() = 0;	virtual void slot38() = 0;
	virtual void slot39() = 0;
	// slot 40, vtable+0xA0
	virtual Bool objectInteractsWithBridgeLayer(Object *obj, Int layer, Bool considerBridgeHealth = true) const = 0;
};

extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setLayer(PathfindLayerEnum layer);

	const Coord3D *getPosition(void) const { return &m_position; }

private:
	char m_slice_padA[0x38];					// retail this+0x00 .. +0x37, untouched
	Coord3D m_position;						// this+0x38
	char m_slice_padB[0x314 - 0x44];				// this+0x44 .. +0x313, untouched
	PathfindLayerEnum m_layer;					// this+0x314
};

void Object::setLayer(PathfindLayerEnum layer)
{
	if (layer != m_layer) {
		if (m_layer != LAYER_GROUND) {
			TheTerrainLogic->objectInteractsWithBridgeLayer(this, m_layer);
		}
		TheAI->pathfinder()->removePos(this);
		m_layer = layer;
		TheAI->pathfinder()->updatePos(this, getPosition());
	}
}

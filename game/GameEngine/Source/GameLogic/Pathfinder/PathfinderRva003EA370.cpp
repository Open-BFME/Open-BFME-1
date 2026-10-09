// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include <math.h>
#include <windows.h>
#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameCommon.h"
#include "Common/GameType.h"
#include "GameLogic/TerrainLogic.h"
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const Coord3D *getPosition() const { return &m_cachedPos; }
#define OBJECT_TU_MEMBERS void setLayer(PathfindLayerEnum);
#include "../Object/object.h"

static __forceinline bool rva003EA370BridgeLayer(int layer) { return layer >= 2 && layer <= 15; }
static __forceinline bool rva003EA370WallLayer(int layer) { return layer >= 17 && layer <= 64; }

class Gen_001BEC20
{
public:
	int bfmeScale() const;
};

struct Rva003E5CA0Pos
{
	Real x;
	Real y;
	Real z;
	Rva003E5CA0Pos(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
	~Rva003E5CA0Pos() {}
};

struct Rva003EA370LayerRecord
{
	char m_pad00[0x3C];
	Int m_word3c;
	char m_pad40[4];
};

class Bfme5BridgeList
{
public:
	char bfmeAnyBridgeAt(const Coord3D *pos);
};

class Pathfinder : public Bfme5BridgeList
{
public:
	Real getLayerHeight(PathfindLayerEnum layer, const Coord3D *pos, Coord3D *normal);
	Int bfmeLayerForPosition(Object *obj, Coord3D pos);
	void Rva003E4190(Object *obj);
	void Rva003EA370(Object *obj, Int layer);

private:
	char m_pad00[0x85C];
	Rva003EA370LayerRecord m_layers[1];
};

extern void j_00040f52();

// Open BFME 2 donor: Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderUpdateLayer.cpp
// ?Rva003EA370@Pathfinder@@QAEXPAVObject@@H@Z
void Pathfinder::Rva003EA370(Object *obj, Int layer)
{
	PathfindLayerEnum oldLayer = (PathfindLayerEnum)((const Gen_001BEC20 *)obj)->bfmeScale();
	Int newLayer = oldLayer;
	const Real MAX_Z_TO_WALL = 10.0f;
	Int mode = 3;
	if (rva003EA370BridgeLayer(layer))
		mode = 0;
	if (layer == 16)
		mode = 1;
	if (layer == LAYER_GROUND)
	{
		mode = 3;
		if (rva003EA370WallLayer(oldLayer))
			mode = 1;
	}
	if (rva003EA370WallLayer(layer))
	{
		mode = 2;
		if (fabs(obj->getPosition()->z - getLayerHeight((PathfindLayerEnum)layer, obj->getPosition(), 0)) > MAX_Z_TO_WALL)
			mode = 1;
		if (oldLayer == LAYER_GROUND)
			mode = 1;
	}

	if (mode == 3)
	{
		if (oldLayer == 16 && bfmeAnyBridgeAt(obj->getPosition()))
			return;
		newLayer = LAYER_GROUND;
	}
	else if (mode == 0)
	{
		if (oldLayer == 16 && bfmeAnyBridgeAt(obj->getPosition()))
			return;
		Bool onLayer;
		if (m_layers[layer].m_word3c != 0)
		{
			typedef Int (Pathfinder::*Call)(Object *, Rva003E5CA0Pos);
			union { void *raw; Call member; } call;
			call.raw = (void *)j_00040f52;
			onLayer = (this->*call.member)(obj, *obj->getPosition()) == layer;
		}
		else
			onLayer = TheTerrainLogic->objectInteractsWithBridgeLayer(obj, layer, true);
		if (onLayer)
			newLayer = layer;
		else
			newLayer = oldLayer;
	}
	else if (mode == 1)
	{
		newLayer = oldLayer;
		if (bfmeAnyBridgeAt(obj->getPosition()))
			newLayer = 16;
		else if (oldLayer == 16)
			newLayer = LAYER_GROUND;
	}
	else if (mode == 2)
	{
		if (bfmeAnyBridgeAt(obj->getPosition()))
			newLayer = 16;
		else
			newLayer = layer;
	}
	obj->setLayer((PathfindLayerEnum)newLayer);
	Rva003E4190(obj);
}

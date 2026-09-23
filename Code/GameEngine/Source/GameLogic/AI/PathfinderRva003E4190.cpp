// cl: /DNDEBUG /MD
// ?Rva003E4190@Pathfinder@@QAEXPAVObject@@@Z

#include <math.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_DUMMY = 0
};

class BFMEObjectLayerQuery
{
public:
	Int getLayer() const;
};

class Object : public BFMEObjectLayerQuery
{
public:
	void setLayer(PathfindLayerEnum layer);

	char m_pad[0x38];
	Coord3D m_position;
};

class PathfindCell
{
public:
	char m_pad[0x0c];
	unsigned int m_flags;

	Int getLayer() const { return (m_flags >> 6) & 0x3f; }
	Int getType() const { return m_flags & 7; }
};

class PathfindLayer
{
public:
	Bool isUsed();
};

struct Rva003FD060TerrainLogic
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual Real bfmeHeightABE(Real x, Real y, Int layer, Int normal, Int clip);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeDirectionWeight1285;

static __forceinline Real bfmeFloatFromBits(Int bits)
{
	union
	{
		Int bits;
		Real value;
	} floating;
	floating.bits = bits;
	return floating.value;
}

class Pathfinder
{
public:
	PathfindCell *bfmeObjectCell(Object *object);
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);

	void Rva003E4190(Object *object);
};

void Pathfinder::Rva003E4190(Object *object)
{
	Int oldLayer = object->getLayer();
	PathfindCell *currentCell = bfmeObjectCell(object);
	Coord3D position;
	position.x = object->m_position.x;
	position.y = object->m_position.y;
	position.z = object->m_position.z;

	if (currentCell == 0)
		return;

	Int cellLayer = currentCell->getLayer();
	if (cellLayer == oldLayer)
		return;

	register Int yBits = *(volatile Int *)&position.y;
	_ReadWriteBarrier();
	if (fabs(TheTerrainLogic->bfmeHeightABE(position.x, bfmeFloatFromBits(yBits),
		cellLayer, 0, 1) - position.z) < g_bfmeDirectionWeight1285)
		object->setLayer((PathfindLayerEnum)currentCell->getLayer());

	Int layerNumber = 2;
	PathfindLayer *layer;
	layer = (PathfindLayer *)((char *)this + 0x8e4);
	do
	{
		if (layer->isUsed())
		{
			ICoord2D cell;
			if (!worldToCell(&position, &cell))
			{
				PathfindCell *candidate = getCell((PathfindLayerEnum)layerNumber,
					cell.x, cell.y);
				if (candidate != 0 && candidate->getLayer() == layerNumber &&
					candidate->getType() != 5)
				{
					if (fabs(TheTerrainLogic->bfmeHeightABE(position.x,
						bfmeFloatFromBits(yBits),
						layerNumber, 0, 1) - position.z) < g_bfmeDirectionWeight1285)
					{
						object->setLayer((PathfindLayerEnum)layerNumber);
						return;
					}
				}
			}
		}

		++layerNumber;
		layer = (PathfindLayer *)((char *)layer + 0x44);
	} while (layerNumber <= 15);
}

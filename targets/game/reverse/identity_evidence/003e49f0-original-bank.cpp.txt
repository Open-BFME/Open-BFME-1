// ?bfmeCheckAttackViewHelper@Pathfinder@@QAEHPAVObject@@PAUCoord3D@@PAX@Z
// partial score=0.9668 date=2026-10-01
// cl: /DNDEBUG /MD
//
// Retail 0x003E49F0, 753 bytes (ret 0xC at +0x2EE). Identity: ILT 0x00005484 and
// the matched caller at 0x003EA570.  Rewritten on the layout of the matched
// sibling Pathfinder::checkDestination (PathfindCheckDestination.cpp): inline
// Pathfinder::getCell(layer,x,y), the ZH numCellsAbove preamble, REAL_TO_INT_FLOOR
// via fast_float2long_round, literal 0.1f/0.5f, and expression-form loop bounds
// the compiler hoists itself.  Retail sets the ground-cell flag when the layer is
// ground or out of range (the old bank dropped that path).
// probe: 753/753 bytes, shape 1.000; 29 bytes differ, all stack displacements:
// our frame is 0x28 against retail 0x24 because iRadius keeps its own slot at -12
// where retail overlaps it with the fistp temporaries and the hoisted xLast.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

extern "C" __declspec(dllimport) double __cdecl floor(double);

struct Coord3D { Real x, y, z; };
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

inline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

inline float fast_float_floor(float f)
{
	return (float)floor(f);
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

class Object
{
public:
	ObjectID getID( void ) const { return m_id; }
	Int getLayer( void ) const;

private:
	unsigned char m_prefix[0x74];
	ObjectID m_id;
};

class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
	ObjectID m_bfme1C;
	ObjectID m_bfme20;
};

class PathfindCell
{
public:
	ObjectID getPosUnit( void ) const { ObjectID id = m_info ? m_info->m_posUnitID : INVALID_ID; return id; }
	ObjectID getBfme20( void ) const { return m_info ? m_info->m_bfme20 : INVALID_ID; }

	PathfindCellInfo *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	unsigned char m_body[0x44];
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40();
	virtual Bool queryObjectLayer( Object *object, Int layer );
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Int bfmeCheckAttackViewHelper( Object *obj, Coord3D *pos, void *cellIds );
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );

protected:
	void getRadiusAndCenter( const Object *obj, Int &iRadius, Bool &center );

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > LAYER_GROUND && layer <= LAYER_LAST)
		{
			PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
}

Int Pathfinder::bfmeCheckAttackViewHelper( Object *obj, Coord3D *pos, void *cellIds )
{
	Int radius;
	Bool center;
	{
		Int iRadiusStorage[2];
#define iRadius iRadiusStorage[1]
		getRadiusAndCenter(obj, iRadius, center);
		radius = iRadius;
	}
	Bool centered = center;
	Int numCellsAbove = radius;
	ICoord2D cell;
	if (centered)
	{
		numCellsAbove = radius + 1;
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f);
	}
	else
	{
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f + 0.5f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f + 0.5f);
	}

	Bool checkGround = false;
	Bool checkLayer = false;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	if (layer != LAYER_GROUND && layer < 16)
	{
		checkLayer = true;
		if (TheTerrainLogic->queryObjectLayer(obj, layer))
			checkGround = true;
	}
	else
	{
		checkGround = true;
	}

	ObjectID *ids = (ObjectID *)cellIds;
	Int numIds = 0;
	Int i, j;
	for (i = cell.x - radius - 1; i < cell.x + numCellsAbove + 1; i++)
	{
		for (j = cell.y - radius - 1; j < cell.y + numCellsAbove + 1; j++)
		{
			if (i != cell.x - radius - 1 && j != cell.y - radius - 1 &&
				i != cell.x + numCellsAbove && j != cell.y + numCellsAbove)
				continue;

			if (checkLayer)
			{
				PathfindCell *layerCell = getCell(layer, i, j);
				if (layerCell)
				{
					ObjectID id = layerCell->getPosUnit();
					if (id == INVALID_ID)
						id = layerCell->getBfme20();
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = id;
							if (numIds == 16)
								return 16;
						}
					}
				}
			}

			if (checkGround)
			{
				PathfindCell *groundCell = getCell(LAYER_GROUND, i, j);
				if (groundCell)
				{
					ObjectID id = groundCell->getPosUnit();
					if (id == INVALID_ID)
						id = groundCell->getBfme20();
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = id;
							if (numIds == 16)
								return 16;
						}
					}
				}
			}
		}
	}
	return numIds;
}

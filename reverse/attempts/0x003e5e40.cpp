// ?rva003E5E40@Pathfinder@@QAEEPAVObject@@@Z
// partial score=0.1 date=2026-09-16
// cl: /DNDEBUG /MD
//
// Retail 0x003E5E40: address-derived Pathfinder footprint query.  The owner
// and method identity are not named by a caller, but the Pathfinder layout and
// all five called ABIs are independently witnessed by the adjacent bodies.

typedef int Int;
typedef unsigned int ObjectID;
typedef unsigned char Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

extern const float g_bfmeK1266C;

class Object
{
public:
	Bool bfmeIsComputerControlled(void) const;
	const Coord3D *getPosition(void) const { return &m_position; }

	char m_prefix[0x38];
	Coord3D m_position;
	char m_middle[0x74 - 0x44];
	ObjectID m_id;
};

class PathfindCellInfo
{
public:
	char m_prefix[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
};

class PathfindCell
{
public:
	Int getType(void) const
	{
		return m_packed & 7;
	}

	unsigned char getAircraftGoalByte(void) const
	{
		return (unsigned char)(m_packed >> 21);
	}

	PathfindCellInfo *m_info;
	Int m_unused04;
	Int m_unused08;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);

	char m_body[0x44];
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void bfmeQuery(Object *object, Int *radius, Bool *center);
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	Bool rva003E5E40(Object *object);

	__forceinline PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extentLoX && x <= m_extentHiX &&
			y >= m_extentLoY && y <= m_extentHiY)
		{
			if (layer > LAYER_GROUND && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(x, y);
				if (cell != 0)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}

private:
	char m_prefix[0x10];
	PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
	char m_middle[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

Bool Pathfinder::rva003E5E40(Object *object)
{
	Bool center;
	Int radius;
	Coord3D position;
	ICoord2D cell;
	bfmeQuery(object, &radius, &center);

	const Coord3D *objectPosition = object->getPosition();
	position = *objectPosition;
	if (!center)
	{
		position.x += g_bfmeK1266C;
		position.y += g_bfmeK1266C;
	}

	if (worldToCell(&position, &cell))
		return false;

	PathfindLayerEnum layer =
		TheTerrainLogic->getLayerForDestination(object, objectPosition);
	Int numCellsAbove = radius;
	if (center)
		++numCellsAbove;

	ObjectID objectID = object->m_id;
	Int x;
	Int y;
	for (x = cell.x - radius;
		x < cell.x + numCellsAbove;
		++x)
	{
		for (y = cell.y - radius;
			y < cell.y + numCellsAbove;
			++y)
		{
			PathfindCell *pathCell = getCell(layer, x, y);
			if (pathCell == 0)
				return false;

			if (pathCell->getType() == 5)
				return false;

			if ((pathCell->getAircraftGoalByte() & 1) != 0 &&
				object->bfmeIsComputerControlled())
				return false;

			if (pathCell->getType() == 4)
				return false;

			if ((pathCell->m_packed & 0x38) != 0)
			{
				PathfindCellInfo *info = pathCell->m_info;
				ObjectID goalUnitID = info != 0 ? info->m_goalUnitID : 0;
				if (goalUnitID == objectID || goalUnitID == 0)
					continue;

				ObjectID posUnitID = info != 0 ? info->m_posUnitID : 0;
				if (posUnitID == goalUnitID)
					return false;
			}
		}
	}

	return true;
}

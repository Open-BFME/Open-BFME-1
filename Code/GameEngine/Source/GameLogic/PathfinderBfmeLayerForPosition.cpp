// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003E5CA0: Pathfinder::bfmeLayerForPosition.

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class Rva001BF140ByteField
{
public:
	unsigned char get(void) const;
	char m_pad[0x3a8];
	unsigned char m_value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Rva001BF140ByteField
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getLayer(void) const { return (Int)((m_packed >> 6) & 0x3f); }
	Int getType(void) const { return (Int)(m_packed & 7); }

private:
	void *m_info;
	Int m_field04;
	Int m_field08;
	unsigned int m_packed;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	bool isUsed(void);

	char m_pad00[0x38];
	void *m_bridgeA;
	void *m_bridgeB;
	Int m_height;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int bfmeLayerForPosition(Object *object, Coord3D position);

	void bfmeQuery(Object *object, Int *radius, Bool *center);
	bool worldToCell(const Coord3D *position, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	PathfindCell *getGroundCell(Int x, Int y)
	{
		if (x >= m_extentLoX && x <= m_extentHiX &&
			y >= m_extentLoY && y <= m_extentHiY)
			return &m_map[x][y];
		return 0;
	}

	char m_pad00[0x10];
	PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
	char m_pad24[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

Int Pathfinder::bfmeLayerForPosition(Object *object, Coord3D position)
{
	ICoord2D cell;
	if (object != 0)
	{
		if (object->get())
			return LAYER_GROUND;

		Bool center;
		bfmeQuery(object, &cell.x, &center);
		if (!center)
		{
			position.x += 5.0f;
			position.y += 5.0f;
		}
	}

	Int layer = 2;
	char *bridge = (char *)&m_layers[2].m_bridgeB;
	while (layer <= 15)
	{
		if (((PathfindLayer *)(bridge - 0x3c))->isUsed() &&
			*(void **)bridge != 0)
		{
			if (!worldToCell(&position, &cell))
			{
				PathfindCell *pathCell = getCell((PathfindLayerEnum)layer,
					cell.x, cell.y);
				if (pathCell != 0 && pathCell->getLayer() == layer &&
					pathCell->getType() != 5 &&
					*(Int *)(bridge + 4) - position.z < 25.0f)
					return layer;
			}
		}
		++layer;
		bridge += 0x44;
	}

	if (worldToCell(&position, &cell))
		return LAYER_GROUND;
	PathfindCell *pathCell = getGroundCell(cell.x, cell.y);
	if (pathCell != 0)
		return pathCell->getLayer();
	return LAYER_GROUND;
}

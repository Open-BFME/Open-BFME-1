// cl: /DNDEBUG /MD
//
// Retail 0x003EE9F0 is the stateful pathfind-cell callback reached through
// the ILT at 0x000257D4.  Its semantic owner is not identified in the
// available caller evidence, so the payload keeps an address-derived name.

typedef unsigned char Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 0
};

struct BfmeMovementPositionInfo
{
	int m_surfaces;
	unsigned char m_field04;
	unsigned char m_allowAircraftGoal;
	unsigned char m_pad06[2];
	int m_maxLayer;
};

class PathfindCell
{
public:
	unsigned char m_pad00[0xc];
	unsigned int m_word;
};

class Pathfinder;
class BfmeE1081;

class Pathfinder
{
public:
	bool bfmeStepD4F90(void *state, PathfindCell *cell);
};

class BfmeD1081
{
public:
	char bfmeDo1081(BfmeE1081 *a, char *b, char *c, int d);
};

class TerrainLogic
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;
};

extern TerrainLogic *TheTerrainLogic;
extern const float g_bfmeK1253;
extern const float g_bfmeDirectionWeight1285;

class Object
{
public:
	char m_pad00[0x38];
	char m_position;
};

class Rva003EE9F0
{
public:
	int run(PathfindCell *unused, PathfindCell *cell, int cellX, int cellY);

	Pathfinder *m_pathfinder;
	Object *m_object;
	char m_pad08[4];
	BfmeMovementPositionInfo m_info;
	Bool m_found;
	Bool m_field19;
	Bool m_stepFailed;
	Bool m_field1B;
	Bool m_field1C;
};

int Rva003EE9F0::run(PathfindCell *unused, PathfindCell *cell,
	int cellX, int cellY)
{
	register PathfindCell *toCell = cell;
	unsigned int word = toCell->m_word;

	if (((unsigned char)(word >> 20) & 1) == 0 &&
		((char)(word >> 6) & 0x3f) <= 1)
		goto check_type;
	if (m_field19 != 0)
		goto check_type;
	if (m_stepFailed != 0)
		goto check_type;
	if (m_field1B != 0)
		return true;

check_type:
	int type = word;
	type &= 7;
	if (type == 4)
		return false;
	if (((char)(word >> 6) & 0x3f) > 1 &&
		m_field19 == 0 && m_stepFailed != 0)
		return false;

	m_stepFailed = 0;
	if (!m_pathfinder->bfmeStepD4F90(&m_info, toCell))
		return false;

	Coord3D position;
	position.x = ((float)cellX + g_bfmeK1253) * g_bfmeDirectionWeight1285;
	position.y = ((float)cellY + g_bfmeK1253) * g_bfmeDirectionWeight1285;
	unsigned int layerWord = toCell->m_word;
	int layer = (layerWord >> 6) & 0x3f;
	position.z = TheTerrainLogic->getLayerHeight(position.x, position.y,
		(PathfindLayerEnum)layer, 0, true);

	if (((BfmeD1081 *)m_pathfinder)->bfmeDo1081(
		(BfmeE1081 *)m_object, &m_object->m_position,
		(char *)&position, 0))
	{
		m_found = 1;
		return true;
	}

	if (m_field1C != 0)
	{
		m_field1B = 1;
		return true;
	}

	m_field1B = 1;
	return m_field19 != 0;
}

// BFME choose-best-locomotor query at retail 0x003D5CA0.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline Int bfmeFloatToInt(Real value)
{
	Int result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define BFME_CELL_INV 0.1f
#define BFME_FLOOR(value) bfmeFloatToInt((Real)floor((double)(value)))

struct Coord3D
{
	Real x, y, z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 0
};

class PathfindCell
{
public:
	char m_head[0x0c];
	unsigned int m_packed;

	Int getType(void) const
	{
		return (Int)(m_packed & 7);
	}
};

class Locomotor
{
};

typedef int LocomotorSurfaceTypeMask;

class LocomotorSet
{
public:
	Locomotor *findLocomotor(LocomotorSurfaceTypeMask surfaces);
};

extern int g_Va012B49FC[];

class Pathfinder
{
public:
	Locomotor *chooseBestLocomotorForPosition(PathfindLayerEnum layer,
		LocomotorSet *locomotorSet, const Coord3D *pos);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
};

// ?chooseBestLocomotorForPosition@Pathfinder@@QAEPAVLocomotor@@W4PathfindLayerEnum@@PAVLocomotorSet@@PBUCoord3D@@@Z
Locomotor *Pathfinder::chooseBestLocomotorForPosition(PathfindLayerEnum layer,
	LocomotorSet *locomotorSet, const Coord3D *pos)
{
	Int x = BFME_FLOOR(pos->x * BFME_CELL_INV);
	Int y = BFME_FLOOR(pos->y * BFME_CELL_INV);
	PathfindCell *cell = getCell(layer, x, y);
	Int type = cell ? cell->getType() : 0;
	LocomotorSurfaceTypeMask surfaces = g_Va012B49FC[type];
	return locomotorSet->findLocomotor(surfaces);
}

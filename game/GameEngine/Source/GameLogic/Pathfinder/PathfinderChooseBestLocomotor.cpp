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

// Retail 0x012B49FC: the surfaces each cell type accepts, indexed by the 3-bit
// type above (8 entries). It is the table form of Zero Hour's
// Pathfinder::validLocomotorSurfacesForCellType: every live type adds AIR (8),
// and the unused eighth type is NO_SURFACES.
int g_Va012B49FC[8] = { 0x09, 0x0A, 0x0C, 0x18, 0x28, 0x48, 0x48, 0x00 };

class Pathfinder
{
public:
	Locomotor *chooseBestLocomotorForPosition(PathfindLayerEnum layer,
		LocomotorSet *locomotorSet, const Coord3D *position);
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);
};

// ?chooseBestLocomotorForPosition@Pathfinder@@QAEPAVLocomotor@@W4PathfindLayerEnum@@PAVLocomotorSet@@PBUCoord3D@@@Z
Locomotor *Pathfinder::chooseBestLocomotorForPosition(PathfindLayerEnum layer,
	LocomotorSet *locomotorSet, const Coord3D *position)
{
	Int x = BFME_FLOOR(position->x * BFME_CELL_INV);
	Int y = BFME_FLOOR(position->y * BFME_CELL_INV);
	PathfindCell *cell = getCell(layer, x, y);
	Int type = cell ? cell->getType() : 0;
	LocomotorSurfaceTypeMask surfaces = g_Va012B49FC[type];
	return locomotorSet->findLocomotor(surfaces);
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?isUnderwater@TerrainLogic@@UAE_NMMPAM0@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

typedef bool Bool;
typedef float Real;

struct Coord3D;
struct WaterHandle {};

class TerrainVisualDispatch
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0;
	virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0;
	virtual void v18() = 0; virtual void v19() = 0;
	virtual Bool getWaterGridHeight(Real x, Real y, Real *height) = 0;
};

class TerrainLogicDispatch
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
	virtual void v07() = 0; virtual void v08() = 0;
	virtual void v09() = 0; virtual void v10() = 0;
	virtual void v11() = 0; virtual void v12() = 0;
	virtual void v13() = 0; virtual void v14() = 0;
	virtual void v15() = 0; virtual void v16() = 0;
	virtual void v17() = 0; virtual void v18() = 0;
	virtual void v19() = 0; virtual void v20() = 0;
	virtual void v21() = 0; virtual void v22() = 0;
	virtual void v23() = 0; virtual void v24() = 0;
	virtual const WaterHandle *getWaterHandle(Real x, Real y) = 0;
	virtual void v26() = 0;
	virtual Real getWaterHeight(const WaterHandle *water) = 0;
};

extern "C" TerrainVisualDispatch *g_bfmeTerrainVisual;
extern "C" WaterHandle g_bfmeGridWaterHandle;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ);
};

Bool TerrainLogic::isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ)
{
	TerrainLogicDispatch *self = reinterpret_cast<TerrainLogicDispatch *>(this);
	const WaterHandle *water = self->getWaterHandle(x, y);
	if (water == 0) {
		return false;
	}

	Real waterHeight = 0.0f;
	if (water == &g_bfmeGridWaterHandle) {
		g_bfmeTerrainVisual->getWaterGridHeight(x, y, &waterHeight);
	} else {
		waterHeight = self->getWaterHeight(water);
	}

	if (waterZ != 0) {
		*waterZ = waterHeight;
	}

	Real terrainHeight = self->getGroundHeight(x, y, 0);
	if (terrainZ != 0) {
		*terrainZ = terrainHeight;
	}

	return terrainHeight < waterHeight;
}

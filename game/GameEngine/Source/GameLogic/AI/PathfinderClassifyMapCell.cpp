// cl: /Igame/Libraries/Source/WWVegas/WWMath
// ?classifyMapCell@Pathfinder@@SAXHHPAVPathfindCell@@@Z
//
// Retail 0x003F7630, 732 bytes: BFME's Pathfinder::classifyMapCell, the Zero
// Hour twin in AIPathfind.cpp. The static cdecl (i, j, cell) ABI and name are
// pinned; the matched Pathfinder::classifyMap (0x003F9140) calls it through
// ILT 0x00010D2F for every cell. BFME adds two TerrainLogic (x, y) queries at
// vtable +0x58/+0x5C that set cell bits 21 and 24, skips the water test for
// cliff cells, requires the water to be deeper than the AI data value at
// +0x9C, and grades the cell's slope against the two limits at 0x012F1064
// into the two-bit field at bit 22. Slot, bit and field names keep their
// offsets: nothing witnesses their meaning.

typedef bool Bool;
typedef int Int;
typedef float Real;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, fabs)

#define PATHFIND_CELL_SIZE_F 10.0f

#include "coord3d.h"

// BFME's Coord3D has a user-declared constructor and destructor (coord3d.h);
// both are trivial and inline here. The non-POD corners are what give
// retail's frame: the top-left corner shares the height array's slot and the
// bottom-right corner sits above it with its Y kept in EBX.
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_WATER = 1,
		CELL_CLIFF = 2,
		CELL_OBSTACLE = 4
	};

	CellType getType(void) const { return (CellType)m_type; }
	void setPinched(Bool pinch) { m_pinched = pinch; }
	void setType(CellType type);

	void setBit21(Bool on)
	{
		if (on) m_bits |= 0x200000; else m_bits &= ~0x200000;
	}
	void setBit24(Bool on)
	{
		if (on) m_bits |= 0x1000000; else m_bits &= ~0x1000000;
	}

private:
	char m_bfmeHead[0x0c];
	union
	{
		struct
		{
			unsigned int m_type : 3;
			unsigned int m_flags : 4;
			unsigned int m_connectsToLayer : 4;
			unsigned int m_layer : 4;
			unsigned int m_unused : 3;
			unsigned int m_pinched : 1;
			unsigned int m_bits19 : 3;
			unsigned int m_slope22 : 2;
			unsigned int m_rest : 8;
		};
		unsigned int m_bits;
	};
public:
	void setSlope22(Int level) { m_slope22 = level; }
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C(); virtual void slot30();
	virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0);
	virtual Bool isCliffCell(Real x, Real y) const;
	virtual void slot54();
	virtual Bool slot58(Real x, Real y);
	virtual Bool slot5C(Real x, Real y);
};

struct Rva003F7630AiData
{
	char pad[0x9c];
	Real m_real9C;
};

class AI
{
public:
	const Rva003F7630AiData *getAiData() const { return m_aiData14; }

private:
	char pad[0x14];
	Rva003F7630AiData *m_aiData14;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern Real TheSlopeLimits[2];

class Pathfinder
{
public:
	static void classifyMapCell(Int i, Int j, PathfindCell *cell);
};

void Pathfinder::classifyMapCell(Int i, Int j, PathfindCell *cell)
{
	Coord3D bottomRightCorner, topLeftCorner;

	Bool hasObstacle = (cell->getType() == PathfindCell::CELL_OBSTACLE);

	topLeftCorner.y = (Real)j * PATHFIND_CELL_SIZE_F;
	bottomRightCorner.y = topLeftCorner.y + PATHFIND_CELL_SIZE_F;

	topLeftCorner.x = (Real)i * PATHFIND_CELL_SIZE_F;
	bottomRightCorner.x = topLeftCorner.x + PATHFIND_CELL_SIZE_F;

	cell->setPinched(false);

	PathfindCell::CellType type = PathfindCell::CELL_CLEAR;
	if (TheTerrainLogic->isCliffCell(topLeftCorner.x, topLeftCorner.y))
		type = PathfindCell::CELL_CLIFF;
	cell->setBit21(TheTerrainLogic->slot58(topLeftCorner.x, topLeftCorner.y));
	cell->setBit24(TheTerrainLogic->slot5C(topLeftCorner.x, topLeftCorner.y));

	if (type != PathfindCell::CELL_CLIFF)
	{
		Real maxDepth = TheAI->getAiData()->m_real9C;
		Real waterZ, terrainZ;
		if (TheTerrainLogic->isUnderwater(topLeftCorner.x, topLeftCorner.y, &waterZ, &terrainZ) && waterZ - terrainZ > maxDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(topLeftCorner.x, bottomRightCorner.y, &waterZ, &terrainZ) && waterZ - terrainZ > maxDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(bottomRightCorner.x, bottomRightCorner.y, &waterZ, &terrainZ) && waterZ - terrainZ > maxDepth)
			type = PathfindCell::CELL_WATER;
		if (TheTerrainLogic->isUnderwater(bottomRightCorner.x, topLeftCorner.y, &waterZ, &terrainZ) && waterZ - terrainZ > maxDepth)
			type = PathfindCell::CELL_WATER;
	}

	if (hasObstacle)
		type = PathfindCell::CELL_OBSTACLE;
	cell->setType(type);

	static const Real s_invDistance[3] =
	{
		1.0f / PATHFIND_CELL_SIZE_F,
		1.0f / PATHFIND_CELL_SIZE_F,
		1.0f / ((Real)sqrt(2.0f) * PATHFIND_CELL_SIZE_F)
	};

	Real height[4];
	height[0] = TheTerrainLogic->getGroundHeight(topLeftCorner.x, topLeftCorner.y);
	height[1] = TheTerrainLogic->getGroundHeight(topLeftCorner.x, bottomRightCorner.y);
	height[2] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x, topLeftCorner.y);
	height[3] = TheTerrainLogic->getGroundHeight(bottomRightCorner.x, bottomRightCorner.y);

	cell->setSlope22(0);
	for (Int n = 0; n < 2; n++)
	{
		if (TheSlopeLimits[n] != 0.0f)
		{
			Bool found = false;
			for (Int k = 0; k < 3; k++)
			{
				if (found)
					break;
				if ((Real)fabs((height[k + 1] - height[0]) * s_invDistance[k]) > TheSlopeLimits[n])
					found = true;
			}
			if (found)
				cell->setSlope22(n + 1);
		}
	}
}

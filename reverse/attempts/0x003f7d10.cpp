// ?d_003f7d10@@YAXXZ
// partial score=0.87 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Pathfinder::classifyFence, retail 0x003F7D10, 690 bytes.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// ZH's classifyFence walks a fence footprint in cell steps, marking each
// cell as a fence obstacle (insert) or clearing it (remove). BFME resolves
// the fence width/offset through the INI override chain instead of calling
// the template getters directly, and tracks cellBounds with MAX_INT/-1
// sentinels rather than seeding lo from the object's own cell.

typedef float Real;
typedef int Int;
typedef bool Bool;

#define PATHFIND_CELL_SIZE_F 10.0f

extern "C" float __cdecl cosf(float);
extern "C" float __cdecl sinf(float);
extern "C" __declspec(dllimport) double BfmeFloorER(double x);
extern "C" __declspec(dllimport) double bfmeMathVE(double x);

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	Int loX, loY, hiX, hiY;
};

// Overridable::getFinalOverride is inline and recursive in the vendored
// header; declared-not-defined here so the one-level-unrolled chain walk
// below calls through the already-matched ILT 0x000022BB, same lever as
// ControlBar::findNonConstCommandButton.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	Overridable *m_override;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing/ThingTemplate.h
class ThingTemplateFence : public Overridable
{
public:
	char m_pad08[0x398 - 8];
	float m_fenceWidth;
	float m_fenceXOffset;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_pad00[4];
	ThingTemplateFence *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_position;
	float m_orientation;
	char m_pad48[0x74 - 0x48];
	unsigned int m_id;
};

// TU-local view of the already-matched state reset at 0x003F7380: an
// ICF-shared body reached here as PathfindCell::removeObstacle.
struct Rva003F7380Argument
{
	unsigned char m_padding[0x74];
	int m_value;
};

class Rva003F7380State
{
public:
	void resetIfMatching(const Rva003F7380Argument *argument);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	void setTypeAsObstacle(Object *obstacle, Bool isFence, const ICoord2D &pos);

private:
	char m_pad[16];
};

class PathfindZoneManager
{
public:
	void markZonesDirty(Bool a, Bool b);

private:
	Bool m_bfmeDirty;
};

static int RealToIntFloor(float v)
{
	float t = (float)BfmeFloorER((double)v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

static int RealToIntCeil(float v)
{
	float t = (float)bfmeMathVE((double)v);
	int i;
	__asm fld t
	__asm fistp i
	return i;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void classifyFence(Object *obj, Bool insert);

private:
	char m_pad00[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	char m_pad24[0xc9c - 0x24];
	PathfindZoneManager m_zoneManager;
};

void Pathfinder::classifyFence(Object *obj, Bool insert)
{
	const Coord3D *pos = &obj->m_position;
	Real angle = obj->m_orientation;

	ThingTemplateFence *widthTempl = obj->m_template;
	if (widthTempl != 0 && widthTempl->m_override != 0)
		widthTempl = (ThingTemplateFence *)widthTempl->m_override->getFinalOverride();
	Real halfsizeX = widthTempl->m_fenceWidth * 0.5f;

	Real halfsizeY = PATHFIND_CELL_SIZE_F / 10.0f;

	ThingTemplateFence *offsetTempl = obj->m_template;
	if (offsetTempl != 0 && offsetTempl->m_override != 0)
		offsetTempl = (ThingTemplateFence *)offsetTempl->m_override->getFinalOverride();
	Real fenceOffset = offsetTempl->m_fenceXOffset;

	Real c = cosf(angle);
	Real s = sinf(angle);

	const Real STEP_SIZE = PATHFIND_CELL_SIZE_F * 0.5f;
	Real ydx = s * STEP_SIZE;
	Real ydy = -c * STEP_SIZE;
	Real xdx = c * STEP_SIZE;
	Real xdy = s * STEP_SIZE;

	Int numStepsX = RealToIntCeil(2.0f * halfsizeX / STEP_SIZE);
	Int numStepsY = RealToIntCeil(2.0f * halfsizeY / STEP_SIZE);

	IRegion2D cellBounds;
	cellBounds.loX = 0x7fffffff;
	cellBounds.loY = 0x7fffffff;
	cellBounds.hiX = -1;
	cellBounds.hiY = -1;

	Real tl_x = pos->x - fenceOffset * c - halfsizeY * s;
	Real tl_y = pos->y + halfsizeY * c - fenceOffset * s;

	for (Int iy = 0; iy < numStepsY; ++iy, tl_x += ydx, tl_y += ydy)
	{
		Real x = tl_x;
		Real y = tl_y;
		for (Int ix = 0; ix < numStepsX; ++ix, x += xdx, y += xdy)
		{
			Int cx = RealToIntFloor((x + 0.5f) / PATHFIND_CELL_SIZE_F);
			Int cy = RealToIntFloor((y + 0.5f) / PATHFIND_CELL_SIZE_F);

			if (cx >= 0 && cy >= 0 && cx < m_extent.hiX && cy < m_extent.hiY)
			{
				if (insert)
				{
					ICoord2D cellPos;
					cellPos.x = cx;
					cellPos.y = cy;
					m_map[cx][cy].setTypeAsObstacle(obj, true, cellPos);
				}
				else
				{
					((Rva003F7380State *)&m_map[cx][cy])->resetIfMatching(
						(const Rva003F7380Argument *)obj);
				}

				if (cx < cellBounds.loX) cellBounds.loX = cx;
				if (cy < cellBounds.loY) cellBounds.loY = cy;
				cellBounds.hiX = (cx > cellBounds.hiX) ? cx : cellBounds.hiX;
				cellBounds.hiY = (cy > cellBounds.hiY) ? cy : cellBounds.hiY;
			}
		}
	}

	if (cellBounds.hiX != -1)
	{
		m_zoneManager.markZonesDirty(true, insert);
	}
}

// ?rva003F8820@Pathfinder@@QAEXPAVBridge@@_N@Z
// partial score=1.0 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc
// ?rva003F8820@Pathfinder@@QAEXPAVBridge@@_N@Z at retail RVA 0x003F8820, 1391 bytes
// (0x003F8820..0x003F8D8E, ret 8 at +0x491, int3 pad from +0x56F).
//
// Identity: a Pathfinder method (ECX is the Pathfinder: m_map@+0x10,
// m_extent@+0x14, m_layers[]@+0x85c stride 0x44, and it calls
// Pathfinder::worldToCell and Pathfinder::bfmeLayerForPosition on it). The
// first argument is a Bridge (ZH TerrainLogic.h layout: vptr, m_next@+4,
// m_bridgeInfo@+0xc copied as 27 dwords into a constructed BridgeInfo,
// m_bounds@+0x78); the second is a bool (tested as a byte). No retail string
// or ZH twin names the method, so the name keeps the address token. The
// symbols.csv pin ?releaseCell@Pathfinder@@QAEXPAVPathfindCell@@H@Z at this
// address spells a (PathfindCell*, int) ABI that retail's byte test of arg 2
// and its Bridge field reads contradict. The ledger's 1007-byte
// ?snapClosestGoalPosition@Pathfinder@@... MASM row at 0x003F89A0 is the
// interior +0x180 suffix of this body (refuted boundary, see re_attempts.log).

typedef int Int;
typedef bool Bool;
typedef float Real;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord2D { Real x, y; };
struct Region2D { Coord2D lo, hi; };
// Retail's by-value Coord3D argument records the argument block's esp in a
// dead frame slot (`mov [esp+N],esp`), which VC7.1 only emits for a class with
// a user-declared copy constructor and destructor.
struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	~Coord3D() {}
};

#define PATHFIND_CELL_SIZE_F 10.0f

// BFME's REAL_TO_INT_FLOOR/CEIL call the CRT through the import table, then
// round with fld/fistp (see inputs/reference/shims/pathfind/GameLogic/AIPathfind.h).
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline Real fast_float_ceil(Real f)
{
	return (Real)ceil((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define REAL_TO_INT_CEIL(x) (fast_float2long_round(fast_float_ceil(x)))

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class BridgeInfo
{
public:
	BridgeInfo();

	Coord3D from, to;
	Real bridgeWidth;
	Coord3D fromLeft, fromRight, toLeft, toRight;
	Int bridgeIndex;
	Int curDamageState;
	Int bridgeObjectID;
	Int towerObjectID[4];
	Bool damageStateChanged;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	virtual ~Bridge();

	void setNext(Bridge *pNext) { m_next = pNext; }
	Bridge *getNext(void) { return m_next; }
	void getBridgeInfo(BridgeInfo *pInfo) { *pInfo = m_bridgeInfo; }

	Bridge *m_next;
	void *m_templateName;
	BridgeInfo m_bridgeInfo;
	Region2D m_bounds;
	Int m_layer;
};

// Owner class of the matched setter ?bfmeSetMode@Gen_003F68B0@@QAEXI@Z
// (retail 0x003F68B0); retail calls it on a PathfindCell.
class Gen_003F68B0
{
public:
	void bfmeSetMode(unsigned int mode);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCellInfo
{
public:
	unsigned char m_pad00[0x20];
	Int m_at20;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// Retail 16-byte cell: packed dword@+0x0c, type:3@0, layer:6@6.
class PathfindCell
{
public:
	Int getLayer(void) const { return (Int)((m_packed >> 6) & 0x3f); }
	Int getType(void) const { return (Int)(m_packed & 7); }

	PathfindCellInfo *m_info;
	Int m_at04;
	Int m_at08;
	unsigned int m_packed;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	PathfindCell *getCell(Int cellX, Int cellY);
	void bfmeRememberEndpoint(const ICoord2D *cell);

	unsigned char m_pad00[0x40];
	Int m_at40;
};

// Retail calls the per-cell classifier (dump body 0x003F82C0) through its
// ILT ?j_0001a523@@YAXXZ; the pointer-to-member cast keeps ECX=this and the
// seven stack arguments while the relocation names the ledger's thunk.
extern void j_0001a523();
struct Rva003F82C0Classify
{
	void call(Int cellX, Int cellY, PathfindCell *cell, Bridge *theBridge, Bool keep,
		PathfindCell *bridgeCell, Real height);
};
typedef void (Rva003F82C0Classify::*Rva003F82C0Call)(Int, Int, PathfindCell *,
	Bridge *, Bool, PathfindCell *, Real);

extern Int g_rva012B4C34[8];	// i deltas of the eight neighbours
extern Int g_rva012B4C0C[8];	// j deltas of the eight neighbours

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void rva003F8820(Bridge *theBridge, Bool keep);
	Int bfmeLayerForPosition(Object *object, Coord3D position);
	Bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);

	__forceinline void classify(Int cellX, Int cellY, PathfindCell *cell, Bridge *theBridge,
		Bool keep, PathfindCell *bridgeCell, Real height)
	{
		union { void (*asFunction)(); Rva003F82C0Call asMember; } fnCast;
		fnCast.asFunction = j_0001a523;
		(reinterpret_cast<Rva003F82C0Classify *>(this)->*fnCast.asMember)(cellX, cellY, cell,
			theBridge, keep, bridgeCell, height);
	}

	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x858 - 0x24];
	Bridge *m_at858;
	PathfindLayer m_layers[16];
	unsigned char m_tail[0x243f4 - 0xc9c];
	Bool m_at243f4;
};

void Pathfinder::rva003F8820(Bridge *theBridge, Bool keep)
{
	Region2D bounds;
	bounds.lo.x = theBridge->m_bounds.lo.x;
	bounds.lo.y = theBridge->m_bounds.lo.y;
	bounds.hi.x = theBridge->m_bounds.hi.x;
	bounds.hi.y = theBridge->m_bounds.hi.y;

	if (!keep)
	{
		Bridge *prev = 0;
		Bridge *cur = m_at858;
		while (cur)
		{
			Bridge *next = cur->getNext();
			Region2D curBounds;
			curBounds.lo.x = cur->m_bounds.lo.x;
			curBounds.lo.y = cur->m_bounds.lo.y;
			curBounds.hi.x = cur->m_bounds.hi.x;
			curBounds.hi.y = cur->m_bounds.hi.y;
			Real dLoX = curBounds.lo.x - bounds.lo.x;
			Real dLoY = curBounds.lo.y - bounds.lo.y;
			Real dHiX = curBounds.hi.x - bounds.hi.x;
			Real dHiY = curBounds.hi.y - bounds.hi.y;
			if ((Real)fabs(dLoX) < 1.0f && (Real)fabs(dLoY) < 1.0f &&
				(Real)fabs(dHiX) < 1.0f && (Real)fabs(dHiY) < 1.0f)
			{
				if (prev)
					prev->setNext(next);
				else
					m_at858 = next;
				cur->setNext(0);
				delete cur;
			}
			else
			{
				prev = cur;
			}
			cur = next;
		}
	}

	Int layerA = 1;
	Int layerB = 1;
	Int rawA = 1;
	Int rawB = 1;
	if (keep)
	{
		BridgeInfo info;
		theBridge->getBridgeInfo(&info);

		rawA = layerA = bfmeLayerForPosition(0, info.from);
		if (layerA >= 2 && layerA <= 15)
		{
			ICoord2D endpointCell;
			worldToCell(&info.from, &endpointCell);
			m_layers[layerA].bfmeRememberEndpoint(&endpointCell);
		}
		else
		{
			layerA = 1;
		}

		rawB = layerB = bfmeLayerForPosition(0, info.to);
		if (layerB >= 2 && layerB <= 15)
		{
			ICoord2D endpointCell;
			worldToCell(&info.to, &endpointCell);
			m_layers[layerB].bfmeRememberEndpoint(&endpointCell);
		}
		else
		{
			layerB = 1;
		}
	}

	Int cellLoX = REAL_TO_INT_FLOOR((bounds.lo.x - 0.1f) / PATHFIND_CELL_SIZE_F);
	Int cellLoY = REAL_TO_INT_FLOOR((bounds.lo.y - 0.1f) / PATHFIND_CELL_SIZE_F);
	Int cellHiX = REAL_TO_INT_CEIL((bounds.hi.x + 0.1f) / PATHFIND_CELL_SIZE_F);
	Int cellHiY = REAL_TO_INT_CEIL((bounds.hi.y + 0.1f) / PATHFIND_CELL_SIZE_F);
	cellLoX -= 2;
	cellLoY -= 2;
	cellHiX += 2;
	cellHiY += 2;
	if (cellLoX < m_extent.lo.x)
		cellLoX = m_extent.lo.x;
	if (cellLoY < m_extent.lo.y)
		cellLoY = m_extent.lo.y;
	if (cellHiX > m_extent.hi.x)
		cellHiX = m_extent.hi.x;
	if (cellHiY > m_extent.hi.y)
		cellHiY = m_extent.hi.y;

	Int i, j;
	if (m_at243f4 || !keep || (layerA >= 2 && layerA <= 15) || (layerB >= 2 && layerB <= 15))
	{
		for (i = cellLoX; i <= cellHiX; i++)
		{
			for (j = cellLoY; j <= cellHiY; j++)
			{
				PathfindCell *bridgeCell = 0;
				Real height = 0.0f;
				if (layerA != 1)
				{
					bridgeCell = m_layers[layerA].getCell(i, j);
					height = (Real)m_layers[layerA].m_at40;
				}
				if (bridgeCell == 0 && layerB != 1)
				{
					bridgeCell = m_layers[layerB].getCell(i, j);
					height = (Real)m_layers[layerB].m_at40;
				}
				classify(i, j, &m_map[i][j], theBridge, keep, bridgeCell, height);
			}
		}
	}

	if (keep && (layerA != 1 || layerB != 1) && rawA != 1 && rawB != 1)
	{
		for (i = cellLoX + 1; i <= cellHiX - 1; i++)
		{
			for (j = cellLoY + 1; j <= cellHiY - 1; j++)
			{
				PathfindCell *cell = &m_map[i][j];
				if (cell->getLayer() == 16 && cell->getType() != 5)
				{
					for (Int k = 0; k < 8; k++)
					{
						PathfindCell *adj = &m_map[i + g_rva012B4C34[k]][j + g_rva012B4C0C[k]];
						if (adj->getLayer() != 16 && adj->getType() != 5 && adj->getLayer() == 1 &&
							(adj->m_info == 0 || adj->m_info->m_at20 == 0))
						{
							((Gen_003F68B0 *)adj)->bfmeSetMode(2);
						}
					}
				}
			}
		}
	}
}

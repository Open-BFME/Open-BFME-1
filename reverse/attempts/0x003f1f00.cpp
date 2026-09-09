// ?iterateCellsAlongLine@Pathfinder@@IAEHABUICoord2D@@0W4PathfindLayerEnum@@PAX@Z
// partial score=0.94 date=2026-09-09
// cl: /DNDEBUG /MD
//
// Retail 0x003F1F00: byte-for-byte the SAME Bresenham shape as the sibling
// analysis at 0x003E3190 (reverse/attempts/0x003e3190.cpp) -- identical
// offsets for delta_x/delta_y/den/numadd, identical getCell() inline chain
// (same call 0x0000105CD thunk), identical push order into the per-cell
// callback, and the SAME dead-return-value "xor eax,eax" at every early-out
// (consistent here since this signature genuinely returns Int, unlike the
// suspect void identity logged for 0x003ED9F0's row).  The only byte
// differences from 0x3E3190 are the callback call target -- here 0x0002839E,
// an ILT thunk already claimed by ?j_0002839e@@YAXXZ (functions.csv
// target=FUN_007F1840) -- and userData being a raw void* here (PAX) instead
// of a typed struct pointer, cast internally the way ZH's real
// tightenPathCallback casts its void* userData to TightenPathStruct*
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameLogic/AI/AIPathfind.cpp:8407-8434 -- 0x003F1F00's other caller per
// reverse/reloc_names.csv is Pathfinder::tightenPath).
//
// NEEDS THIS PIN to resolve the callback call byte-exact (drop it when you
// park without landing -- add_match only writes it once the body matches):
//   ?process@PathfinderCellCallbackStruct@@QAEHPAVPathfindCell@@0HH@Z,0x0002839E,route=0x007F1840; retail iterateCellsAlongLine@Pathfinder@0x003F1F00 callback call reaches this real target only through the ILT thunk already claimed by ?j_0002839e@@YAXXZ
//
// Same blocker as 0x3E3190 and (once its identity is corrected) 0x3ED9F0:
// with the pin in place the call resolves exactly and the ONLY remaining
// diff is the register allocator's scratch-stack-slot rotation for
// den/numadd/from (retail 0x28/0x24/0x20 vs this TU's 0x24/0x20/0x28) --
// proven unreachable via source-level control across three prior sessions
// on 0x3E3190 (G5/G6/G7/Ot/Og/Oy- sweep, declaration-order permutations,
// statement reordering). Not re-swept here; same family, same verdict.
//
// Confirmed this session: with the pin above in place, explain_mismatch's
// classification moves from "unresolved REL32 call" to "instruction/
// register encoding mismatch" and the diff is ~31 lines, all in the same
// den/numadd/from region -- i.e. this really is the same blocker, not a
// coincidence of the brief's wording.

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class PathfindCell
{
public:
	char m_unreconstructed[0x10];
};

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	char m_unreconstructed[0x44];
};

// Stand-in for whichever real userData struct casts out of the raw void* at
// this call site (tightenPath's TightenPathStruct in ZH); nothing in the
// emitted bytes depends on its real layout, only on the thiscall shape of
// the member it calls through.
struct PathfinderCellCallbackStruct
{
	Int process( PathfindCell *from, PathfindCell *to, Int x, Int y );
};

class Pathfinder
{
protected:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, void *userData );

private:
	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y )
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell( x, y );
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}
};

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	void *userDataVoid )
{
	PathfinderCellCallbackStruct *userData =
		(PathfinderCellCallbackStruct *)userDataVoid;

	const ICoord2D *start_ptr = &start;
	const ICoord2D *end_ptr = &end;
	Int end_x = end_ptr->x;
	Int x = start_ptr->x;
	Int delta_x = abs( end_x - x );
	Int y = start_ptr->y;
	Int end_y = end_ptr->y;
	Int delta_y = abs( end_y - y );

	Int numpixels, num, numadd, den;
	Int xinc1, xinc2, yinc1, yinc2;
	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (start.x > end_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	PathfindCell *from = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return 0;

		Int ret = userData->process( from, to, x, y );
		if (ret != 0)
			return ret;

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
		from = to;
	}

	return 0;
}

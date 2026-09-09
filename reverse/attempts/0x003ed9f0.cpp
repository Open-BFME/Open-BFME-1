// ?iterateCellsAlongLine@Pathfinder@@AAEXPBUICoord2D@@0W4PathfindLayerEnum@@PAUMADStruct@@@Z
// partial score=0.55 date=2026-09-09
// cl: /DNDEBUG /MD
//
// Retail 0x003ED9F0 is byte-for-byte the SAME Bresenham shape as the
// analysis at 0x003E3190 (reverse/attempts/0x003e3190.cpp) -- identical
// offsets for delta_x/delta_y/den/numadd, identical getCell() inline chain
// (same call 0x0000105CD thunk), identical push order into the per-cell
// callback (ecx=from, push y,x,to,from; mov ecx=userData; call [thunk]).
// The only byte differences from 0x3E3190 are the callback call target --
// here 0x00023114, an ILT thunk already claimed by ?j_00023114@@YAXXZ
// (functions.csv target=FUN_007EC070).
//
// THE CANDIDATE'S RETURN TYPE LOOKS WRONG.  The row's mangled name (from
// tools/next_work.py's named tier / reverse/reloc_names.csv) decodes AAEX =
// private, thiscall, returns VOID.  But retail's shared exit (delta<=0
// early-out, getCell-null early-out, and loop-exhausted) all fall into a
// "33 c0  xor eax,eax" right before the pop/pop/pop/pop; add esp,0x2c
// epilogue -- the same dead-return-value pattern 0x3E3190 uses for its real
// `return 0;`.  A genuinely void function does not emit that.  Proof, done
// this session: recompiling this exact body with the return type changed to
// Int (`return 0;` / `return ret;`, otherwise byte-identical source) mangles
// to ?iterateCellsAlongLine@Pathfinder@@AAEHPBUICoord2D@@0W4PathfindLayerEnum@@PAUMADStruct@@@Z
// (AAEH, one letter different) and reproduces retail EXACTLY through the
// whole shared-exit region that this void version gets wrong -- the compiled
// size even matches (478 raw / 475 compared, same as 0x3E3190) instead of
// this void version's 472.  The remaining diff after that correction is the
// IDENTICAL 32-line den/numadd/from stack-slot rotation (retail 0x28/0x24/
// 0x20, ours 0x24/0x20/0x28) already proven unreachable at 0x3E3190 across
// three sessions (flag sweep, declaration-order permutations, statement
// reordering all tried and logged there) -- so correcting the identity does
// NOT unblock landing by itself, but it is the right identity to converge
// the family on.  Whoever revisits this row should first decide whether to
// correct reverse/reloc_names.csv's return-type letter for 0x003ED9F0 (or
// re-derive why AAEX was chosen -- the citing file's own note says "nothing
// in the emitted bytes depends on the type", i.e. the type letters were
// inferred, not read off the bytes) before spending more time on register
// allocation here; landing under the void identity as literally given is
// not possible, it compiles 3 bytes short with a structurally different
// shared exit.
//
// This stash keeps the GIVEN (void) identity so it still fills the row
// next_work.py serves; see the note above for the corrected Int-return body.
//
// NEEDS THIS PIN for the callback call (drop when parking without landing):
//   ?process@MADStruct@@QAEHPAVPathfindCell@@0HH@Z,0x00023114,route=0x007EC070; retail iterateCellsAlongLine@Pathfinder@0x003ED9F0 callback call reaches this real target only through the ILT thunk already claimed by ?j_00023114@@YAXXZ

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

struct MADStruct
{
	Int process( PathfindCell *from, PathfindCell *to, Int x, Int y );
};

class Pathfinder
{
private:
	void iterateCellsAlongLine( const ICoord2D *start, const ICoord2D *end,
		PathfindLayerEnum layer, MADStruct *userData );

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

void Pathfinder::iterateCellsAlongLine( const ICoord2D *start,
	const ICoord2D *end, PathfindLayerEnum layer,
	MADStruct *userData )
{
	const ICoord2D *start_ptr = start;
	const ICoord2D *end_ptr = end;
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

	if (start->x > end_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start->y > end_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	PathfindCell *from = 0;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *to = getCell( layer, x, y );
		if (to == 0)
			return;

		Int ret = userData->process( from, to, x, y );
		if (ret != 0)
			return;

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
}

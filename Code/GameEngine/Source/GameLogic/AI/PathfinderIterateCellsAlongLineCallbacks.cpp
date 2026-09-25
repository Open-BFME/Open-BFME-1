// cl: /DNDEBUG /MD
//
// Eight of retail's cell-space Pathfinder::iterateCellsAlongLine instances, one
// 478-byte body each, byte-identical apart from the callback they call:
//
//   0x003DE480  ILT 0x00005713  Rva003DE480Struct       -> Rva003D61C0::cellCallback
//   0x003E2F30  ILT 0x00031C50  ExamineCellsStruct      -> ExamineCellsStruct::cellCallback
//   0x003E33F0  ILT 0x00013DC2  GroundPathPassableInfo  -> GroundPathPassableStruct::cellCallback
//   0x003E7F80  ILT 0x00029DF7  BfmeCheckMovementInfo   -> Rva003E5820Info::examine
//   0x003E81E0  ILT 0x00023DDF  Rva003DB640Info         -> LinePassableStruct::linePassableCallback
//   0x003E8440  ILT 0x0001DAA2  Rva003E5A50Info         -> Rva003E5A50Info::rva003e5b80
//   0x003F1CA0  ILT 0x0003EBC1  Rva003F1CA0Struct       -> Rva003EE9F0::run
//   0x003F1F00  ILT 0x000190B0  void (tightenPath)      -> TightenPathCallbackInfo::cellCallback
//
// Retail drops ZH's CellAlongLineProc parameter and instantiates the walk per
// user-data type (see pathfind_iterateCellsAlongLine_world.cpp); the walk
// itself is the MADStruct one in PathfinderIterateCellsAlongLineMADStruct.cpp.
// Each overload keeps the user-data spelling its byte-true caller pins, and the
// callback is reached through the class its own matched body is named on: the
// walker passes the user data as the callback's `this`, so the two names are
// one object (PathfinderLineQueries.cpp records the same aliasing).

extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)

typedef int Int;

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
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	char m_unreconstructed[0x44];
};

class Rva003D61C0
{
public:
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

struct ExamineCellsStruct
{
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class TightenPathCallbackInfo
{
public:
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class GroundPathPassableStruct
{
public:
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

struct ObstacleCellStruct
{
public:
	Int cellCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class Rva003E5820Info
{
public:
	Int examine( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class LinePassableStruct
{
public:
	Int linePassableCallback( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class Rva003E5A50Info
{
public:
	Int rva003e5b80( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

class Rva003EE9F0
{
public:
	Int run( PathfindCell *previousCell, PathfindCell *currentCell, Int cellX, Int cellY );
};

struct GroundPathPassableInfo;
struct Rva003DE480Struct;
class BfmeCheckMovementInfo;
class Rva003DB640Info;
struct Rva003F1CA0Struct;

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003DE480Struct *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, BfmeCheckMovementInfo *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003DB640Info *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003E5A50Info *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003F1CA0Struct *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, ExamineCellsStruct *callbackInfo );
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, ObstacleCellStruct *callbackInfo );

protected:
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, void *callbackInfo );

private:
	Int iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, GroundPathPassableInfo *callbackInfo );

	char m_beforeMap[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];

	__forceinline PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}

	template <class Owner, Int (Owner::*Callback)( PathfindCell *, PathfindCell *, Int, Int )>
	__forceinline Int walkCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Owner *callbackInfo )
	{
		Int delta_x = abs( destinationCell.x - startCell.x );
		Int delta_y = abs( destinationCell.y - startCell.y );

		Int xinc2, yinc1, xinc1, numpixels, numadd, den;
		Int yinc2, num;
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

		if (startCell.x > destinationCell.x)
		{
			xinc2 = -xinc2;
			xinc1 = -1;
		}
		if (startCell.y > destinationCell.y)
		{
			yinc2 = -yinc2;
			yinc1 = -1;
		}

		Int x = startCell.x;
		Int y = startCell.y;
		PathfindCell *from = 0;
		for (Int curpixel = 0; curpixel < numpixels; curpixel++)
		{
			PathfindCell *to = getCell( layer, x, y );
			if (to == 0)
				return 0;

			Int ret = (callbackInfo->*Callback)( from, to, x, y );
			if (ret != 0)
				return ret;
			from = to;

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
		}

		return 0;
	}
};

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, Rva003DE480Struct *callbackInfo )
{
	return walkCellsAlongLine<Rva003D61C0, &Rva003D61C0::cellCallback>(
		startCell, destinationCell, layer, (Rva003D61C0 *)callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, GroundPathPassableInfo *callbackInfo )
{
	return walkCellsAlongLine<GroundPathPassableStruct, &GroundPathPassableStruct::cellCallback>(
		startCell, destinationCell, layer, (GroundPathPassableStruct *)callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, BfmeCheckMovementInfo *callbackInfo )
{
	return walkCellsAlongLine<Rva003E5820Info, &Rva003E5820Info::examine>(
		startCell, destinationCell, layer, (Rva003E5820Info *)callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, Rva003DB640Info *callbackInfo )
{
	return walkCellsAlongLine<LinePassableStruct, &LinePassableStruct::linePassableCallback>(
		startCell, destinationCell, layer, (LinePassableStruct *)callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, Rva003E5A50Info *callbackInfo )
{
	return walkCellsAlongLine<Rva003E5A50Info, &Rva003E5A50Info::rva003e5b80>(
		startCell, destinationCell, layer, callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, Rva003F1CA0Struct *callbackInfo )
{
	return walkCellsAlongLine<Rva003EE9F0, &Rva003EE9F0::run>(
		startCell, destinationCell, layer, (Rva003EE9F0 *)callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, ObstacleCellStruct *callbackInfo )
{
	return walkCellsAlongLine<ObstacleCellStruct, &ObstacleCellStruct::cellCallback>(
		startCell, destinationCell, layer, callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, ExamineCellsStruct *callbackInfo )
{
	return walkCellsAlongLine<ExamineCellsStruct, &ExamineCellsStruct::cellCallback>(
		startCell, destinationCell, layer, callbackInfo );
}

Int Pathfinder::iterateCellsAlongLine( const ICoord2D &startCell, const ICoord2D &destinationCell,
	PathfindLayerEnum layer, void *callbackInfo )
{
	return walkCellsAlongLine<TightenPathCallbackInfo, &TightenPathCallbackInfo::cellCallback>(
		startCell, destinationCell, layer, (TightenPathCallbackInfo *)callbackInfo );
}

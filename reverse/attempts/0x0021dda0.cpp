// ?findClosestFreeGarrisonPointIndex@GarrisonContain@@IAEHHPBUCoord3D@@@Z
// partial score=0.72 date=2026-09-09
// Full-source bank for the 653-byte body at retail RVA 0x0021DDA0.
//
// Identity is supported by the full Ghidra boundary and named callers from
// GarrisonContain::calcBestGarrisonPosition (0x0021E130),
// putObjectAtBestGarrisonPoint (0x0021E1C0),
// attemptBestFirePointPosition (0x0021E5D0), and trackTargets (0x0021E6C0).
// The active production ZH loop was not changed.  Retail's BFME layout is
// recovered from the GarrisonContain constructor/loadGarrisonPoints bodies:
// point records begin at +0xD8 with a 0x14-byte object-first record, the
// point-in-use count is +0x3F8, point coordinates begin at +0x3FC with a
// 40-point condition stride, and per-condition counts begin at +0x99C.
//
// The source below is a complete semantic reconstruction, but it was not
// compiled after the earlier 1158-byte ZH-layout probe (retail 653 bytes,
// 605 non-relocation differences, first at body offset +8).  It is therefore
// evidence for the next converter, not a production claim.

#include <float.h>

typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
};

template <typename T>
inline T sqr( T value )
{
	return value * value;
}

inline Real calcDistSqr( const Coord3D &a, const Coord3D &b )
{
	return sqr( a.x - b.x ) + sqr( a.y - b.y ) + sqr( a.z - b.z );
}

class GarrisonContain
{
public:
	Int findClosestFreeGarrisonPointIndex( Int conditionIndex,
		const Coord3D *targetPos );
};

// ?findClosestFreeGarrisonPointIndex@GarrisonContain@@IAEHHPBUCoord3D@@@Z
Int GarrisonContain::findClosestFreeGarrisonPointIndex( Int conditionIndex,
	const Coord3D *targetPos )
{
	if ( targetPos == 0 )
		return -1;

	const char *base = reinterpret_cast<const char *>( this );
	Int pointsInUse = *reinterpret_cast<const Int *>( base + 0x3F8 );
	if ( pointsInUse == 40 )
		return -1;

	Int pointCount = *reinterpret_cast<const Int *>(
		base + 0x99C + conditionIndex * sizeof( Int ) );
	if ( pointsInUse >= pointCount )
		return -1;

	Object *owner = *reinterpret_cast<Object *const *>( base + 0x08 );
	const Coord3D *ownerPos = reinterpret_cast<const Coord3D *>(
		reinterpret_cast<const char *>( owner ) + 0x38 );

	if ( targetPos->x == ownerPos->x &&
		targetPos->y == ownerPos->y &&
		targetPos->z == ownerPos->z )
	{
		Object *const *pointObjects = reinterpret_cast<Object *const *>(
			base + 0xD8 );
		for ( Int i = 0; i < 40; ++i )
		{
			if ( pointObjects[ i * 5 ] == 0 )
				return conditionIndex;
		}
		return conditionIndex;
	}

	Object *const *pointObjects = reinterpret_cast<Object *const *>(
		base + 0xD8 );
	const Coord3D *pointPositions = reinterpret_cast<const Coord3D *>(
		base + 0x3FC );
	Real closestDistSq = FLT_MAX;
	Int closestIndex = -1;

	for ( Int i = 0; i < pointCount; ++i )
	{
		if ( pointObjects[ i * 5 ] == 0 )
		{
			const Coord3D &point = pointPositions[ conditionIndex * 40 + i ];
			Real distSq = calcDistSqr( *targetPos, point );
			if ( distSq < closestDistSq )
			{
				closestDistSq = distSq;
				closestIndex = i;
			}
		}
	}

	return closestIndex;
}

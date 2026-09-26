// ?d_00206b40@@YAXXZ
// partial score=0.26 date=2026-09-21
// cl: /DNDEBUG /MD
// Retail 0x00206B40, 295 bytes. Finds an Object by id, syncs this-0x20 via
// the pinned bfmeTwoCFD, then scans a pointer array at this+4..this+8 for
// the nearest not-yet-claimed (+0x20==0) item whose owner/override chain
// passes an Overridable check and whose own +4 is clear, tracking the
// closest by 3D distance to a fixed anchor (the array's first element),
// and finally stores the found id (param) into the closest item's +0x20.
// No caller/vtable/string identity; address-derived receiver and fields.

typedef int Int;

extern "C" double sqrt( double value );

class BfmeOuterCFD
{
public:
	void bfmeTwoCFD();
};

class GameLogic
{
public:
	void *findObjectByID( Int id );
};

#define TheBfmeGameLogic ( *(GameLogic **)0x012F0898 )

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_unmodelled000[ 0xd8 ];
	Int m_flagsD8;
};

class BfmeSubBIA
{
public:
	Overridable *ask();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ArrayItem
{
public:
	Int m_claimed20;
	Int m_ownerField4;
	Coord3D m_position;
};

class Rva00206B40Owner
{
public:
	Int rva00206b40( Int id );

private:
	char m_unmodelled000[ 4 ];
	ArrayItem **m_arrayBegin;
	ArrayItem **m_arrayEnd;
};

Int Rva00206B40Owner::rva00206b40( Int id )
{
	void *found = TheBfmeGameLogic->findObjectByID( id );
	if ( found == 0 )
		return -1;

	reinterpret_cast<BfmeOuterCFD *>(
		reinterpret_cast<char *>( this ) - 0x20 )->bfmeTwoCFD();

	ArrayItem **begin = m_arrayBegin;
	ArrayItem **end = m_arrayEnd;
	Int count = ( end - begin );

	Int result = -1;
	if ( count == 0 )
		return result;

	ArrayItem *anchor = *begin;
	float bestDistance = 100001.0f;
	Int bestIndex = -1;

	for ( Int i = 0; i < count; ++i )
	{
		ArrayItem *item = begin[ i ];
		if ( item->m_claimed20 != 0 )
			continue;

		if ( anchor->m_ownerField4 != 0 )
		{
			BfmeSubBIA *ownerField = reinterpret_cast<BfmeSubBIA *>(
				anchor->m_ownerField4 );
			if ( *reinterpret_cast<void **>( reinterpret_cast<char *>( ownerField ) + 4 ) != 0 )
			{
				Overridable *nested = *reinterpret_cast<Overridable **>(
					reinterpret_cast<char *>( ownerField ) + 4 );
				const Overridable *override_ = nested->getFinalOverride();
				if ( const_cast<Overridable *>( override_ )->m_flagsD8 & 0x40000 )
					continue;
			}
		}

		if ( item->m_ownerField4 != 0 )
			continue;

		float dx = item->m_position.x - anchor->m_position.x;
		float dy = item->m_position.y - anchor->m_position.y;
		float dz = item->m_position.z - anchor->m_position.z;
		float distance = (float)sqrt( dx * dx + dy * dy + dz * dz );

		if ( distance < bestDistance )
		{
			bestDistance = distance;
			bestIndex = i;
		}
	}

	if ( bestIndex < 0 )
		return result;

	begin[ bestIndex ]->m_claimed20 = id;
	return result;
}

// ?rva001f96e0@DynamicPortalBehaviour@@QAEXXZ
// partial score=0.5 date=2026-09-24
// ?dup_001f96e0@@YAXXZ
// Retail 0x001F96E0 / 979 bytes.  DynamicPortalBehaviour receiver layout is
// proven by ctor/vtable (caller 0x001F9C20 is vtable 0x010A3950 slot 1;
// neighbour ctor 0x001F8B80 installs DynamicPortalBehaviour's primary/Create
// vtables), but this private method has no proved semantic name, so it stays
// address-derived under the proven owner.
//
// The body builds BFME waypoint objects from the module's bone positions and
// then links the copied integer paths.  The small local types below are
// deliberately scoped to this reconstruction: their offsets are witnessed by
// the retail stores, while their semantic owners are not.

// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath

#include "coord3d.h"
#include <string.h>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;

// Retail's real Coord3D() / ~Coord3D() (0x00016C93 / 0x0001364C, both empty)
// are what make MSVC emit the ??_L/??_M array-with-cleanup helpers for a
// local Coord3D[16] -- no hand-rolled array-new/delete shim is needed.

class Matrix3D;

// upstream layout: witnessed by the retail call at this body's +0x7d, which
// pushes (prefix, module->0x70, positions, 0, 1, 0) into the real, already
// matched ?getMultiLogicalBonePosition@Object@@... row.
class Object
{
public:
	Int getMultiLogicalBonePosition( const char *boneNamePrefix, Int maxBones,
		Coord3D *positions, Matrix3D *transforms, Bool convertToWorld, Int extra ) const;

private:
	unsigned char m_pad00[0x74];
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() {}

	const char *text( void ) const
	{
		if (m_data == 0)
			return 0;
		return (const char *)m_data + 8;
	}

private:
	void *m_data;
};

// Retail's 0x00887B60 copy body is ICF-folded under this name.  Its live
// payload for this call site is one pointer, not the unrelated 0x20-byte
// network-room record that shares the printed ICF name elsewhere.
class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom( const GameSpyGroupRoom &other );
	~GameSpyGroupRoom() {}

private:
	void *m_data;
};

class Rva001F96E0Waypoint
{
public:
	unsigned char m_storage[0xb0];
};

struct Rva001F96E0Pair
{
	UnsignedInt index;
	UnsignedInt kind;
};

// Witnessed 12-byte width: module->m_nested.begin sits at module+0xB4, not
// +0xB0, so this vector carries a third (unread) capacity-style slot exactly
// like Rva001F96E0IntVector below.
struct Rva001F96E0PairVector
{
	Rva001F96E0Pair *begin;
	Rva001F96E0Pair *end;
	Rva001F96E0Pair *capacity;
};

struct Rva001F96E0IntVector
{
	int *begin;
	int *end;
	int *capacity;
};

// Witnessed 12-byte width: module->m_flagc5/m_valueDC only land on their
// named offsets (0xC5 / 0xDC) when this vector is 12 bytes, not 8.
struct Rva001F96E0NestedVector
{
	Rva001F96E0IntVector *begin;
	Rva001F96E0IntVector *end;
	Rva001F96E0IntVector *capacity;
};

namespace _STL
{
	template <bool Threads, int Instance>
	class __node_alloc
	{
	public:
		static void _M_deallocate( void *, unsigned int );
	};
}

class Rva001F96E0ModuleData
{
public:
	unsigned char m_pad00[0x70];
	UnsignedInt m_value70;
	unsigned char m_pad74[0x30];
	BFMERetailAsciiString m_bonePrefix;
	Rva001F96E0PairVector m_pairs;
	Rva001F96E0NestedVector m_nested;
	unsigned char m_padc0[5];
	unsigned char m_flagc5;
	unsigned char m_padc6[0x16];
	Real m_valueDC;
};

class Rva001F96E0Pathfinder
{
};

class Rva001F96E0AI
{
public:
	unsigned char m_pad00[0x0c];
	Rva001F96E0Pathfinder *m_pathfinder;
};

class Rva001F96E0GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern void j_0001adb1( void );
extern void j_000212d3( void );
extern void j_0003793e( void );
extern void j_0003cf51( void );

typedef void (Rva001F96E0Waypoint::*Rva001F96E0WaypointCtor)(
	UnsignedInt, BFMERetailAsciiString,
	const Coord3D *, GameSpyGroupRoom, GameSpyGroupRoom, GameSpyGroupRoom,
	unsigned char, UnsignedInt, GameSpyGroupRoom );
typedef int (Rva001F96E0IntVector::*Rva001F96E0NestedValue)(
	unsigned char * );
typedef void (Rva001F96E0IntVector::*Rva001F96E0VectorCtor)(
	int, int );
typedef void (Rva001F96E0Pathfinder::*Rva001F96E0PathAdd)(
	Rva001F96E0Waypoint * );

class DynamicPortalBehaviour
{
public:
	void rva001f96e0( void );
};

void DynamicPortalBehaviour::rva001f96e0( void )
{
	unsigned char *owner = (unsigned char *)this;
	Coord3D positions[16];

	unsigned char wasBuilt = *(owner + 0x3c);
	Rva001F96E0ModuleData *module =
		*(Rva001F96E0ModuleData **)(owner + 4);
	Object *object =
		*(Object **)(owner + 8);

	if (wasBuilt == 0)
	{
		const char *prefix = module->m_bonePrefix.text();
		if (prefix == 0)
			prefix = (const char *)0x0107388b;

		object->getMultiLogicalBonePosition( prefix, (Int)module->m_value70,
			positions, 0, true, 0 );

		int frameDelta = 0;
		if (module->m_valueDC != *(const Real *)0x01075350)
		{
			Rva001F96E0GameLogic *logic =
				*(Rva001F96E0GameLogic **)0x012f0898;
			Real scaled = module->m_valueDC * *(const Real *)0x010a39c4;
			frameDelta = (int)scaled;
			frameDelta = (int)logic->m_frame - frameDelta;
		}

		UnsignedInt objectField74 =
			*(const UnsignedInt *)((const unsigned char *)object + 0x74);

		Rva001F96E0Pair *pair = module->m_pairs.begin;
		Rva001F96E0Pair *pairEnd = module->m_pairs.end;
		while (pair != pairEnd)
		{
			UnsignedInt index = pair->index;
			const Coord3D *location = positions + index;
			void *rawWaypoint = ::operator new( 0xb0 );
			if (rawWaypoint != 0)
			{
				Rva001F96E0Waypoint *waypoint =
					(Rva001F96E0Waypoint *)rawWaypoint;
				union
				{
					void (*raw)( void );
					Rva001F96E0WaypointCtor member;
				} constructWaypoint;
				constructWaypoint.raw = j_0001adb1;
				(waypoint->*constructWaypoint.member)( 0x7ffffffe,
					BFMERetailAsciiString( (const char *)0x010a39ac ),
					location,
					*(const GameSpyGroupRoom *)0x01336e50,
					*(const GameSpyGroupRoom *)0x01336e50,
					*(const GameSpyGroupRoom *)0x01336e50,
					(unsigned char)0,
					module->m_value70,
					*(const GameSpyGroupRoom *)0x01336e50 );

				*(UnsignedInt *)((unsigned char *)waypoint + 0xa8) = objectField74;
				*(unsigned char *)((unsigned char *)waypoint + 0x68) = 1;

				UnsignedInt *dst6c = (UnsignedInt *)((unsigned char *)waypoint + 0x6c);
				const UnsignedInt *src74 = (const UnsignedInt *)((const unsigned char *)module + 0x74);
				dst6c[0] = src74[0];
				dst6c[1] = src74[1];
				dst6c[2] = src74[2];
				dst6c[3] = src74[3];
				dst6c[4] = src74[4];
				dst6c[5] = src74[5];

				*(unsigned char *)((unsigned char *)waypoint + 0x84) = 1;

				UnsignedInt *dst88 = (UnsignedInt *)((unsigned char *)waypoint + 0x88);
				const UnsignedInt *src8c = (const UnsignedInt *)((const unsigned char *)module + 0x8c);
				dst88[0] = src8c[0];
				dst88[1] = src8c[1];
				dst88[2] = src8c[2];
				dst88[3] = src8c[3];
				dst88[4] = src8c[4];
				dst88[5] = src8c[5];

				*(unsigned char *)((unsigned char *)waypoint + 0xa0) =
					module->m_flagc5;
				if (frameDelta > 0)
					*(UnsignedInt *)((unsigned char *)waypoint + 0xac) = (UnsignedInt)frameDelta;

				*(UnsignedInt *)(owner + 0x24 + index * 4) =
					(UnsignedInt)waypoint;
			}

			++pair;
		}

		*(owner + 0x3c) = 1;
	}

	Rva001F96E0IntVector *inner = module->m_nested.begin;
	while (inner != module->m_nested.end)
	{
		unsigned char allocatorStorage;
		union
		{
			void (*raw)( void );
			Rva001F96E0NestedValue member;
		} valueAt;
		valueAt.raw = j_0003cf51;
		int allocator = (inner->*valueAt.member)( &allocatorStorage );

		int *sourceBegin = inner->begin;
		int *sourceEnd = inner->end;
		int sourceCount = (int)(sourceEnd - sourceBegin);
		Rva001F96E0IntVector copied;
		union
		{
			void (*raw)( void );
			Rva001F96E0VectorCtor member;
		} constructVector;
		constructVector.raw = j_000212d3;
		(( &copied )->*constructVector.member)( sourceCount, allocator );

		if (sourceCount != 0)
			memmove( copied.begin, sourceBegin, sourceCount * sizeof(int) );

		int *copiedBegin = copied.begin;
		int *copiedEnd = copied.end;
		if (copiedBegin != copiedEnd)
		{
			UnsignedInt firstIndex = (UnsignedInt)copiedBegin[0];
			UnsignedInt lastIndex =
				(UnsignedInt)copiedEnd[-1];
			if (wasBuilt == 0)
			{
				Rva001F96E0Waypoint *first =
					*(Rva001F96E0Waypoint **)(owner + 0x24 + firstIndex * 4);
				Rva001F96E0Waypoint *last =
					*(Rva001F96E0Waypoint **)(owner + 0x24 + lastIndex * 4);
				UnsignedInt count =
					*(UnsignedInt *)((unsigned char *)first + 0x4c);
				if (count < 8)
				{
					*(Rva001F96E0Waypoint **)((unsigned char *)first +
						0x20 + count * 4) = last;
					*(UnsignedInt *)((unsigned char *)first + 0x4c) = count + 1;
				}
				*(Rva001F96E0Waypoint **)((unsigned char *)last + 0x40) = first;

				Rva001F96E0AI *ai = *(Rva001F96E0AI **)0x012ef214;
				union
				{
					void (*raw)( void );
					Rva001F96E0PathAdd member;
				} addPath;
				addPath.raw = j_0003793e;
				(ai->m_pathfinder->*addPath.member)( first );
			}

			if (wasBuilt == 0)
			{
				int count = (int)(copiedEnd - copiedBegin) - 2;
				for (int i = 0; i < count; ++i)
				{
					UnsignedInt nextIndex = (UnsignedInt)copiedBegin[i + 1];
					UnsignedInt priorIndex = (UnsignedInt)copiedBegin[i];
					Rva001F96E0Waypoint *next =
						*(Rva001F96E0Waypoint **)(owner + 0x24 + nextIndex * 4);
					Rva001F96E0Waypoint *prior =
						*(Rva001F96E0Waypoint **)(owner + 0x24 + priorIndex * 4);
					*(unsigned char *)((unsigned char *)next + 0x48) = 0;
					*(Rva001F96E0Waypoint **)((unsigned char *)prior + 0x44) = next;
				}
			}
		}

		int elemCount = (int)(copiedEnd - copiedBegin);
		unsigned int copiedBytes = (unsigned int)elemCount * sizeof(int);
		if (copiedBytes > 0x80)
			::operator delete( copiedBegin );
		else if (copiedBegin != 0)
			_STL::__node_alloc<true, 0>::_M_deallocate(
				copiedBegin, copiedBytes );

		++inner;
	}
}

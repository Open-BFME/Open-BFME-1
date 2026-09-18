// ?dup_001f96e0@@YAXXZ
// partial score=0.45 date=2026-09-17
// ?dup_001f96e0@@YAXXZ
// Retail 0x001F96E0 / 979 bytes.  The DynamicPortalBehaviour receiver layout
// is witnessed by its constructor and vtable, but this private body has no
// proved semantic method name, so the source and claim stay address-derived.
//
// The body builds BFME waypoint objects from the module's bone positions and
// then links the copied integer paths.  The small local type models below are
// deliberately scoped to this reconstruction: their offsets are witnessed by
// the retail stores, while their semantic owners are not.

// cl: /DNDEBUG /MD /EHsc

#include <string.h>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
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

struct Rva001F96E0PairVector
{
	Rva001F96E0Pair *begin;
	Rva001F96E0Pair *end;
};

struct Rva001F96E0IntVector
{
	int *begin;
	int *end;
	int *capacity;
};

struct Rva001F96E0NestedVector
{
	Rva001F96E0IntVector *begin;
	Rva001F96E0IntVector *end;
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

class Rva001F96E0Object
{
public:
	unsigned char m_pad00[0x74];
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

extern void j_000107ad( void );
extern void j_0001364c( void );
extern void j_00016c93( void );
extern void j_0001adb1( void );
extern void j_000212d3( void );
extern void j_0003793e( void );
extern void j_0003cf51( void );
extern void j_0000e68d( void );

typedef void (*Rva001F96E0ArrayElement)( void * );

#pragma comment(linker, "/alternatename:?Rva001F96E0ArrayNew@@YGXPAXIHP6EX0@Z1@Z=?ArrayNewHelperBodyThunk@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva001F96E0ArrayDelete@@YGXPAXIHP6EX0@Z@Z=?ArrayDeleteHelperBodyThunk@@YAXXZ")

extern void __stdcall Rva001F96E0ArrayNew(
	void *, unsigned int, int, Rva001F96E0ArrayElement,
	Rva001F96E0ArrayElement );
extern void __stdcall Rva001F96E0ArrayDelete(
	void *, unsigned int, int, Rva001F96E0ArrayElement );

typedef void (Rva001F96E0Object::*Rva001F96E0GetPositions)(
	const char *, Coord3D *, int, int, int );
typedef void (Rva001F96E0Waypoint::*Rva001F96E0WaypointCtor)(
	UnsignedInt, BFMERetailAsciiString,
	const Coord3D *, GameSpyGroupRoom, GameSpyGroupRoom, GameSpyGroupRoom,
	unsigned char, UnsignedInt, GameSpyGroupRoom );
typedef int (Rva001F96E0IntVector::*Rva001F96E0NestedValue)(
	unsigned char * );
typedef void (Rva001F96E0IntVector::*Rva001F96E0VectorCtor)(
	int, int );
typedef void (Rva001F96E0IntVector::*Rva001F96E0VectorDtor)(
	);
typedef void (Rva001F96E0Pathfinder::*Rva001F96E0PathAdd)(
	Rva001F96E0Waypoint * );

class Rva001F96E0Owner
{
public:
	void rva001f96e0( void );
};

void Rva001F96E0Owner::rva001f96e0( void )
{
	unsigned char *owner = (unsigned char *)this;
	volatile unsigned char framePadding[8];
	unsigned char positionStorage[16 * sizeof(Coord3D)];

	Rva001F96E0ArrayNew( positionStorage, sizeof(Coord3D), 0x10,
		(Rva001F96E0ArrayElement)j_00016c93,
		(Rva001F96E0ArrayElement)j_0001364c );

	unsigned char wasBuilt = *(owner + 0x3c);
	Rva001F96E0ModuleData *module =
		*(Rva001F96E0ModuleData **)(owner + 4);
	Rva001F96E0Object *object =
		*(Rva001F96E0Object **)(owner + 8);
	int frameDelta = 0;
	framePadding[7] = 0;

	if (wasBuilt == 0)
	{
		const char *prefix = module->m_bonePrefix.text();
		if (prefix == 0)
			prefix = (const char *)0x0107388b;

		union
		{
			void (*raw)( void );
			Rva001F96E0GetPositions member;
		} getPositions;
		getPositions.raw = j_000107ad;
		(object->*getPositions.member)( prefix, (Coord3D *)positionStorage,
			0, 1, 0 );

		if (module->m_valueDC != *(const Real *)0x01075350)
		{
			Rva001F96E0GameLogic *logic =
				*(Rva001F96E0GameLogic **)0x012f0898;
			Real scaled = module->m_valueDC * *(const Real *)0x010a39c4;
			frameDelta = (int)scaled;
			frameDelta = (int)logic->m_frame - frameDelta;
		}
	}

	Rva001F96E0Pair *pair = module->m_pairs.begin;
	Rva001F96E0Pair *pairEnd = module->m_pairs.end;
	while (pair != pairEnd)
	{
		UnsignedInt index = pair->index;
		Coord3D *location = ((Coord3D *)positionStorage) + index * 3;
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

			*(UnsignedInt *)(owner + 0x24 + index * 4) =
				(UnsignedInt)waypoint;
			*(unsigned char *)((unsigned char *)waypoint + 0x68) = 1;
			memmove( (unsigned char *)waypoint + 0x6c,
				(unsigned char *)module + 0x74, 0x18 );
			*(unsigned char *)((unsigned char *)waypoint + 0x84) = 1;
			memmove( (unsigned char *)waypoint + 0x88,
				(unsigned char *)module + 0x8c, 0x18 );
			*(unsigned char *)((unsigned char *)waypoint + 0xa0) =
				module->m_flagc5;
			if (frameDelta > 0)
				*(UnsignedInt *)((unsigned char *)waypoint + 0xac) = frameDelta;
		}

		++pair;
	}

	*(owner + 0x3c) = 1;

	Rva001F96E0NestedVector *nested = &module->m_nested;
	Rva001F96E0IntVector *inner = nested->begin;
	while (inner != nested->end)
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

		unsigned int copiedBytes =
			(unsigned int)((char *)copiedEnd - (char *)copiedBegin);
		if (copiedBytes > 0x80)
			::operator delete( copiedBegin );
		else if (copiedBegin != 0)
			_STL::__node_alloc<true, 0>::_M_deallocate(
				copiedBegin, copiedBytes );

		union
		{
			void (*raw)( void );
			Rva001F96E0VectorDtor member;
		} destroyVector;
		destroyVector.raw = j_0000e68d;
		(( &copied )->*destroyVector.member)();
		++inner;
	}

	Rva001F96E0ArrayDelete( positionStorage, sizeof(Coord3D), 0x10,
		(Rva001F96E0ArrayElement)j_0001364c );
}

// ?rva002c2a60@GiantBirdAIUpdate@@MAEXPAX0@Z
// partial score=0.15 date=2026-09-22
// cl: /DNDEBUG /MD

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
// GiantBirdAIUpdate's primary vtable 0x010C7F40 is proven (ctor 0x002C2430,
// deleting dtor 0x002C2800 at slot 0, privateFollowPathAppend at slot 0x74 --
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/
// GiantBirdAIUpdate_privateFollowPathAppend.cpp).  This body is the same
// vtable's slot 0x58 (index 22); no source names that slot, so it keeps its
// address-derived identity on the real, vtable-proven class.
class AIUpdateInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void rva002c2a60( void *segmentList, void *arg1 );
};

class GiantBirdAIUpdate : public AIUpdateInterface
{
protected:
	virtual void rva002c2a60( void *segmentList, void *arg1 );

private:
	unsigned char m_pad000[ 0x1cc - 4 ];
	void *m_z1cc;
	unsigned char m_pad1d0[ 0x478 - 0x1d0 ];
	void *m_z478;
	unsigned char m_pad47c[ 0x488 - 0x47c ];
	unsigned char m_z488;
};

// still-dump helper reached only through ILT thunk j_000070cc; matched
// sibling PathVector::push_back / SinglePathVector::insertInitial share the
// exact same generated body (Coord3DVectorInsertOverflow.cpp).
extern "C" void j_000070cc();
// still-dump helper reached only through ILT thunk j_0002299e; the matched
// Rva002BCE00StateAction::run has the identical (Path*,Object*,void*,void*)
// shape (Rva002BCE00StateAction.cpp) and is reached the same way from a
// sibling body, so the call is modelled on that signature.
extern "C" void j_0002299e();

class PathVector
{
public:
	PathVector() : m_start( 0 ), m_finish( 0 ), m_endOfStorage( 0 ) {}
	~PathVector();

	Real *m_start;
	Real *m_finish;
	Real *m_endOfStorage;
};

struct SegmentNode
{
	SegmentNode *m_next0;
	void *m_next4;
	unsigned char m_pad08[ 4 ];
	Real *m_begin;
	Real *m_end;
	void *m_z14;
	unsigned char m_pad18[ 8 ];
	SegmentNode *m_next;
	unsigned char m_pad24[ 0x4c - 0x24 ];
	int m_hasMore;
};

class RunTarget;
typedef void ( RunTarget::*RunMethod )( Real **, Object *, void *, void * );

namespace _STL
{
void vectorLargeDeallocate( void *memory );
}
extern "C" void __cdecl node_alloc_deallocate( void *memory, unsigned int bytes );

void GiantBirdAIUpdate::rva002c2a60( void *segmentList, void *arg1 )
{
	if( m_z1cc != 0 )
		m_z478 = *reinterpret_cast<void **>( reinterpret_cast<char *>( m_z1cc ) + 0x44 );
	m_z488 = 0;

	PathVector path;

	SegmentNode *head = reinterpret_cast<SegmentNode *>( segmentList );
	if( head != 0 )
	{
		SegmentNode *node = head;
		for( ;; )
		{
			Real *begin = node->m_begin;
			Real *end = node->m_end;

			if( node->m_hasMore == 0 )
			{
				m_z488 = 1;

				union
				{
					void ( *raw )( void );
					RunMethod member;
				} run;
				run.raw = (void ( * )( void ))j_0002299e;
				Real *segment[ 2 ];
				segment[ 0 ] = begin;
				segment[ 1 ] = end;
				( reinterpret_cast<RunTarget *>( this )->*run.member )(
					segment, 0, arg1, 0 );

				node = 0;
				break;
			}

			if( path.m_finish == path.m_endOfStorage || path.m_finish == 0 )
			{
				class ValueTarget;
				typedef void ( ValueTarget::*InsertCall )( Real *, const Real *, const void *, unsigned int, Bool );
				union
				{
					void ( *raw )( void );
					InsertCall member;
				} insert;
				insert.raw = (void ( * )( void ))j_000070cc;
				Real value[ 2 ] = { (Real)(size_t)begin, (Real)(size_t)end };
				( reinterpret_cast<ValueTarget *>( &path )->*insert.member )(
					path.m_finish, value, 0, 1, true );
			}
			else
			{
				Real *slot = path.m_finish;
				slot[ 0 ] = (Real)(size_t)begin;
				slot[ 1 ] = (Real)(size_t)end;
				path.m_finish += 3;
			}

			if( node->m_hasMore == 0 )
				break;
			node = node->m_next;
			if( node == head )
				break;
		}
	}

	unsigned int bytes = (unsigned int)(
		reinterpret_cast<char *>( path.m_endOfStorage ) - reinterpret_cast<char *>( path.m_start ) );
	if( bytes > 0x80 )
		_STL::vectorLargeDeallocate( path.m_start );
	else if( path.m_start != 0 )
		node_alloc_deallocate( path.m_start, bytes );
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc
// partial score=0.50 date=2026-09-03
// stlport
// partial score=0.50 date=2026-09-03
// Open-BFME scratch reconstruction for retail 0x00240F10.

typedef char Bool;
typedef int Int;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

class AsciiString
{
private:
	void *m_data;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	char m_vtable[ 4 ];
	BfmeOverridable *m_nextOverride;
};

class ThingTemplate : public BfmeOverridable
{
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate( const AsciiString &name );
};

extern ThingFactory *TheThingFactory;

class BfmeD975
{
public:
	Bool bfmeUse975D( void *other );
};

class Object
{
public:
	char m_head[ 4 ];
	ThingTemplate *m_template;
	char m_gap[ 0x74 - 8 ];
	Int m_id;
};

#define BFME_VIEW_SLOT( N ) virtual void bfmeViewSlot##N( void ) = 0
class BfmeHordeContainView
{
public:
	BFME_VIEW_SLOT( 00 ); BFME_VIEW_SLOT( 01 ); BFME_VIEW_SLOT( 02 );
	BFME_VIEW_SLOT( 03 ); BFME_VIEW_SLOT( 04 ); BFME_VIEW_SLOT( 05 );
	BFME_VIEW_SLOT( 06 ); BFME_VIEW_SLOT( 07 ); BFME_VIEW_SLOT( 08 );
	BFME_VIEW_SLOT( 09 ); BFME_VIEW_SLOT( 10 ); BFME_VIEW_SLOT( 11 );
	BFME_VIEW_SLOT( 12 ); BFME_VIEW_SLOT( 13 ); BFME_VIEW_SLOT( 14 );
	BFME_VIEW_SLOT( 15 ); BFME_VIEW_SLOT( 16 ); BFME_VIEW_SLOT( 17 );
	BFME_VIEW_SLOT( 18 ); BFME_VIEW_SLOT( 19 ); BFME_VIEW_SLOT( 20 );
	BFME_VIEW_SLOT( 21 ); BFME_VIEW_SLOT( 22 ); BFME_VIEW_SLOT( 23 );
	BFME_VIEW_SLOT( 24 ); BFME_VIEW_SLOT( 25 ); BFME_VIEW_SLOT( 26 );
	BFME_VIEW_SLOT( 27 ); BFME_VIEW_SLOT( 28 ); BFME_VIEW_SLOT( 29 );
	virtual void bfmePrepare( int value ) = 0;
};
#undef BFME_VIEW_SLOT

class BfmeSubDSU
{
public:
	void **bfmeTwoDSU( void **key );

private:
	char m_body[ 12 ];
};

struct BfmeHordeRosterEntry
{
	void *m_key;
	AsciiString m_name;
};

class BfmeHordeRosterOwner
{
public:
	char m_head[ 0x224 ];
	BfmeHordeRosterEntry **m_begin;
	BfmeHordeRosterEntry **m_end;
};

struct BfmeHordeSlot
{
	void *m_key;
	char m_tail[ 12 ];
};

struct BfmeInsertResult
{
	void *m_iterator;
	Bool m_inserted;
};

class BfmeObjectIDTree
{
public:
	BfmeInsertResult insertUnique( const Int &id );

private:
	char m_body[ 12 ];
};

class BfmeHordeContainAdmit
{
public:
	void addMember( Object *member );

private:
	char m_head[ 0x30 ];
	BfmeObjectIDTree m_memberIds;
	BfmeSubDSU m_indices;
	BfmeHordeSlot *m_slotsBegin;
	BfmeHordeSlot *m_slotsEnd;
	BfmeHordeSlot *m_slotsCapacity;
	_STL::list<Int> m_freeIndices;
	char m_flag;
};

void BfmeHordeContainAdmit::addMember( Object *member )
{
	if ( m_flag == 0 )
		((BfmeHordeContainView *)( (char *)this - 0xe4 ))->bfmePrepare( 1 );

	_STL::list<Int>::iterator node = m_freeIndices.begin();
	if ( node == m_freeIndices.end() )
		return;

	Int index = *node;
	void *slotKey = m_slotsBegin[ index ].m_key;
	BfmeHordeRosterOwner *owner =
		*(BfmeHordeRosterOwner **)( (char *)this - 0xe0 );
	BfmeHordeRosterEntry **cursor = owner->m_begin;
	for ( ; cursor != owner->m_end; ++cursor )
	{
		if ( slotKey == (*cursor)->m_key )
			break;
	}
	if ( cursor == owner->m_end )
		return;

	ThingTemplate *ownerTemplate =
		TheThingFactory->findTemplate( (*cursor)->m_name );
	ThingTemplate *memberTemplate = member->m_template;
	BfmeOverridable *resolved = memberTemplate;
	if ( resolved != 0 && resolved->m_nextOverride != 0 )
		resolved = resolved->m_nextOverride->friend_getFinalOverride();
	if ( !((BfmeD975 *)resolved)->bfmeUse975D( ownerTemplate ) )
		return;

	Int id = member->m_id;
	*(Int *)m_indices.bfmeTwoDSU( (void **)&id ) = index;

	m_freeIndices.erase( node );

	m_memberIds.insertUnique( id );
}

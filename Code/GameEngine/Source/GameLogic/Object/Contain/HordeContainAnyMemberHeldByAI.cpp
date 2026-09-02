// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the horde-container query that asks whether any contained member
// is currently held by its AI, retail 0x0023CD70.
//
// `this` is the interface subobject, not the container: every reference to the
// contained-items list is `this - 0xAC`, the same interior-this shape
// GarrisonContain::getApparentControllingPlayer records in docs/lessons.md. The
// member is an STLport list, so its one word is the sentinel node and the walk
// re-reads that word every iteration because the virtual call inside can change
// it.
//
// Each node's value at +8 is an Object; the AI interface at Object+0x204 is
// null-checked, asked slot 97, and only then is bit 0x10000000 of the status
// word at Object+0x90 tested. Any member passing all three wins immediately;
// the exhausted loop falls into the shared `xor al, al`.
//
// The AI interface is opaque apart from slot 97, so the preceding slots are
// placeholders.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define BFME_SLOT( N ) virtual int bfmeSlot##N( void ) = 0

class BfmeMemberAIInterface
{
public:
	BFME_SLOT( 00 ); BFME_SLOT( 01 ); BFME_SLOT( 02 ); BFME_SLOT( 03 );
	BFME_SLOT( 04 ); BFME_SLOT( 05 ); BFME_SLOT( 06 ); BFME_SLOT( 07 );
	BFME_SLOT( 08 ); BFME_SLOT( 09 ); BFME_SLOT( 10 ); BFME_SLOT( 11 );
	BFME_SLOT( 12 ); BFME_SLOT( 13 ); BFME_SLOT( 14 ); BFME_SLOT( 15 );
	BFME_SLOT( 16 ); BFME_SLOT( 17 ); BFME_SLOT( 18 ); BFME_SLOT( 19 );
	BFME_SLOT( 20 ); BFME_SLOT( 21 ); BFME_SLOT( 22 ); BFME_SLOT( 23 );
	BFME_SLOT( 24 ); BFME_SLOT( 25 ); BFME_SLOT( 26 ); BFME_SLOT( 27 );
	BFME_SLOT( 28 ); BFME_SLOT( 29 ); BFME_SLOT( 30 ); BFME_SLOT( 31 );
	BFME_SLOT( 32 ); BFME_SLOT( 33 ); BFME_SLOT( 34 ); BFME_SLOT( 35 );
	BFME_SLOT( 36 ); BFME_SLOT( 37 ); BFME_SLOT( 38 ); BFME_SLOT( 39 );
	BFME_SLOT( 40 ); BFME_SLOT( 41 ); BFME_SLOT( 42 ); BFME_SLOT( 43 );
	BFME_SLOT( 44 ); BFME_SLOT( 45 ); BFME_SLOT( 46 ); BFME_SLOT( 47 );
	BFME_SLOT( 48 ); BFME_SLOT( 49 ); BFME_SLOT( 50 ); BFME_SLOT( 51 );
	BFME_SLOT( 52 ); BFME_SLOT( 53 ); BFME_SLOT( 54 ); BFME_SLOT( 55 );
	BFME_SLOT( 56 ); BFME_SLOT( 57 ); BFME_SLOT( 58 ); BFME_SLOT( 59 );
	BFME_SLOT( 60 ); BFME_SLOT( 61 ); BFME_SLOT( 62 ); BFME_SLOT( 63 );
	BFME_SLOT( 64 ); BFME_SLOT( 65 ); BFME_SLOT( 66 ); BFME_SLOT( 67 );
	BFME_SLOT( 68 ); BFME_SLOT( 69 ); BFME_SLOT( 70 ); BFME_SLOT( 71 );
	BFME_SLOT( 72 ); BFME_SLOT( 73 ); BFME_SLOT( 74 ); BFME_SLOT( 75 );
	BFME_SLOT( 76 ); BFME_SLOT( 77 ); BFME_SLOT( 78 ); BFME_SLOT( 79 );
	BFME_SLOT( 80 ); BFME_SLOT( 81 ); BFME_SLOT( 82 ); BFME_SLOT( 83 );
	BFME_SLOT( 84 ); BFME_SLOT( 85 ); BFME_SLOT( 86 ); BFME_SLOT( 87 );
	BFME_SLOT( 88 ); BFME_SLOT( 89 ); BFME_SLOT( 90 ); BFME_SLOT( 91 );
	BFME_SLOT( 92 ); BFME_SLOT( 93 ); BFME_SLOT( 94 ); BFME_SLOT( 95 );
	BFME_SLOT( 96 );
	virtual Bool bfmeIsAIHolding( void ) = 0;						///< slot 97
};

#undef BFME_SLOT

// upstream layout: reference/shims/bfmeobject/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[ 0x90 ];
	UnsignedInt m_bfmeStatus[ 2 ];								///< retail this+0x90
	char m_bfmeGap[ 0x204 - 0x98 ];
	BfmeMemberAIInterface *m_bfmeAI;							///< retail this+0x204
};

// upstream layout: STLport 4.5.3 list node
struct BfmeContainedNode
{
	BfmeContainedNode *m_bfmeNext;								///< +0x00
	BfmeContainedNode *m_bfmePrev;								///< +0x04
	Object *m_bfmeObject;										///< +0x08
};

class BfmeContainInterfaceView
{
public:
	Bool bfmeAnyMemberHeldByAI( void ) const;

private:
	BfmeContainedNode *const &bfmeContainList( void ) const
	{
		return *(BfmeContainedNode *const *)( (const char *)this - 0xac );
	}
};

// ?bfmeAnyMemberHeldByAI@BfmeContainInterfaceView@@QBE_NXZ
Bool BfmeContainInterfaceView::bfmeAnyMemberHeldByAI( void ) const
{
	BfmeContainedNode *sentinel = bfmeContainList();

	for ( BfmeContainedNode *node = sentinel->m_bfmeNext; node != sentinel;
		node = node->m_bfmeNext, sentinel = bfmeContainList() )
	{
		Object *member = node->m_bfmeObject;
		BfmeMemberAIInterface *ai = member->m_bfmeAI;

		if ( ai && ai->bfmeIsAIHolding() && ( member->m_bfmeStatus[ 0 ] & 0x10000000 ) )
			return true;
	}

	return false;
}

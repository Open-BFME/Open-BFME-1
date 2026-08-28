// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: address-derived object visitor at retail 0x000D46E0.
//
// The visitor's context is three dwords: a bit index, the running count, and
// the inclusive limit.  The object supplies a word-indexed bitset at +0x110.
// It stops Player::iterateObjects only after incrementing beyond the limit.

typedef int Int;
typedef unsigned int UnsignedInt;

class Rva000D46E0Object
{
public:
	unsigned char m_unmodelled_000[ 0x110 ];
	UnsignedInt m_bits[ 1 ];
};

struct Rva000D46E0CountContext
{
	UnsignedInt m_bitIndex;
	Int m_count;
	Int m_limit;
};

Int rva000D46E0CountVisit( Rva000D46E0Object *object, void *userData )
{
	Rva000D46E0CountContext *context =
		static_cast<Rva000D46E0CountContext *>( userData );
	UnsignedInt bit = context->m_bitIndex;

	if ( object->m_bits[ bit >> 5 ] & ( 1U << ( bit & 0x1F ) ) )
	{
		++context->m_count;
		if ( context->m_count > context->m_limit )
			return 0;
	}

	return 1;
}

class Object;
typedef void ( *PlayerObjectVisit )( Object *object, void *userData );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void iterateObjects( PlayerObjectVisit visit, void *userData ) const;
	Int rva000D4730CountObjects( UnsignedInt bitIndex, Int limit ) const;
};

Int Player::rva000D4730CountObjects( UnsignedInt bitIndex, Int limit ) const
{
	Rva000D46E0CountContext context = { bitIndex, 0, limit };
	iterateObjects(
		reinterpret_cast<PlayerObjectVisit>( rva000D46E0CountVisit ), &context );
	return context.m_count;
}

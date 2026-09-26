// ?d_0049ba80@@YAXXZ
// partial score=0.62 date=2026-09-21
// cl: /DNDEBUG /MD
// Retail 0x0049BA80, 292 bytes. Dispatches on this+0x18's flag bits to pick
// one of several status checks on the caller-supplied object, comparing (or
// storing) the result into this+0x148. this+0x138/+0x13c bound a pointer
// vector that must hold >=2 entries or the result is forced to 0; a null
// object, or any branch's own lookup miss, instead leaves this+0x148
// untouched. No caller, vtable, or string proves the owning class, so the
// receiver keeps an address-derived name; callee pins keep their given
// signatures/names.

typedef int Int;
typedef unsigned int UInt;

class BFMEWeaponSetFlags
{
public:
	UInt m_bits;
};

class BFMEWeaponSetOwner
{
public:
	const BFMEWeaponSetFlags &getWeaponSetFlags() const;
};

class RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve( Int id );
};

class BfmeX1004
{
public:
	char m_unmodelled000[ 0xd8 ];
};

class BfmeHold1004
{
public:
	BfmeX1004 *bfmeFind1004();
};

class BFMEActionObject
{
public:
	bool testStatus( Int code ) const;
};

class BFMESelectionStatusBits
{
public:
	bool test( UInt bit ) const;
};

class Rva0049BA80Owner
{
public:
	void rva0049ba80( void *object, bool flag );

private:
	char m_unmodelled000[ 0x10 ];
	Int m_field10;
	char m_unmodelled014[ 0x18 - 0x14 ];
	UInt m_flags18;
	char m_unmodelled01c[ 0x70 - 0x1c ];
	Int m_field70;
	Int m_field74;
	Int m_field78;
	UInt m_field7c;
	char m_unmodelled080[ 0x138 - 0x80 ];
	char *m_vecBegin;
	char *m_vecEnd;
	char m_unmodelled140[ 0x148 - 0x140 ];
	Int m_cached148;
};

void Rva0049BA80Owner::rva0049ba80( void *object, bool flag )
{
	if ( object == 0 )
		return;

	if ( ( UInt )( m_vecEnd - m_vecBegin ) >> 2 < 2u )
	{
		m_cached148 = 0;
		return;
	}

	UInt flags = m_flags18;

	if ( flags & 0x1000000 )
	{
		BFMEWeaponSetOwner *owner = reinterpret_cast<BFMEWeaponSetOwner *>( object );
		const BFMEWeaponSetFlags &weaponFlags = owner->getWeaponSetFlags();
		bool bitSet = ( weaponFlags.m_bits & m_field7c ) != 0;
		m_cached148 = ( bitSet != flag ) ? 1 : 0;
		return;
	}

	if ( flags & 0x2000000 )
	{
		RvaC4390Second *second = reinterpret_cast<RvaC4390Second *>( object );
		RvaC4390First *first = second->resolve( 0 );
		if ( first == 0 )
			return;

		BfmeHold1004 *holder = reinterpret_cast<BfmeHold1004 *>( first );
		BfmeX1004 *found = holder->bfmeFind1004();
		if ( found == 0 )
			return;

		typedef bool ( BfmeX1004::*Slot0xd8 )();
		void *slotPtr = ( *reinterpret_cast<void ***>( found ) )[ 0xd8 / 4 ];
		union
		{
			void *asVoid;
			Slot0xd8 asMember;
		} slotCast;
		slotCast.asVoid = slotPtr;
		m_cached148 = ( ( found->*slotCast.asMember )() != flag ) ? 1 : 0;
		return;
	}

	if ( flags & 0x800000 )
	{
		if ( m_field10 == 0x22 )
		{
			BFMESelectionStatusBits *bits =
				reinterpret_cast<BFMESelectionStatusBits *>( object );
			if ( bits->test( 0x89 ) )
			{
				m_cached148 = m_field74;
				return;
			}
			if ( bits->test( 0x8a ) )
			{
				m_cached148 = m_field78;
				return;
			}
			m_cached148 = m_field70;
			return;
		}

		if ( m_field10 != 0x2e )
			return;

		BFMEActionObject *action = reinterpret_cast<BFMEActionObject *>( object );
		bool status = action->testStatus( 0x17 );
		m_cached148 = ( status != flag ) ? 1 : 0;
		return;
	}
}

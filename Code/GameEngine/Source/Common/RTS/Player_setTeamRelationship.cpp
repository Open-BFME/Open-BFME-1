// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?setTeamRelationship@Player@@QAEXPBVTeam@@W4Relationship@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Player::setTeamRelationship, retail 0x000D7640.
//
// Zero Hour's body verbatim. BFME's TeamRelationMap carries a single vtable
// pointer rather than ZH's two bases, so m_map sits at +0x04; the hash_map is
// the int/int instantiation whose operator[] is matched at 0x000D6280 and
// reached here through its incremental-link thunk.

typedef int Int;

namespace _STL {

template <class T> struct hash {};
template <class T> struct equal_to {};
template <class T1, class T2> struct pair { T1 first; T2 second; };
template <class T> class allocator {};

template <class K, class V, class H, class E, class A> class hash_map
{
public:
	V &operator[]( const K &key );
};

}	// namespace _STL

typedef _STL::hash_map< Int, Int, _STL::hash< Int >, _STL::equal_to< Int >,
		_STL::allocator< _STL::pair< const Int, Int > > > TeamRelationMapType;

enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[ 0x08 ];
	Int m_id;											///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamRelationMap
{
public:
	virtual ~TeamRelationMap();							///< the vtable pointer occupies +0x00

	TeamRelationMapType m_map;							///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void setTeamRelationship( const Team *that, Relationship r );

private:
	unsigned char m_unreconstructed_00[ 0x290 ];
	TeamRelationMap *m_teamRelations;					///< retail this+0x290
};

void Player::setTeamRelationship( const Team *that, Relationship r )
{
	if( that != 0 )
	{
		// note that this creates the entry if it doesn't exist.
		m_teamRelations->m_map[ that->getID() ] = r;
	}
}

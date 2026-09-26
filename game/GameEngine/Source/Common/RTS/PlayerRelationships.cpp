// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?removePlayerRelationship@Player@@QAE_NPBV1@@Z: game/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?setTeamRelationship@Player@@QAEXPBVTeam@@W4Relationship@@@Z: game/GameEngine/Source/Common/RTS/Player.cpp

// The two relation maps a Player carries, and they are adjacent:
//
//   0x000D4160  removePlayerRelationship   m_playerRelations at Player+0x28C
//   0x000D7640  setTeamRelationship        m_teamRelations   at Player+0x290
//
// Both are Zero Hour's body verbatim on BFME's layout, and both maps have the
// same BFME shape: where Zero Hour gives the map object MemoryPoolObject plus
// Snapshot, BFME gives it a single vtable pointer, so m_map lands at +0x04 in
// each. That shape was written down twice, once per file, with no way to see
// that it is one fact about two neighbouring fields.
//
// They also each modelled a different half of Player and left the other half
// as padding -- one named the player index at +0x24 and stopped at +0x28C, the
// other spelled 0x290 bytes of nothing. One layout states the index and both
// maps.
//
// The two hash_map spellings are NOT drift and do not collapse. This TU takes
// STLport's real <hash_map> because removePlayerRelationship's body is made of
// empty/find/erase/clear inlined out of it. setTeamRelationship's file had
// instead hand-written a stub _STL::hash_map declaring operator[] only, so
// that its one use compiled to a call rather than to an inlined insert -- and
// that call is the point: retail reaches the int/int operator[] body at
// 0x000D6280 through its incremental-link thunk. Under the real header MSVC
// still emits the call rather than inlining it, so both bodies match against
// one header and the stub is gone; had it inlined, the two would have had to
// stay apart.
//
// The team file built with /EHs-c- and no _STLP_USE_STATIC_LIB; it
// byte-verifies unchanged under the player file's flags, which is what let the
// two share a TU.

#include <hash_map>

class Xfer;

typedef int Int;
typedef bool Bool;
typedef Int PlayerIndex;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

typedef _STL::pair< const PlayerIndex, Relationship > PlayerRelationMapPair;
typedef _STL::hash_map< PlayerIndex, Relationship, _STL::hash< PlayerIndex >,
		_STL::equal_to< PlayerIndex >, _STL::allocator< PlayerRelationMapPair > >
		PlayerRelationMapType;

typedef _STL::hash_map< Int, Int, _STL::hash< Int >, _STL::equal_to< Int >,
		_STL::allocator< _STL::pair< const Int, Int > > > TeamRelationMapType;

// BFME gives the relation maps one base with a vtable where Zero Hour gives
// them MemoryPoolObject plus Snapshot, so m_map lands at +0x04 in both.
class PlayerRelationMapBase
{
public:
	virtual ~PlayerRelationMapBase() {}

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class PlayerRelationMap : public PlayerRelationMapBase
{
public:
	virtual ~PlayerRelationMap();

	PlayerRelationMapType m_map;						///< retail this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamRelationMap
{
public:
	virtual ~TeamRelationMap();							///< the vtable pointer occupies +0x00

	TeamRelationMapType m_map;							///< retail this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Int getID( void ) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[ 0x08 ];
	Int m_id;											///< retail this+0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool removePlayerRelationship( const Player *that );
	void setTeamRelationship( const Team *that, Relationship r );

	PlayerIndex getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[ 0x24 ];
	PlayerIndex m_playerIndex;							///< retail this+0x24
	unsigned char m_unreconstructed_28[ 0x28c - 0x28 ];
	PlayerRelationMap *m_playerRelations;				///< retail this+0x28C
	TeamRelationMap *m_teamRelations;					///< retail this+0x290
};

// ?removePlayerRelationship@Player@@QAE_NPBV1@@Z
//
// Near twin of ?removeTeamRelationship@Player@@QAE_NPBVTeam@@@Z at 0x000D4200,
// which reads m_teamRelations and keys on the team id at +0x08. That one is a
// row in Player.cpp and stays there.
Bool Player::removePlayerRelationship( const Player *that )
{
	if( !m_playerRelations->m_map.empty() )
	{
		if( that == 0 )
		{
			m_playerRelations->m_map.clear();
			return true;
		}
		else
		{
			PlayerRelationMapType::iterator it =
					m_playerRelations->m_map.find( that->getPlayerIndex() );
			if( it != m_playerRelations->m_map.end() )
			{
				m_playerRelations->m_map.erase( it );
				return true;
			}
		}
	}
	return false;
}

// ?setTeamRelationship@Player@@QAEXPBVTeam@@W4Relationship@@@Z
void Player::setTeamRelationship( const Team *that, Relationship r )
{
	if( that != 0 )
	{
		// note that this creates the entry if it doesn't exist.
		m_teamRelations->m_map[ that->getID() ] = r;
	}
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?removePlayerRelationship@Player@@QAE_NPBV1@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Player::removePlayerRelationship, retail 0x000D4160, 126 bytes.
//
// Zero Hour's body verbatim, on BFME's layout. m_playerRelations sits at
// Player+0x28c where this tree's header puts it at +0x1a4, and BFME's
// PlayerRelationMap carries one vtable pointer rather than ZH's two bases, so
// m_map sits at +0x04. getPlayerIndex needs no adjustment: retail reads +0x24
// too.
//
// It lives in its own translation unit rather than in Player.cpp because
// Player.cpp holds 21 rows that no longer byte-verify, and the commit hook
// byte-verifies every source it touches.
//
// Near twin of ?removeTeamRelationship@Player@@QAE_NPBVTeam@@@Z at 0x000D4200,
// which reads m_teamRelations at +0x290 and keys on the team id at +0x08.

#include <hash_map>

class Xfer;

typedef int Int;
typedef bool Bool;
typedef Int PlayerIndex;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

// BFME gives this one base with a vtable where Zero Hour gives it
// MemoryPoolObject plus Snapshot, so m_map lands at +0x04.
class PlayerRelationMapBase
{
public:
	virtual ~PlayerRelationMapBase() {}

protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class PlayerRelationMap : public PlayerRelationMapBase
{
public:
	virtual ~PlayerRelationMap();

	PlayerRelationMapType m_map;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool removePlayerRelationship( const Player *that );

	PlayerIndex getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[ 0x24 ];
	PlayerIndex m_playerIndex;							///< retail this+0x24
	unsigned char m_unreconstructed_28[ 0x28c - 0x28 ];
	PlayerRelationMap *m_playerRelations;				///< retail this+0x28c
};

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

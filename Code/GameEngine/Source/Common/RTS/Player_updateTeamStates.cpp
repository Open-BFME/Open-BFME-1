// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateTeamStates@Player@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Player.cpp

// Player::updateTeamStates, retail 0x000CE140. A walk of the player's team
// list at +0x288, calling one zero-argument member on each team.
//
// The list is circular through its own head: the loop starts at the head's
// next link and stops when it comes back round, which is why the terminating
// compare is against the head pointer and not against null. That pointer is
// re-read from the member on every iteration rather than kept in a register,
// so the member access is written inside the loop.
//
// The team hangs off +0x08 of each node. The member called on it is unnamed in
// the image; the name it is pinned under says what this loop does with it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void updateState( void );
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;					// +0x00
	unsigned char m_unmodelled_04[4];
	TeamPrototype *m_team;							// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void updateTeamStates( void );

private:
	unsigned char m_unmodelled_00[ 0x288 ];
	PlayerTeamNode *m_teams;				// +0x288
};

// ?updateTeamStates@Player@@QAEXXZ
void Player::updateTeamStates( void )
{
	for( PlayerTeamNode *node = m_teams->m_next; node != m_teams; node = node->m_next )
		node->m_team->updateState();
}

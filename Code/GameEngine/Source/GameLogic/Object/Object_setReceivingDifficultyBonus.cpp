// cl: /DNDEBUG /MD /EHsc
// readable body of ?setReceivingDifficultyBonus@Object@@QAEX_N@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::setReceivingDifficultyBonus, retail 0x001BE7D0. Zero Hour's body plus
// one guard:
//
//   if (receive == m_isReceivingDifficultyBonus) return;
//   m_isReceivingDifficultyBonus = receive;
//   getControllingPlayer()->friend_applyDifficultyBonusesForObject(this, m_isReceivingDifficultyBonus);
//
// getControllingPlayer is inlined to its team read, and BFME checks the player
// for null where Zero Hour dereferences it unconditionally. The flag is stored
// before that check rather than after - scheduling, not order - and the
// argument is re-READ from +0x348 rather than reusing the parameter, which is
// what passing the member instead of the argument compiles to.
//
// The applier is unnamed in the image; it is pinned on the thunk this call site
// encodes, and the name is Zero Hour's for the same call.

typedef bool Bool;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void friend_applyDifficultyBonusesForObject( Object *object, Bool receive );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setReceivingDifficultyBonus( Bool receive );

private:
	Player *getControllingPlayer() const
	{
		return m_team ? m_team->getControllingPlayer() : 0;
	}

	unsigned char m_unmodelled_000[ 0x23C ];
	Team *m_team;							// +0x23C
	unsigned char m_unmodelled_240[ 0x348 - 0x240 ];
	Bool m_isReceivingDifficultyBonus;		// +0x348
};

// ?setReceivingDifficultyBonus@Object@@QAEX_N@Z
void Object::setReceivingDifficultyBonus( Bool receive )
{
	if( receive == m_isReceivingDifficultyBonus )
		return;

	m_isReceivingDifficultyBonus = receive;

	Player *player = getControllingPlayer();

	if( !player )
		return;

	player->friend_applyDifficultyBonusesForObject( this, m_isReceivingDifficultyBonus );
}

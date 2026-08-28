// cl: /DNDEBUG /MD /EHsc

// Object::getIndicatorColor, retail 0x001BE4F0. One call, three ways out.
//
// An override colour at +0x244 wins outright when it is non-zero. Otherwise the
// team at +0x23C is asked for its controlling player and that player's colour at
// +0x1C4 is used. Anything missing on that path - no team, or a team with no
// controlling player - falls to opaque black, 0xFF000000.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_00[ 0x1C4 ];
	UnsignedInt m_color;					// +0x1C4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer( void ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	UnsignedInt getIndicatorColor( void ) const;

private:
	unsigned char m_unmodelled_00[ 0x23C ];
	Team *m_team;							// +0x23C
	unsigned char m_unmodelled_240[ 4 ];
	UnsignedInt m_indicatorColor;			// +0x244
};

// ?getIndicatorColor@Object@@QBEIXZ
UnsignedInt Object::getIndicatorColor( void ) const
{
	if( m_indicatorColor )
		return m_indicatorColor;

	if( m_team )
	{
		Player *player = m_team->getControllingPlayer();

		if( player )
			return player->m_color;
	}

	return 0xFF000000;
}

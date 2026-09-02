// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Player
{
public:
	int getPlayerIndex( void ) const { return m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer( void ) const;
};

class Rva001DD0B0PlayerMaskFilter
{
public:
	bool accepts( Object *object ) const;

private:
	unsigned char m_unreconstructed_00[8];
	unsigned short m_playerMask;
	bool m_match;
};

bool Rva001DD0B0PlayerMaskFilter::accepts( Object *object ) const
{
	Player *player = object->getControllingPlayer();
	unsigned int playerBit = player ? (1 << player->getPlayerIndex()) : 0;
	return ((m_playerMask & playerBit) != 0) == m_match;
}

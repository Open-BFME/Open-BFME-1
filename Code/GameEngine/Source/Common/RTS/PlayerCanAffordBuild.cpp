// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Player;

class Money
{
public:
	UnsignedInt m_money;
};

class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int buildIndex) const;
};

class Player
{
public:
	Bool canAffordBuild(const ThingTemplate *whatToBuild) const;

private:
	unsigned char m_beforeMoney[0x4C];
	Money m_money;
};

Bool Player::canAffordBuild(const ThingTemplate *whatToBuild) const
{
	UnsignedInt money = m_money.m_money;
	if (whatToBuild->calcCostToBuild(this, -1) <= money)
	{
		return true;
	}
	return false;
}

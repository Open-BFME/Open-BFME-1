// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// readable body of ?canAffordBuild@Player@@QBE_NPBVThingTemplate@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt m_money;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int buildIndex) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
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

// cl: /DNDEBUG /MD /EHsc
// readable body of ?maskObject@Object@@QAEX_N@Z: Code/GameEngine/Source/GameLogic/Object/Object.cpp

typedef bool Bool;
typedef unsigned short PlayerMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	PlayerMaskType getPlayerMask() const
	{
		return 1 << *reinterpret_cast<const int *>(
			reinterpret_cast<const unsigned char *>(this) + 0x24);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void deselectObject(Object *object, PlayerMaskType playerMask, Bool force);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void maskObject(Bool mask);

private:
	__forceinline Player *getControllingPlayer() const
	{
		return m_team ? m_team->getControllingPlayer() : 0;
	}

	unsigned char m_unmodelled000[0x23c];
	Team *m_team;
	unsigned char m_unmodelled240[0x345 - 0x240];
	unsigned char m_statusByte345;
};

void Object::maskObject(Bool mask)
{
	if (mask)
	{
		m_statusByte345 |= 2;
		TheGameLogic->deselectObject(
			this, ~getControllingPlayer()->getPlayerMask(), true);
	}
	else
	{
		m_statusByte345 &= ~2;
	}
}

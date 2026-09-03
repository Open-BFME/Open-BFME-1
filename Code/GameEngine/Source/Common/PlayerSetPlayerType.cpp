// cl: /DNDEBUG /MD /EHsc
// readable body of ?setPlayerType@Player@@QAEXW4PlayerType@@_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

enum PlayerType
{
	PLAYER_COMPUTER = 1
};

class BfmeOwnedAI
{
public:
	virtual ~BfmeOwnedAI();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void setPlayerType(PlayerType type, bool skirmish);

private:
	unsigned char m_bfmeBeforeType[0x2c];
	PlayerType m_playerType;
	unsigned char m_bfmeBeforeAI[0x220 - 0x30];
	BfmeOwnedAI *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	AIPlayer(Player *player);

private:
	unsigned char m_bfmeBody[0x78];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AISkirmishPlayer.h
class AISkirmishPlayer
{
public:
	AISkirmishPlayer(Player *player);

private:
	unsigned char m_bfmeBody[0xa0];
};

struct BfmeAIData
{
	unsigned char m_bfmeBeforeForceSkirmishAI[0x65];
	bool m_forceSkirmishAI;
};

struct BfmeAI
{
	const BfmeAIData *getAiData() { return m_data; }

	unsigned char m_bfmeBeforeData[0x14];
	BfmeAIData *m_data;
};

extern "C" BfmeAI *TheAIParseDefinitionAI;

void Player::setPlayerType(PlayerType type, bool skirmish)
{
	m_playerType = type;

	delete m_ai;
	m_ai = 0;

	if (type == PLAYER_COMPUTER)
	{
		if (skirmish || TheAIParseDefinitionAI->getAiData()->m_forceSkirmishAI)
			m_ai = reinterpret_cast<BfmeOwnedAI *>(new AISkirmishPlayer(this));
		else
			m_ai = reinterpret_cast<BfmeOwnedAI *>(new AIPlayer(this));
	}
}

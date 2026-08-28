// cl: /DNDEBUG /MD /EHsc

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Int getFrame() const { return m_frame; }

private:
	char m_pad00[0x3c];
	Int m_frame;
};

extern GameLogic *TheGameLogic;

class GameLogicShim
{
public:
	void unidentified_0000f5fb(Int playerIndex);

private:
	struct PlayerRecord
	{
		Int m_frame;
		char m_pad04[0x18];
	};

	char m_pad00[0x1bc];
	PlayerRecord m_playerRecords[8];
};

void GameLogicShim::unidentified_0000f5fb(Int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 8)
		m_playerRecords[playerIndex].m_frame = TheGameLogic->getFrame();
}

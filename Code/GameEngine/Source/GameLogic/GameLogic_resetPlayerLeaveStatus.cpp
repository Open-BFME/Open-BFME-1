// cl: /O2 /Ob0

struct PlayerLeaveStatus
{
	int status;
	int quitFrame;
	int defeatFrame;
	int victoryFrame;
	bool notPresent;
	char padding[3];
	int isHuman;
	char playerName[4];
};

class GameLogic
{
public:
	void resetPlayerLeaveStatus(void);

private:
	char m_fieldsBeforeLeaveStatus[0x1B0];
	PlayerLeaveStatus m_playerLeaveStatus[8];
};

void GameLogic::resetPlayerLeaveStatus(void)
{
	for (int index = 0; index < 8; ++index)
	{
		m_playerLeaveStatus[index].notPresent = true;
		m_playerLeaveStatus[index].quitFrame = 0;
		m_playerLeaveStatus[index].defeatFrame = 0;
		m_playerLeaveStatus[index].victoryFrame = 0;
		m_playerLeaveStatus[index].status = 0;
		m_playerLeaveStatus[index].isHuman = 0xFF;
	}
}

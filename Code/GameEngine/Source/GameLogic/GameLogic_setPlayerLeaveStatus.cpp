// cl: /O2 /Ob0

struct PlayerLeaveStatus
{
	int status;
	int quitFrame;
	char fields[0x14];
};

class GameLogic
{
public:
	void setPlayerLeaveStatus(int playerIndex, int status);

private:
	char m_fieldsBeforeFrame[0x3c];
	int m_frame;
	char m_fieldsBeforeLeaveStatus[0x1b0 - 0x40];
	PlayerLeaveStatus m_playerLeaveStatus[8];
};

void GameLogic::setPlayerLeaveStatus(int playerIndex, int status)
{
	if (playerIndex < 0 || playerIndex >= 8)
		return;

	m_playerLeaveStatus[playerIndex].status = status;
	m_playerLeaveStatus[playerIndex].quitFrame = m_frame;
}

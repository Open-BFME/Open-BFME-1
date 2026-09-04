// cl: /O2 /Ob0

struct PlayerLeaveStatus
{
	char fields[0x1C];
};

class GameLogic
{
public:
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);

private:
	char m_fieldsBeforeLeaveStatus[0x1B0];
	PlayerLeaveStatus m_playerLeaveStatus[8];
};

PlayerLeaveStatus *GameLogic::getPlayerLeaveStatus(int playerIndex)
{
	if (playerIndex < 0 || playerIndex >= 8)
		return 0;
	return &m_playerLeaveStatus[playerIndex];
}
